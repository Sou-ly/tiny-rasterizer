#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "maths.hpp"

namespace trz
{
    std::vector<std::string> split(std::string &s, std::string delimiter);

    bool load(trz::mesh &object, std::ifstream infile);
}