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
            void set_orthographic_projection(float near, float far, float left, float right, float top, float bottom);
            void set_perspective_projection(float field_of_view, float near, float far);
            mat4 projection();
            mat4 view();
        private:
            mat4 projMatrix;
            mat4 viewMatrix;
    };
}