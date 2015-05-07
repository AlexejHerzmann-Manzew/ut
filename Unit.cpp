/* 
 * File:   Unit.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 5, 2015, 4:53 PM
 */

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "Unit.hpp"
#include "Game.hpp"

using namespace std;

const double PI = 3.14159265;

Unit::Unit(double x, double y, double a, int faction) {
    this->x = x;
    this->y = y;
    this->a = ((double) rand()) / 256 / 256;
    this->faction = faction;
    this->radius = 40;
}

Unit::Unit(const Unit& orig) {
}

Unit::~Unit() {
}

void Unit::render() {
    double x = this->x, y = this->y, a = this->a;
    glTranslated(x, y, 0);
    glRotated(a / PI * 180, 0, 0, 1);
    this->game->faction[faction]->color->bind();
    glBegin(GL_QUADS);
    {
        glVertex2f(-32, -32);
        glTexCoord2f(0, 0);

        glVertex2f(32, -32);
        glTexCoord2f(1, 0);

        glVertex2f(32, 32);
        glTexCoord2f(1, 1);

        glVertex2f(-32, 32);
        glTexCoord2f(0, 1);
    }
    glEnd();
    glRotated(a / PI * 180, 0, 0, -1);
    glTranslated(-x, -y, 0);
}

void Unit::smallTick() {
    for (int i = 0; i < 256; i++) {
        if (game->unit[i] != NULL) {
            double d = (sqrt(pow(game->unit[i]->x - x, 2) + pow(game->unit[i]->y - y, 2)) - (game->unit[i]->radius + radius)) / 2;
            if (d < 0) {
                double a = atan2(game->unit[i]->y - y, game->unit[i]->x - x);
                game->unit[i]->x -= cos(a) * d;
                game->unit[i]->y -= sin(a) * d;

                x += cos(a) * d;
                y += sin(a) * d;
            }
        }
    }

    a += 0.01570796326;
    x += cos(a) * 5;
    y += sin(a) * 5;
}

void Unit::tick() {
    if (this->faction == game->player)
        this->game->fow.open(5, x, y);
}
