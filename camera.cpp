#include "camera.hpp"

namespace trz
{
    void camera::set_orthographic_projection(float left, float right, float top, float bottom, float near, float far)
    {
        projMatrix = {{0}};
        projMatrix.m[0][0] = 2.f / (right - left);
        projMatrix.m[0][3] = -(right + left) / (right - left);
        projMatrix.m[1][1] = 2.f / (top - bottom);
        projMatrix.m[1][3] = -(top + bottom) / (top - bottom);
        projMatrix.m[2][2] = -2.f / (far - near);
        projMatrix.m[2][3] = -(far + near) / (far - near);
        projMatrix.m[3][3] = 1.f;
    }

    void camera::set_perspective_projection(float field_of_view, float near, float far)
    {
        projMatrix = {{0}};
        float half_fov = field_of_view / 2 * M_PI / 180;
        projMatrix.m[0][0] = 1.f / (tan(half_fov));
        projMatrix.m[1][1] = 1.f / (tan(half_fov));
        projMatrix.m[2][2] = far / (far - near);
        projMatrix.m[2][3] = -near * far / (far - near);
        projMatrix.m[2][3] = 1.f;
    }

    mat4 camera::projection() {
        return projMatrix;
    }

    mat4 camera::view() {
        return viewMatrix;
    }
} // namespace trz