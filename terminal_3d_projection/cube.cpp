#include <vector>

#include "cube.hpp"
#include "plane.hpp"

Cube::Cube(double size) {
    for (int i = 0; i < 6; i++) {
        planes.push_back(Plane(size, size / 2, i));
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
        }
    }
    return dot_product;
}

void Cube::rotate_x(double angle) {
    for (Plane &plane : planes){
        plane.rotate_x(angle);
    }
}
void Cube::rotate_y(double angle) {
        for (Plane &plane : planes){
        plane.rotate_y(angle);
    }
}
void Cube::rotate_z(double angle) {
        for (Plane &plane : planes){
        plane.rotate_z(angle);
    }
}


void Cube::clear() {
        for (Plane &plane : planes){
        plane.clear();
    }
}