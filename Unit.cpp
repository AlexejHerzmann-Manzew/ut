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
    this->a = a;
    this->faction = faction;
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
    glRotated(a/PI*180, 0, 0, -1);
    glTranslated(-x, -y, 0);
}
