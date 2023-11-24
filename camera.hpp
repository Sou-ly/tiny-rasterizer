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
            void set_perspective_projection(float field_of_view, float aspect_ratio, float near, float far);
            mat4 projection();
        private:
            mat4 proj;
    };
}