#pragma once

#include <string>
#include <vector>

class Canvas {
    private:
    public:
    int size;
    std::vector<char> canvas;
    std::vector<std::string> canvas_colours;

    public:
    Canvas(const int size_x, const int size_y);

    void set(int index, char _char);
    void set(int index, char _char, std::string colour);

    std::string to_string();
};