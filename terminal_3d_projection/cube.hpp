#pragma once

#include <vector>

#include "plane.hpp"

class Cube {
    private:
    std::vector<Plane> planes;

    public:
    Cube(double size);

    std::vector<double> get_points(std::vector<double>& points_x,
                                   std::vector<double>& points_y,
                                   std::vector<double>& points_z);

    void rotate_x(double angle);
    void rotate_y(double angle);
    void rotate_z(double angle);

    void clear();
};