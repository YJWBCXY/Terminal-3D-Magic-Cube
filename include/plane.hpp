#pragma once
#include <vector>

class Plane {
    private:
    int SIZE_X, SIZE_Y;
    double RESOLUTION = 0.0145;
    double rotation_x = 0, rotation_y = 0, rotation_z = 0;
    std::vector<double> initial_points_x, initial_points_y, initial_points_z;
    double initial_normal[3] = {0, 0, 0}; // x, y, z

    public:
    int SIZE;
    std::vector<double> points_x, points_y, points_z;
    double normal[3] = {0, 0, 0}; // x, y, z
    double view[3] = {0, 1, 1};   // x, y, z
    double dot_product;

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

    void move(double x, double y, double z);
    void pmove(double x, double y, double z);

    void clear();
};