/* 
 * File:   Terrain.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 5, 2015, 10:25 PM
 */

#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/freeglut_std.h>

#include "FogOfWar.hpp"
#include "Point.hpp"

using namespace std;

FogOfWar::FogOfWar() {

}

FogOfWar::~FogOfWar() {
}

void FogOfWar::open(int radius, int x, int y) {
    for (int rx = x / 20 - radius; rx <= x / 20 + radius; rx++) {
        for (int ry = y / 20 - radius; ry <= y / 20 + radius; ry++) {
            if (rx < 0 || ry < 0 || rx >= 1024 || ry >= 1024)
                continue;
            float l = 1 - (sqrt(pow(rx - x / 20, 2) + pow(ry - y / 20, 2)) / ((float) radius));
            if (l < 0)l = 0;
            realFog[rx][ry] += l * 256;
            if (realFog[rx][ry] > 255) {
                realFog[rx][ry] = 255;
            }
        }
    }
}

void FogOfWar::update() {
    for (int x = 0; x < 1024; x++) {
        for (int y = 0; y < 1024; y++) {
            if (realFog[x][y] > terrain[x][y])
                terrain[x][y] = (terrain[x][y] * 2 + realFog[x][y]) / 3;
            else
                terrain[x][y] = (terrain[x][y] * 39 + realFog[x][y]) / 40;
            if (y < 10)
                realFog[x][y] = 256 - y * 25;
            else
                realFog[x][y] = 0;
        }
    }
}

unsigned short int FogOfWar::getFog(int x, int y) {
    if (x >= 0 && y >= 0 && x < 1024 && y < 1024)
        return terrain[x][y];
    else if (y < 0)
        return 255;
    else
        return 0;
}

void FogOfWar::setFog(unsigned short int value, int x, int y) {
    if (x >= 0 && y >= 0 && x < 1024 && y < 1024)
        terrain[x][y] = value;
}

void FogOfWar::render(double cx, double cy) {
    int width = glutGet(GLUT_WINDOW_WIDTH) / 20;
    int height = glutGet(GLUT_WINDOW_HEIGHT) / 20;
    for (int x = 0 + cx / 20; x <= width + cx / 20 + 1; x++) {
        for (int y = 0 + cy / 20; y <= height + cy / 20 + 1; y++) {
            float light;
            if (
                    this->getFog(x, y) == 255 &
                    this->getFog(x + 1, y) == 255 &
                    this->getFog(x, y + 1) == 255 &
                    this->getFog(x + 1, y + 1) == 255
                    ) continue;
            if (
                    this->getFog(x, y) == 0 &
                    this->getFog(x + 1, y) == 0 &
                    this->getFog(x, y + 1) == 0 &
                    this->getFog(x + 1, y + 1) == 0
                    ) glDisable(GL_BLEND);
            else glEnable(GL_BLEND);
            glBegin(GL_QUADS);
            {
                light = this->getFog(x, y) / 256.0f;
                glColor4f(0, 0, 0, 1.0f - light);
                glVertex2f(x * 20, y * 20);
                glTexCoord2f(0, 0);

                light = this->getFog(x + 1, y) / 256.0f;
                glColor4f(0, 0, 0, 1.0f - light);
                glVertex2f(x * 20 + 20, y * 20);
                glTexCoord2f(1, 0);

                light = this->getFog(x + 1, y + 1) / 256.0f;
                glColor4f(0, 0, 0, 1.0f - light);
                glVertex2f(x * 20 + 20, y * 20 + 20);
                glTexCoord2f(1, 1);

                light = this->getFog(x, y + 1) / 256.0f;
                glColor4f(0, 0, 0, 1.0f - light);
                glVertex2f(x * 20, y * 20 + 20);
                glTexCoord2f(0, 1);
            }
            glEnd();
        }
    }
}

