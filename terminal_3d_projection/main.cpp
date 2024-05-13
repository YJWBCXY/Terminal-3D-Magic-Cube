#include <chrono>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <thread>
#include <vector>

#define RX 80
#define RY 23

#define R1 1
#define R2 2

#define K1 125
#define K2 R1 + R2 * 2

void ascii_frame() {
    double rotation_x = 0, rotation_z = 0;

    while (true) {
        std::string print_buffer;
        std::vector<double> z_buffer;
        rotation_x += 0.07;
        rotation_z += 0.03;
        double cos_rx = cos(rotation_x), sin_rx = sin(rotation_x);
        double cos_rz = cos(rotation_z), sin_rz = sin(rotation_z);

        for (int i = 0; i < RX * RY; i++) {
            if (i % RX == RX - 1) {
                print_buffer.push_back('\n');
            } else {
                print_buffer.push_back(' ');
            }
            z_buffer.push_back(0.0);
        }

        for (double theta = 0; theta < 2 * M_PI; theta += 0.07) {
            double cos_theta = cos(theta), sin_theta = sin(theta);
            for (double phi = 0; phi < 2 * M_PI; phi += 0.02) {
                double cos_phi = cos(phi), sin_phi = sin(phi);
                double circle_x = cos_theta * R1 + R2,
                       circle_y = sin_theta * R1;
                double inverse_z = 1 / (sin_phi * circle_x * sin_rx +
                                        circle_y * cos_rx + K2); //  1/z
                double t = sin_phi * circle_x * cos_rx - sin_theta * sin_rx;

                int x = (int)(RX / 2 +
                              K1 * inverse_z *
                                  (cos_phi * circle_x * cos_rz - t * sin_rz)),
                    y = (int)(RY / 2 +
                              (K1 / 2) * inverse_z *
                                  (cos_phi * circle_x * sin_rz + t * cos_rz));
                double o = x + RX * y;
                int normal =
                    (int)(8 *
                          ((sin_theta * sin_rx - sin_phi * cos_theta * cos_rx) *
                               cos_rz -
                           sin_phi * cos_theta * sin_rx - sin_theta * cos_rx -
                           cos_phi * cos_theta * sin_rz));
                if (y < RY && y >= 0 && x >= 0 && x <= RX - 1 &&
                    inverse_z > z_buffer[o]) {
                    z_buffer[o] = inverse_z;
                    char _char;
                    if (normal > 0) {
                        _char = ".,-~:;=!*#$@"[normal];
                    } else {
                        _char = '.';
                    }
                    print_buffer[o] = _char;
                }
            }
        }

        std::cout << print_buffer;
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
    }
}

int main() {
    ascii_frame();
    return 0;
}