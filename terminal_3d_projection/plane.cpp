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

// Plane::Plane(double size_x, double size_y, double z_offset) {
//     SIZE_X = size_x / RESOLUTION, SIZE_Y = size_y / RESOLUTION;
//     SIZE = SIZE_X * SIZE_Y;
//     initial_points_x.resize(SIZE);
//     initial_points_y.resize(SIZE);
//     initial_points_z.resize(SIZE);
//     for (int y = 0; y < SIZE_Y; y++) {
//         for (int x = 0; x < SIZE_X; x++) {
//             int o = x + SIZE_X * y;
//             initial_points_x[o] = x * RESOLUTION - RESOLUTION * SIZE_X / 2;
//             initial_points_y[o] = y * RESOLUTION - RESOLUTION * SIZE_Y / 2;
//             initial_points_z[o] = z_offset;
//         }
//     }
// }

void Plane::rotate_x(double angle) {
    rotation_x += angle;
    double sin_alpha = sin(rotation_x), cos_alpha = cos(rotation_x);
    for (int i = 0; i < SIZE; i++) {
        points_x[i] = initial_points_x[i];
        points_y[i] =
            initial_points_y[i] * cos_alpha - initial_points_z[i] * sin_alpha;
        points_z[i] =
            initial_points_y[i] * sin_alpha + initial_points_z[i] * cos_alpha;
    }
}
