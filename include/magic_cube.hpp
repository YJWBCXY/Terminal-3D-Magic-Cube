#pragma once

#if defined(_WIN32)
    #define _USE_MATH_DEFINES
    #include <cmath>
#endif

#include <vector>

#include "cube.hpp"

class Magic_cube {
    private:
    std::vector<Cube> cubes;
    double tmp_angle = 0, step = 0.04;

    public:
    Magic_cube(double size);

    void rotate_x(double angle);
    void rotate_y(double angle);
    void rotate_z(double angle);

    void protate_x(double angle);
    void protate_y(double angle);
    void protate_z(double angle);

    void srotate_x(double angle);
    void srotate_y(double angle);
    void srotate_z(double angle);

    void pi_2_rotate();

    void move(double x, double y, double z);
    void pmove(double x, double y, double z);

    void draw(Canvas& canvas);

    int get_pi_2_rotation_x();
    int get_pi_2_rotation_y();
    int get_pi_2_rotation_z();

    void set_pi_2_rotation_x(int value);
    void set_pi_2_rotation_y(int value);
    void set_pi_2_rotation_z(int value);

    void scramble();
};