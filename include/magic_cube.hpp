#pragma once

#include <vector>

#include "cube.hpp"

class Magic_cube {
    private:
    std::vector<Cube> cubes;

    public:
    Magic_cube(double size);

    void draw(Canvas& canvas);
};