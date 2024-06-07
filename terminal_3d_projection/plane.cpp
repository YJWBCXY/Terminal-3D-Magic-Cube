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
            initial_points_z[o] = z_offset;
        }
    }
    points_x = initial_points_x;
    points_y = initial_points_y;
    points_z = initial_points_z;
}

void Plane::rotate_x(double angle) {
    rotation_x += angle;
    double sin_alpha = sin(rotation_x), cos_alpha = cos(rotation_x);
    for (int i = 0; i < SIZE; i++) {
        double tpm_y = points_y[i];
        points_y[i] = tpm_y * cos_alpha - points_z[i] * sin_alpha;
        points_z[i] = tpm_y * sin_alpha + points_z[i] * cos_alpha;
    }
}

void Plane::rotate_y(double angle) {
    rotation_y += angle;
    double sin_beta = sin(rotation_y), cos_beta = cos(rotation_y);
    for (int i = 0; i < SIZE; i++) {
        double tpm_x = points_x[i];
        points_x[i] = tpm_x * cos_beta + points_z[i] * sin_beta;
        points_z[i] = -tpm_x * sin_beta + points_z[i] * cos_beta;
    }
}

void Plane::rotate_z(double angle) {
    rotation_z += angle;
    double sin_gamma = sin(rotation_z), cos_gamma = cos(rotation_z);
    for (int i = 0; i < SIZE; i++) {
        double tpm_x = points_x[i];
        points_x[i] = tpm_x * cos_gamma - points_y[i] * sin_gamma;
        points_y[i] = tpm_x * sin_gamma + points_y[i] * cos_gamma;
    }
}

void Plane::clear() {
    points_x = initial_points_x;
    points_y = initial_points_y;
    points_z = initial_points_z;
}