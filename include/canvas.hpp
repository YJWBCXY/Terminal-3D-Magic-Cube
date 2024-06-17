#pragma once

#include <string>
#include <vector>

class Canvas {
    private:
    public:
    int size, size_x, size_y;
    std::vector<char> canvas;
    std::vector<std::string> canvas_colours;
    std::vector<double> z_buffer;

    public:
    Canvas(const int x, const int y);

    void set(int index, char _char);
    void set(int index, char _char, std::string colour);

    std::string to_string();

    void clear();
};