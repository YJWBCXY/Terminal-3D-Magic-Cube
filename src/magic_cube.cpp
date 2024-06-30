#include "magic_cube.hpp"



Magic_cube::Magic_cube(double size) {
    double psize = size / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                // if (i == 1 && j == 1 && k == 1) {
                //     continue;
                // }
                Cube cube = Cube(psize);

                double x = 0, y = 0, z = 0;


                if (k == 0) {
                    x -= psize;
                } else if (k == 2) {
                    x += psize;
                }
                if (j == 0) {
                    y -= psize;
                } else if (j == 2) {
                    y += psize;
                }
                if (i == 0) {
                    z -= psize;
                } else if (i == 2) {
                    z += psize;
                }

                cube.pmove(x, y, z);

                cubes.push_back(cube);
            }
        }
    }
}

void Magic_cube::rotate_x(double angle) {
    for (Cube& cube : cubes) {
        cube.rotate_x(angle);
    }
}
void Magic_cube::rotate_y(double angle) {
    for (Cube& cube : cubes) {
        cube.rotate_y(angle);
    }
}
void Magic_cube::rotate_z(double angle) {
    for (Cube& cube : cubes) {
        cube.rotate_z(angle);
    }
}

void Magic_cube::protate_x(double angle) {
    for (Cube& cube : cubes) {
        cube.protate_x(angle);
    }
}
void Magic_cube::protate_y(double angle) {
    for (Cube& cube : cubes) {
        cube.protate_y(angle);
    }
}
void Magic_cube::protate_z(double angle) {
    for (Cube& cube : cubes) {
        cube.protate_z(angle);
    }
}

void Magic_cube::srotate_x(double angle) {
    for (Cube& cube : cubes) {
        cube.srotate_x(angle);
    }
}
void Magic_cube::srotate_y(double angle) {
    for (Cube& cube : cubes) {
        cube.srotate_y(angle);
    }
}
void Magic_cube::srotate_z(double angle) {
    for (Cube& cube : cubes) {
        cube.srotate_z(angle);
    }
}

void Magic_cube::pi_2_rotate() {
    for (Cube& cube : cubes) {
        cube.pi_2_rotate();
    }
}

void Magic_cube::move(double x, double y, double z) {
    for (Cube& cube : cubes) {
        cube.move(x, y, z);
    }
}
void Magic_cube::pmove(double x, double y, double z) {
    for (Cube& cube : cubes) {
        cube.pmove(x, y, z);
    }
}

void Magic_cube::draw(Canvas& canvas) {
    for (Cube& cube : cubes) {
        cube.draw(canvas);
    }
}

void Magic_cube::scramble() {
    tmp_angle += step;
    if (tmp_angle > M_PI_2) {
        std::vector<Cube> tmp_cubes;
        tmp_cubes.assign(cubes.begin(), cubes.end());
        tmp_angle = 0;
        for (int z = 0; z < 3; z++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    int index = x + y * 3 + z * 9;
                    if (z == 0) {
                        int tmp = cubes[index].get_pi_2_rotation_z();
                        tmp++;
                        cubes[index].set_pi_2_rotation_z(tmp);

                        tmp_cubes[y + (3 - 1 - x) * 3 + z * 9] = cubes[index];
                        // continue;
                    }
                    // tmp_cubes[index] = cubes[index];
                }
            }
        }
        cubes.assign(tmp_cubes.begin(), tmp_cubes.end());
    }
    for (int z = 0; z < 3; z++) {
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (z == 0) {
                    cubes[x + y * 3 + z * 9].srotate_z(tmp_angle);
                }
            }
        }
    }
}