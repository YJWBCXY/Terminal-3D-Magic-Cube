#pragma once

#include <vector>

#include "canvas.hpp"
#include "plane.hpp"

class Cube {
    private:
    std::vector<Plane> planes;
    double SIZE;

    public:
    std::vector<std::string> colour;
    std::vector<double> get_points(std::vector<double>& points_x,
                                   std::vector<double>& points_y,
                                   std::vector<double>& points_z);
    int no;

    public:
    Cube(double size);

    void rotate_x(double angle);
    void rotate_y(double angle);
    void rotate_z(double angle);

    void protate_x(double angle);
    void protate_y(double angle);
    void protate_z(double angle);

    void srotate_x(double angle);
    void srotate_y(double angle);
    void srotate_z(double angle);

    void crotate_x(bool reverse);
    void crotate_y(bool reverse);
    void crotate_z(bool reverse);

    void pi_2_rotate();

    void move(double x, double y, double z);
    void pmove(double x, double y, double z);

    void draw(Canvas& canvas);

    void clear();

    void colour_transfer(Cube& cube);

    // TODO: clean it
    int get_pi_2_rotation_x();
    int get_pi_2_rotation_y();
    int get_pi_2_rotation_z();

    void set_pi_2_rotation_x(int value);
    void set_pi_2_rotation_y(int value);
    void set_pi_2_rotation_z(int value);
};