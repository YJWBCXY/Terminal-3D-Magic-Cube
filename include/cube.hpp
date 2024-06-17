#pragma once

#include <vector>

#include "canvas.hpp"
#include "plane.hpp"

class Cube {
    private:
    std::vector<Plane> planes;

    public:
    Cube(double size);
    std::vector<std::string> colour;
    std::vector<double> get_points(std::vector<double>& points_x,
                                   std::vector<double>& points_y,
                                   std::vector<double>& points_z);

    void rotate_x(double angle);
    void rotate_y(double angle);
    void rotate_z(double angle);

    void protate_x(double angle);
    void protate_y(double angle);
    void protate_z(double angle);

    void move(double x, double y, double z);
    void pmove(double x, double y, double z);

    void draw(Canvas& canvas);

    void clear();
};