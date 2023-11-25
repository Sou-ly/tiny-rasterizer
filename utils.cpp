#include "utils.hpp"

namespace trz
{
    std::vector<std::string> split(std::string &s, std::string delimiter)
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
        {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }

    bool load(trz::mesh &object, std::ifstream infile)
    {
        if (!infile.is_open())
        {
            return false;
        }

        std::string line;
        std::vector<vec3> vertices;
        std::vector<vec3> normals;
        std::vector<vec3> texture;
        while (std::getline(infile, line))
        {
            std::vector<std::string> s = split(line, " ");

            if (s[0][0] == 'v')
            {
                vec3 vertex{strtof(s[1].c_str(), NULL), strtof(s[2].c_str(), NULL), strtof(s[3].c_str(), NULL)};
                if (s[0][1] == 'n')
                {
                    normals.push_back(vertex);
                }
                else if (s[0][1] == 't')
                {
                    vertices.push_back(vertex);
                }
                else
                {
                    vertices.push_back(vertex);
                }
            }
            else if (s[0] == "f")
            {
                triangle triangle;
                triangle.normal = {0};
                for (int i = 0; i < 3; i++)
                {
                    std::vector<std::string> indices = split(s[1 + i], "/");
                    triangle.p[i] = vertices[strtof(indices[0].c_str(), NULL) - 1];
                    // TODO: texture
                    // TODO: for now we average the normals (flat shading)
                    triangle.normal = triangle.normal + normals[strtof(indices[2].c_str(), NULL) - 1];
                }
                triangle.normal = normalizeVec(triangle.normal);
                object.tris.push_back(triangle);
            }
        }

        return true;
    }
} // namespace trz
