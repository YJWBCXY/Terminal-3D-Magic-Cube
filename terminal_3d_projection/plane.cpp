#include <cmath>
#include <vector>

#include "plane.hpp"


Plane::Plane(double size, double z_offset) {
    SIZE_X = size / RESOLUTION, SIZE_Y = size / RESOLUTION;
    SIZE = SIZE_X * SIZE_Y;
    initial_points_x.resize(SIZE);
    initial_points_y.resize(SIZE);
    initial_points_z.resize(SIZE);
    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++) {
            int o = x + SIZE_X * y;
            initial_points_x[o] = x * RESOLUTION - RESOLUTION * SIZE_X / 2;
            initial_points_y[o] = y * RESOLUTION - RESOLUTION * SIZE_Y / 2;
            initial_points_z[o] = -z_offset;
        }
    }
    clear();
}

void Plane::rotate_x(double angle, double& y, double& z) {
    double sin_alpha = sin(angle), cos_alpha = cos(angle);
    double tmp_y = y;
    y = y * cos_alpha - z * sin_alpha;
    z = tmp_y * sin_alpha + z * cos_alpha;
}
void Plane::rotate_y(double angle, double& x, double& z) {
    double sin_beta = sin(angle), cos_beta = cos(angle);
    double tmp_x = x;
    x = tmp_x * cos_beta + z * sin_beta;
    z = -tmp_x * sin_beta + z * cos_beta;
}
void Plane::rotate_z(double angle, double& x, double& y) {
    double sin_gamma = sin(angle), cos_gamma = cos(angle);
    double tmp_x = x;
    x = tmp_x * cos_gamma - y * sin_gamma;
    y = tmp_x * sin_gamma + y * cos_gamma;
}

void Plane::calculate_dot_product() {
    dot_product = 0;
    for (int i = 0; i < 3; i++) {
        dot_product += normal[i] * view[i];
    }
}

void Plane::rotate_x(double angle) {
    rotation_x += angle;
    for (int i = 0; i < SIZE; i++) {
        rotate_x(rotation_x, points_y[i], points_z[i]);
    }
    rotate_x(rotation_x, normal[1], normal[2]);
}
void Plane::rotate_y(double angle) {
    rotation_y += angle;
    for (int i = 0; i < SIZE; i++) {
        rotate_y(rotation_y, points_x[i], points_z[i]);
    }
    rotate_y(rotation_y, normal[0], normal[2]);
}
void Plane::rotate_z(double angle) {
    rotation_z += angle;
    for (int i = 0; i < SIZE; i++) {
        rotate_y(rotation_z, points_x[i], points_y[i]);
    }
    rotate_z(rotation_z, normal[0], normal[1]);
}

void Plane::protate_x(double angle) {
    for (int i = 0; i < SIZE; i++) {
        rotate_x(angle, initial_points_y[i], initial_points_z[i]);
    }
    rotate_x(initial_normal[0], initial_normal[1], initial_normal[2]);
}
void Plane::protate_y(double angle) {
    for (int i = 0; i < SIZE; i++) {
        rotate_y(angle, initial_points_x[i], initial_points_z[i]);
    }
    rotate_y(initial_normal[0], initial_normal[1], initial_normal[2]);
}
void Plane::protate_z(double angle) {
    for (int i = 0; i < SIZE; i++) {
        rotate_z(angle, initial_points_x[i], initial_points_y[i]);
    }
    rotate_z(initial_normal[0], initial_normal[1], initial_normal[2]);
}

void Plane::move(double x, double y, double z) {
    for (int i = 0; i < SIZE; i++) {
        points_x[i] += x;
        points_y[i] += y;
        points_z[i] += z;
    }
}
void Plane::pmove(double x, double y, double z) {
    for (int i = 0; i < SIZE; i++) {
        initial_points_x[i] += x;
        initial_points_y[i] += y;
        initial_points_z[i] += z;
    }
}

void Plane::clear() {
    points_x = initial_points_x;
    points_y = initial_points_y;
    points_z = initial_points_z;
    for (int i = 0; i < 3; i++) {
        normal[i] = initial_normal[i];
    }
}