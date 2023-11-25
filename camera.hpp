#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>

#include "maths.hpp"

namespace trz {

    class camera {
        public:
            void set_position(vec3 position);
            void set_direction(vec3 direction);
            void set_orthographic_projection(float near, float far, float left, float right, float top, float bottom);
            void set_perspective_projection(float field_of_view, float near, float far);
            vec3 position();
            vec3 direction();
            mat4 projection();
            mat4 view();
        private:
            vec3 pos;
            vec3 dir;
            mat4 projMatrix;
            mat4 viewMatrix;
    };
}