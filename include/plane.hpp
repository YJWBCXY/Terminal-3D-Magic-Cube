#pragma once

#if defined(_WIN32)
    #define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <vector>

#include "canvas.hpp"
#include "definitions.h"

class Plane {
    private:
    int SIZE_X, SIZE_Y;
    double A;
    double RESOLUTION = 0.05;
    double rotation_x = 0, rotation_y = 0, rotation_z = 0;
    std::vector<double> initial_points_x, initial_points_y, initial_points_z;
    double initial_normal[3] = {0, 0, 0}; // x, y, z
    int pi_2_rotation_x = 0, pi_2_rotation_y = 0, pi_2_rotation_z = 0;

    public:
    int SIZE;
    std::vector<double> points_x, points_y, points_z;
    double normal[3] = {0, 0, 0}; // x, y, z
    double view[3] = {0, 1, 1};   // x, y, z
    double dot_product;
    std::string colour = WHITE;

    private:
    void rotate_x(double angle, double& y, double& z);
    void rotate_y(double angle, double& x, double& z);
    void rotate_z(double angle, double& x, double& y);

    public:
    Plane(double size, double z_offset);
    Plane(double size, double z_offset, int direction);
    void calculate_dot_product();

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

    void clear();

    int get_pi_2_rotation_x();
    int get_pi_2_rotation_y();
    int get_pi_2_rotation_z();

    void set_pi_2_rotation_x(int value);
    void set_pi_2_rotation_y(int value);
    void set_pi_2_rotation_z(int value);
};