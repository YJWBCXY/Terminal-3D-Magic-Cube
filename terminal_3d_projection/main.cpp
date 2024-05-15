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

#define RX 80
#define RY 69

#define R1 1
#define R2 2

// #define K1 88 //23:27 //46:58 //69:88
#define K2 R1 + R2 * 2


std::string torus(const int& terminal_x,
                  const int& terminal_y,
                  double& rotation_x,
                  double& rotation_z) {
    double k1;
    {
        int x = std::min(terminal_x, terminal_y);
        k1 = -0.001 * x * x + 1.413 * x - 5;
    }
    std::string print_buffer;
    std::vector<double> z_buffer;
    rotation_x += 0.07;
    rotation_z += 0.03;
    double cos_rx = cos(rotation_x), sin_rx = sin(rotation_x);
    double cos_rz = cos(rotation_z), sin_rz = sin(rotation_z);

    for (int i = 0; i < terminal_x * terminal_y; i++) {
        if (i % terminal_x == terminal_x - 1) {
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
            double circle_x = cos_theta * R1 + R2, circle_y = sin_theta * R1;
            double inverse_z = 1 / (sin_phi * circle_x * sin_rx +
                                    circle_y * cos_rx + K2); //  1/z
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

void ascii_frame() {
    double rotation_x = 0, rotation_z = 0;
    int terminal_x = RX, terminal_y = RY;

    while (true) {
#if defined(__linux__) || defined(__APPLE__)
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        terminal_x = w.ws_col;
        terminal_y = w.ws_row;
#elif defined(_WIN32)
        // untested
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        terminal_x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        terminal_y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#endif

        std::string print_buffer;

        print_buffer = torus(terminal_x, terminal_y, rotation_x, rotation_z);

        std::cout << print_buffer;
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
    }
}

int main() {
    ascii_frame();
    return 0;
}