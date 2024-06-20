#include <cmath>
#include <vector>

#include "definitions.h"
#include "plane.hpp"


Plane::Plane(double size, double z_offset) {
    SIZE_X = size / RESOLUTION, SIZE_Y = size / RESOLUTION;
    SIZE = SIZE_X * SIZE_Y;
    initial_points_x.resize(SIZE);
    initial_points_y.resize(SIZE);
    initial_points_z.resize(SIZE);
    initial_normal[2] = 1;
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

Plane::Plane(double size, double z_offset, int direction) {
    A = size;
    SIZE_X = size / RESOLUTION, SIZE_Y = size / RESOLUTION;
    SIZE = SIZE_X * SIZE_Y;
    initial_points_x.resize(SIZE);
    initial_points_y.resize(SIZE);
    initial_points_z.resize(SIZE);

    std::vector<double>*ptr_1, *ptr_2, *ptr_flat;
    int offset_direction = 1;

    switch (direction) {
        case PR_FRONT:
            ptr_1 = &initial_points_x;
            ptr_2 = &initial_points_y;
            ptr_flat = &initial_points_z;
            offset_direction = -1;
            initial_normal[2] = 1;
            break;
        case PR_BACK:
            ptr_1 = &initial_points_x;
            ptr_2 = &initial_points_y;
            ptr_flat = &initial_points_z;
            initial_normal[2] = -1;
            break;
        case PR_RIGHT:
            ptr_1 = &initial_points_y;
            ptr_2 = &initial_points_z;
            ptr_flat = &initial_points_x;
            initial_normal[0] = -1;
            break;
        case PR_LEFT:
            ptr_1 = &initial_points_y;
            ptr_2 = &initial_points_z;
            ptr_flat = &initial_points_x;
            offset_direction = -1;
            initial_normal[0] = 1;
            break;
        case PR_TOP:
            ptr_1 = &initial_points_x;
            ptr_2 = &initial_points_z;
            ptr_flat = &initial_points_y;
            offset_direction = -1;
            initial_normal[1] = 1;
            break;
        case PR_BOTTOM:
            ptr_1 = &initial_points_x;
            ptr_2 = &initial_points_z;
            ptr_flat = &initial_points_y;
            initial_normal[1] = -1;
            break;
    }

    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++) {
            int o = x + SIZE_X * y;
            ptr_1->at(o) = x * RESOLUTION - RESOLUTION * SIZE_X / 2;
            ptr_2->at(o) = y * RESOLUTION - RESOLUTION * SIZE_Y / 2;
            ptr_flat->at(o) = z_offset * offset_direction;
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

void Plane::draw(Canvas& canvas) {
    double k2 = A * 4;
    double k1 = 30;

    for (int point = 0; point < SIZE; point++) {
        double inverse_z = 1 / ((points_z[point]) + k2);
        int px = (int)(canvas.size_x / 2 + k1 * inverse_z * (points_x[point])),
            py = (int)(canvas.size_y / 1.95 +
                       (k1 / 2) * inverse_z * (points_y[point]));

        int o = px + canvas.size_x * py;
        int normal = (int)(8 * (dot_product));
        if (py < canvas.size_y && py >= 0 && px >= 0 &&
            px <= canvas.size_x - 1 && inverse_z > canvas.z_buffer[o]) {
            canvas.z_buffer[o] = inverse_z;
            char _char;
            if (normal > 0) {
                _char = ".,-~:;=!*#$@"[normal];
            } else {
                _char = '.';
            }
            canvas.set(o, _char, colour);
        }
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