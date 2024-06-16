#include <string>
#include <vector>

#include "canvas.hpp"
#include "definitions.h"

Canvas::Canvas(const int size_x, const int size_y) {
    size = size_x * size_y;
    for (int i = 0; i < size; i++) {
        if (i % size_x == size_x - 1) {
            canvas.push_back('\n');
        } else {
            canvas.push_back(' ');
        }
        canvas_colours.push_back(WHITE);
    }
}

void Canvas::set(int index, char _char) {
    canvas[index] = _char;
}
void Canvas::set(int index, char _char, std::string colour) {
    canvas[index] = _char;
    canvas_colours[index] = colour;
}

std::string Canvas::to_string() {
    std::string _string;
    for (int i = 0; i < size; i++) {
        _string += canvas_colours[i];
        _string.push_back(canvas[i]);
    }
    return _string;
}