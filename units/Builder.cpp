/* 
 * File:   BattleDriller.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 10, 2015, 11:37 AM
 */

#include <GL/gl.h>
#include <math.h>

#include "Builder.hpp"
#include "../Texture.hpp"

Texture Builder::texture("res/builder_standing.png");
Texture Builder::texture_team("res/builder_team.png");

void Builder::init() {
    this->tx = this->ty = -1;
    this->radius = 50;
    this->turnSpeed = 0.02;
    this->speed = 6;
    this->range = -1;
}

Builder::Builder() : Unit() {
    init();
}

Builder::Builder(double x, double y, double a, int f) : Unit(x, y, a, f) {
    init();
}

Builder::~Builder() {

}

void Builder::renderVirual() {
    glColor3f(1, 1, 1);
    texture.bind();
    glBegin(GL_QUADS);
    {
        int linesize = 64;
        glVertex2f(-linesize, linesize);
        glTexCoord2f(0, 0);

        glVertex2f(-linesize, -linesize);
        glTexCoord2f(1, 0);

        glVertex2f(linesize, -linesize);
        glTexCoord2f(1, 1);

        glVertex2f(linesize, linesize);
        glTexCoord2f(0, 1);
    }
    glEnd();
    texture.unbind();
    this->game->faction[faction]->color->bind();
    texture_team.bind();
    glBegin(GL_QUADS);
    {
        int linesize = 64;
        glVertex2f(-linesize, linesize);
        glTexCoord2f(0, 0);

        glVertex2f(-linesize, -linesize);
        glTexCoord2f(1, 0);

        glVertex2f(linesize, -linesize);
        glTexCoord2f(1, 1);

        glVertex2f(linesize, linesize);
        glTexCoord2f(0, 1);
    }
    glEnd();
    texture_team.unbind();
}

void Builder::renderIntefaceVirtual() {

}

void Builder::smallTickVirtual() {
    
}

void Builder::tickVirtual() {

}
