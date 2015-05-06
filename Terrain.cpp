/* 
 * File:   Terrain.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 5, 2015, 10:25 PM
 */

#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/freeglut_std.h>

#include "Terrain.hpp"

using namespace std;

Terrain::Terrain() {
    for (int x = 0; x < 4096; x++) {
        for (int y = 0; y < 4096; y++) {
            terrain[x][y] = rand();
            terrain[x][y] /= 256;
        }
    }
    for (int times = 0; times < 2; times++) {
        for (int x = 0; x < 4096; x++) {
            for (int y = 0; y < 4096; y++) {
                double d =
                        (
                        (double) getTerrain(x, y)+
                        (double) getTerrain(x + 1, y)+
                        (double) getTerrain(x - 1, y)+
                        (double) getTerrain(x, y + 1)+
                        (double) getTerrain(x, y - 1)+
                        (double) getTerrain(x + 1, y + 1)+
                        (double) getTerrain(x + 1, y - 1)+
                        (double) getTerrain(x - 1, y + 1)+
                        (double) getTerrain(x - 1, y - 1)
                        ) / 9.0;
                this->setTerrain((unsigned short int) d, x, y);
            }
        }
    }
}

Terrain::Terrain(const Terrain& orig) {
}

Terrain::~Terrain() {
}

unsigned short int Terrain::getTerrain(int x, int y) {
    if (x >= 0 && y >= 0 && x < 4096 && y < 4096)
        return terrain[x][y];
    else
        return 0;
}

void Terrain::setTerrain(unsigned short int value, int x, int y) {
    if (x >= 0 && y >= 0 && x < 4096 && y < 256)
        terrain[x][y] = value;
}

void Terrain::render() {
    int width = glutGet(GLUT_WINDOW_WIDTH)/5;
    int height = glutGet(GLUT_WINDOW_HEIGHT)/5;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float light;
            glBegin(GL_QUADS);
            {
                light = this->getTerrain(x, y)/256.0f;
                glColor3f(light, light, light);
                glVertex2f(x * 5, y * 5);
                glTexCoord2f(0, 0);

                light = this->getTerrain(x + 1, y)/256.0f;
                glColor3f(light, light, light);
                glVertex2f(x * 5 + 5, y * 5);
                glTexCoord2f(1, 0);

                light = this->getTerrain(x + 1, y + 1)/256.0f;
                glColor3f(light, light, light);
                glVertex2f(x * 5 + 5, y * 5 + 5);
                glTexCoord2f(1, 1);

                light = this->getTerrain(x, y + 1)/256.0f;
                glColor3f(light, light, light);
                glVertex2f(x * 5, y * 5 + 5);
                glTexCoord2f(0, 1);
            }
            glEnd();
        }
    }
}

