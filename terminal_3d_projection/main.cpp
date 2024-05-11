#include <chrono>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <thread>
#include <vector>

#define RX 80
#define RY 23

void ascii_frame() {
    double A = 1, B = 1;

    while (true) {
        std::string print_buffer;
        std::vector<double> z_buffer;
        A += 0.07;
        B += 0.03;
        double cos_A = cos(A), sin_A = sin(A);
        double cos_B = cos(B), sin_B = sin(B);

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
                double h = cos_theta + 2;
                double D = 1 / (sin_phi * h * sin_A + sin_theta * cos_A + 5);
                double t = sin_phi * h * cos_A - sin_theta * sin_A;

                int x = (int)(40 + 30 * D * (cos_phi * h * cos_B - t * sin_B)),
                    y = (int)(12 + 15 * D * (cos_phi * h * sin_B + t * cos_B));
                double o = x + RX * y;
                int N =
                    (int)(8 *
                          ((sin_theta * sin_A - sin_phi * cos_theta * cos_A) *
                               cos_B -
                           sin_phi * cos_theta * sin_A - sin_theta * cos_A -
                           cos_phi * cos_theta * sin_B));
                if (y < RY && y >= 0 && x >= 0 && x <= RX - 1 &&
                    D > z_buffer[o]) {
                    z_buffer[o] = D;
                    char _char;
                    if (N > 0) {
                        _char = ".,-~:;=!*#$@"[N];
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