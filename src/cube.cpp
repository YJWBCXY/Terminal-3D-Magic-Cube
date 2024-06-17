#include <vector>

#include "cube.hpp"
#include "plane.hpp"

Cube::Cube(double size) {
    for (int i = 0; i < 6; i++) {
        Plane plane = Plane(size, size / 2, i);
        switch (i) {
            case 0:
                plane.colour = RED;
                break;
            case 1:
                plane.colour = MAGENTA;
                break;
            case 2:
                plane.colour = GREEN;
                break;
            case 3:
                plane.colour = BLUE;
                break;
            case 4:
                plane.colour = WHITE;
                break;
            case 5:
                plane.colour = YELLOW;
                break;
        }
        planes.push_back(plane);
    }
}

std::vector<double> Cube::get_points(std::vector<double>& points_x,
                                     std::vector<double>& points_y,
                                     std::vector<double>& points_z) {
    points_x.clear();
    points_y.clear();
    points_z.clear();
    std::vector<double> dot_product;

    for (Plane plane : planes) {
        plane.calculate_dot_product();
        points_x.insert(points_x.end(),
                        plane.points_x.begin(),
                        plane.points_x.end());
        points_y.insert(points_y.end(),
                        plane.points_y.begin(),
                        plane.points_y.end());
        points_z.insert(points_z.end(),
                        plane.points_z.begin(),
                        plane.points_z.end());
        int size = plane.points_x.size();
        for (int i = 0; i < size; i++) {
            dot_product.push_back(plane.dot_product);
            colour.push_back(plane.colour);
        }
    }
    return dot_product;
}

void Cube::rotate_x(double angle) {
    for (Plane& plane : planes) {
        plane.rotate_x(angle);
    }
}
void Cube::rotate_y(double angle) {
    for (Plane& plane : planes) {
        plane.rotate_y(angle);
    }
}
void Cube::rotate_z(double angle) {
    for (Plane& plane : planes) {
        plane.rotate_z(angle);
    }
}

void Cube::protate_x(double angle) {
    for (Plane& plane : planes) {
        plane.protate_x(angle);
    }
}
void Cube::protate_y(double angle) {
    for (Plane& plane : planes) {
        plane.protate_y(angle);
    }
}
void Cube::protate_z(double angle) {
    for (Plane& plane : planes) {
        plane.protate_z(angle);
    }
}

void Cube::move(double x, double y, double z) {
    for (Plane& plane : planes) {
        plane.move(x, y, z);
    }
}

void Cube::pmove(double x, double y, double z) {
    for (Plane& plane : planes) {
        plane.pmove(x, y, z);
    }
}

void Cube::draw(Canvas& canvas) {
    for (Plane& plane : planes) {
        plane.calculate_dot_product();
        plane.draw(canvas);
    }
}

void Cube::clear() {
    for (Plane& plane : planes) {
        plane.clear();
    }
}