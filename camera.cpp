#include "camera.hpp"

namespace trz
{
    void camera::set_orthographic_projection(float left, float right, float top, float bottom, float near, float far)
    {
        proj = {{0}};
        proj.m[0][0] = 2.f / (right - left);
        proj.m[0][3] = -(right + left) / (right - left);
        proj.m[1][1] = 2.f / (top - bottom);
        proj.m[1][3] = -(top + bottom) / (top - bottom);
        proj.m[2][2] = -2.f / (far - near);
        proj.m[2][3] = -(far + near) / (far - near);
        proj.m[3][3] = 1.f;
    }

    void camera::set_perspective_projection(float field_of_view, float aspect_ratio, float near, float far)
    {
        proj = {{0}};
        float half_fov = field_of_view / 2;
        proj.m[0][0] = 1.f / (aspect_ratio * tan(half_fov));
        proj.m[1][1] = 1.f / (tan(half_fov));
        proj.m[2][2] = far / (far - near);
        proj.m[2][3] = -near * far / (far - near);
        proj.m[2][3] = 1.f;
    }

    mat4 camera::projection() {
        return proj;
    }
} // namespace trz