#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

namespace trz {
    
    struct vec3 {
        float x, y, z;

        vec3 operator + (vec3 vec) {
            vec3 res;
            res.x = x + vec.x;
            res.y = y + vec.y;
            res.z = z + vec.z;
            return res;
        }

        vec3 operator * (float scale) {
            vec3 res;
            res.x = x * scale;
            res.y = y * scale;
            res.z = z * scale;
            return res;
        }
    };

    vec3 normalizeVec(vec3 vec);

    struct mat3 {
        float m[3][3];

        vec3 operator * (vec3 vec) {
            vec3 res;
            res.x = vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2];
            res.y = vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2];
            res.z = vec.x * m[2][0] + vec.y * m[2][1] + vec.z * m[2][2];
            return res;
        }

        mat3 operator * (mat3 mat) {
            mat3 res; 
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    float temp = 0;
                    for (int k = 0; k < 3; k++) {
                        temp += m[i][j] * mat.m[j][k];
                    }
                    res.m[i][j] = temp;
                }
            }
            return res;
        }
    };

    struct mat4 {
        float m[4][4];

        vec3 operator * (vec3 vec) {
            vec3 res;
            res.x = vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2] + m[0][3];
            res.y = vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2] + m[1][3];
            res.z = vec.x * m[2][0] + vec.y * m[2][1] + vec.z * m[2][2] + m[2][3];
            float w = vec.x * m[3][0] + vec.y * m[3][1] + vec.z * m[3][2] + m[3][3];

            if (w != 0) {
                res.x /= w;
                res.y /= w;
                res.z /= w;
            } 

            return res;
        }
    };

    struct triangle {
        vec3 p[3];
        vec3 normal;
    };

    struct mesh {
        std::vector<triangle> tris;
    };

}