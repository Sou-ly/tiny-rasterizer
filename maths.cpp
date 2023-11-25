#include "maths.hpp"

namespace trz
{
    vec3 normalizeVec(vec3 vec)
    {
        vec3 res;
        float norm = std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2) + std::pow(vec.z, 2));
        if (norm != 0.f)
        {
            res.x = vec.x / norm;
            res.y = vec.y / norm;
            res.z = vec.z / norm;
        }
        return res;
    }
}