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

void Magic_cube::draw(Canvas& canvas) {
    for (Cube& cube : cubes) {
        cube.draw(canvas);
    }
}