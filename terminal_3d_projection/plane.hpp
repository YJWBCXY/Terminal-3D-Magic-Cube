#pragma once
#include <vector>

class Plane {
    private:
    int SIZE_X, SIZE_Y;
    double RESOLUTION = 0.0145;
    double rotation_x = 0, rotation_y = 0, rotation_z = 0;
    std::vector<double> initial_points_x, initial_points_y, initial_points_z;

    public:
    int SIZE;
    std::vector<double> points_x, points_y, points_z;

    private:
    void rotate_x(double angle, double& y, double& z);
    void rotate_y(double angle, double& x, double& z);
    void rotate_z(double angle, double& x, double& y);

    public:
    Plane(double size, double z_offset);
    // Plane(double size_x, double size_y, double z_offset);
    // Plane(double size_x, double size_y, double z_offset, int direction);

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