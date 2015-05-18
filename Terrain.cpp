/* 
 * File:   Terrain.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 5, 2015, 10:25 PM
 */

#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/freeglut_std.h>

#include "Terrain.hpp"
#include "Point.hpp"

using namespace std;

Texture Terrain::dirt("res/dirt.png");

Terrain::Terrain() {
    for (int x = 0; x < 4096; x++) {
        for (int y = 0; y < 4096; y++) {
            terrain[x][y] = rand();
            terrain[x][y] /= 255;
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
    if (x >= 0 && y >= 0 && x < 4096 && y < 4096)
        terrain[x][y] = value;
}

int maxThenZero(int v) {
    if (v > 0)
        return v;
    else
        return 0;
}

double Terrain::speed(double x, double y) {
    return ((double) getTerrain(x / 5, y / 5)) / 256;
}

void Terrain::digg(double radius, double x, double y) {
    radius /= 5;
    for (int rx = x / 5 - radius; rx <= x / 5 + radius; rx++) {
        for (int ry = y / 5 - radius; ry <= y / 5 + radius; ry++) {
            if (rx < 0 || ry < 0 || rx >= 4096 || ry >= 4096)
                continue;
            if (terrain[rx][ry] > 200)
                continue;
            float l = 1 - (sqrt(pow(rx - x / 5, 2) + pow(ry - y / 5, 2)) / ((float) radius));
            if (l < 0)l = 0;
            if (terrain[rx][ry] < l * 222)
                terrain[rx][ry] = l * 222;
            if (terrain[rx][ry] > 255) {
                terrain[rx][ry] = 255;
            }
        }
    }
}

void Terrain::render(double cx, double cy) {
    int width = glutGet(GLUT_WINDOW_WIDTH) / 5;
    int height = glutGet(GLUT_WINDOW_HEIGHT) / 5;
    for (int x = 0 + cx / 5; x <= width + cx / 5; x++) {
        for (int y = maxThenZero(0 + cy / 5); y <= height + cy / 5; y++) {
            float light;
            glBegin(GL_QUADS);
            {
                light = this->getTerrain(x, y) / 256.0f;
                glColor3f(light, light * 0.8f, light * 0.5f);
                glVertex2f(x * 5, y * 5);
                glTexCoord2f(0, 0);

                light = this->getTerrain(x + 1, y) / 256.0f;
                glColor3f(light, light * 0.8f, light * 0.5f);
                glVertex2f(x * 5 + 5, y * 5);
                glTexCoord2f(1, 0);

                light = this->getTerrain(x + 1, y + 1) / 256.0f;
                glColor3f(light, light * 0.8f, light * 0.5f);
                glVertex2f(x * 5 + 5, y * 5 + 5);
                glTexCoord2f(1, 1);

                light = this->getTerrain(x, y + 1) / 256.0f;
                glColor3f(light, light * 0.8f, light * 0.5f);
                glVertex2f(x * 5, y * 5 + 5);
                glTexCoord2f(0, 1);
            }
            glEnd();
        }
    }
}

