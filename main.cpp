#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "utils.hpp"
#include "maths.hpp"
#include "camera.hpp"

#include <chrono>
#include <vector>
#include <iostream>

void draw_triangle(SDL_Renderer *renderer, trz::triangle &t)
{
    SDL_RenderDrawLine(renderer, t.p[0].x, t.p[0].y, t.p[1].x, t.p[1].y);
    SDL_RenderDrawLine(renderer, t.p[0].x, t.p[0].y, t.p[2].x, t.p[2].y);
    SDL_RenderDrawLine(renderer, t.p[1].x, t.p[1].y, t.p[2].x, t.p[2].y);
}

int main()
{
    int width = 800;
    int height = 600;
    int alpha = height / width;
    float theta;

    static SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Tiny Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // raster projector
    float aspect_ratio = width / height;
    float vertical_field_of_view = 1.f;
    trz::camera camera;
    camera.set_direction({0.f, 0.f, 1.f});
    camera.set_position({0.f, 0.f, 0.f});
    // camera.set_orthographic_projection(-1, 1, -1, 1, -1, 1);
    camera.set_perspective_projection(vertical_field_of_view, 0.1f, 100.f);

    trz::vec3 screen_center = {width * 0.5f, height * 0.5f, 0.f};

    trz::mesh cubemesh;
    trz::load(cubemesh, std::ifstream("res/cube.obj"));

    int elapsedTime = 0;

    // main loop
    bool running = true;
    while (running)
    {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        float theta = .1f * elapsedTime++;

        trz::mat4 rotZ = {{0}};
        rotZ.m[0][0] = std::cos(theta);
        rotZ.m[0][1] = std::sin(theta);
        rotZ.m[1][0] = -std::sin(theta);
        rotZ.m[1][1] = std::cos(theta);
        rotZ.m[2][2] = 1.f;
        rotZ.m[3][3] = 1.f;

        trz::mat4 rotX = {{0}};
        rotX.m[0][0] = 1.f;
        rotX.m[1][1] = std::cos(theta * .5f);
        rotX.m[1][2] = std::sin(theta * .5f);
        rotX.m[2][1] = -std::sin(theta * .5f);
        rotX.m[2][2] = std::cos(theta * .5f);
        rotX.m[3][3] = 1.f;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (trz::triangle &triangle : cubemesh.tris)
        {
            // model + view transformations
            trz::triangle transformed;
            transformed.normal = rotZ * triangle.normal;
            transformed.normal = rotX * transformed.normal;
            if (transformed.normal.z < 0.f)
            {
                // facing the camera
                for (int i = 0; i < 3; i++)
                {
                    transformed.p[i] = rotZ * triangle.p[i];
                    transformed.p[i] = (camera.projection() * (rotX * transformed.p[i]));
                    transformed.p[i] = transformed.p[i] + screen_center;
                }
                draw_triangle(renderer, transformed);
            }
        }

        // Update the display
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Delay(40);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
