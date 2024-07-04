#if defined(_WIN32)
    #define _USE_MATH_DEFINES
#endif

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <thread>
#include <vector>

#if defined(__linux__) || defined(__APPLE__)
    #include <stdio.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif

#include "canvas.hpp"
#include "cube.hpp"
#include "definitions.h"
#include "magic_cube.hpp"
#include "plane.hpp"

#define RX 80
#define RY 24

#define R1 1
#define R2 2

#define PLANE_STEP 0.0145


void blank_canvas(const int& terminal_x,
                  const int& terminal_y,
                  std::string& print_buffer,
                  std::vector<double>& z_buffer) {
    for (int i = 0; i < terminal_x * terminal_y; i++) {
        if (i % terminal_x == terminal_x - 1) {
            print_buffer.push_back('\n');
        } else {
            print_buffer.push_back(' ');
        }
        z_buffer.push_back(0.0);
    }
}

std::string torus_draw(const int& terminal_x,
                       const int& terminal_y,
                       double& rotation_x,
                       double& rotation_z,
                       const int& r1,
                       const int& r2) {
    double k1;
    {
        int x = (std::min)(terminal_x, terminal_y);
        k1 = -0.001 * x * x + 1.413 * x - 5;
    }
    std::string print_buffer;
    std::vector<double> z_buffer;
    rotation_x += 0.07;
    rotation_z += 0.03;
    double cos_rx = cos(rotation_x), sin_rx = sin(rotation_x);
    double cos_rz = cos(rotation_z), sin_rz = sin(rotation_z);
    int k2 = r1 + r2 * 2;

    blank_canvas(terminal_x, terminal_y, print_buffer, z_buffer);

    for (double theta = 0; theta < 2 * M_PI; theta += 0.07) {
        double cos_theta = cos(theta), sin_theta = sin(theta);
        for (double phi = 0; phi < 2 * M_PI; phi += 0.02) {
            double cos_phi = cos(phi), sin_phi = sin(phi);
            double circle_x = cos_theta * r1 + r2, circle_y = sin_theta * r1;
            double inverse_z = 1 / (sin_phi * circle_x * sin_rx +
                                    circle_y * cos_rx + k2); //  1/z
            double t = sin_phi * circle_x * cos_rx - sin_theta * sin_rx;

            int x = (int)(terminal_x / 2 +
                          k1 * inverse_z *
                              (cos_phi * circle_x * cos_rz - t * sin_rz)),
                y = (int)(terminal_y / 1.95 + // 1.95 Good enough for now
                          (k1 / 2) * inverse_z *
                              (cos_phi * circle_x * sin_rz + t * cos_rz));
            double o = x + terminal_x * y;
            int normal =
                (int)(8 * ((sin_theta * sin_rx - sin_phi * cos_theta * cos_rx) *
                               cos_rz -
                           sin_phi * cos_theta * sin_rx - sin_theta * cos_rx -
                           cos_phi * cos_theta * sin_rz));
            if (y < terminal_y && y >= 0 && x >= 0 && x <= terminal_x - 1 &&
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
    return print_buffer;
}

std::string plane_draw(const int& terminal_x,
                       const int& terminal_y,
                       double& rotation_x,
                       double& rotation_z,
                       Plane& square) {
    double a = 3;
    double k1;
    {
        int x = (std::min)(terminal_x, terminal_y);
        // k1 = -0.001 * x * x + 1.413 * x - 5;
        k1 = 28;
    }
    std::string print_buffer;
    std::vector<double> z_buffer;
    int k2 = a * 1.5;
    double ha = a / 2;

    blank_canvas(terminal_x, terminal_y, print_buffer, z_buffer);

    square.rotate_x(0.03);
    square.calculate_dot_product();

    for (int point = 0; point < square.SIZE; point++) {
        double inverse_z = 1 / ((square.points_z[point]) + k2);

        int px = (int)(terminal_x / 2 +
                       k1 * inverse_z * (square.points_x[point])),
            py = (int)(terminal_y / 1.95 +
                       (k1 / 2) * inverse_z * (square.points_y[point]));

        int o = px + terminal_x * py;

        int normal = (int)(8 * (square.dot_product));
        if (py < terminal_y && py >= 0 && px >= 0 && px <= terminal_x - 1 &&
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
    return print_buffer;
}

void cube_draw(const int& terminal_x,
               const int& terminal_y,
               Cube& cube,
               Canvas& canvas) {
    cube.move(0, -1, 0);
    cube.rotate_x(0.03);
    // cube.rotate_y(0.07);

    cube.draw(canvas);

    // cube.clear();
}

void magic_cube_draw(const int& terminal_x,
                     const int& terminal_y,
                     Magic_cube& magic_cube,
                     Canvas& canvas) {
    magic_cube.pi_2_rotate();
    magic_cube.scramble();
    magic_cube.rotate_y(0.02);
    magic_cube.rotate_x(0.01);
    magic_cube.draw(canvas);
}


void ascii_frame() {
    double rotation_x = 0, rotation_z = 0;
    int terminal_x = RX, terminal_y = RY;
    // Plane square = Plane(3, 1.5, PR_FRONT);
    Cube cube = Cube(3);
    Magic_cube magic_cube = Magic_cube(3);


    // magic_cube.protate_y(M_PI_2);
    // magic_cube.pmove(0, 2, 0);

    while (true) {
#if defined(__linux__) || defined(__APPLE__)
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        terminal_x = w.ws_col;
        terminal_y = w.ws_row;
#elif defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        terminal_x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        terminal_y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#endif

        Canvas canvas = Canvas(terminal_x, terminal_y);

        // cube_draw(terminal_x, terminal_y, cube, canvas);
        magic_cube_draw(terminal_x, terminal_y, magic_cube, canvas);

        // print_buffer =
        // plane_draw(terminal_x, terminal_y, rotation_x, rotation_z, square);
        // torus_draw(terminal_x, terminal_y, rotation_x, rotation_z, R1, R2);

        std::cout << canvas.to_string();
        canvas.clear();

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}

int main() {
#if defined(_WIN32)
    system("color");
#endif

    ascii_frame();
    return 0;
}