/* 
 * File:   Explossion.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 16, 2015, 11:16 AM
 */

#include <stdlib.h>

#include "Texture.hpp"
#include "Explossion.hpp"

using namespace std;

Texture* Explossion::texture[] = {
    new Texture("res/explossion/0.png"),
    new Texture("res/explossion/1.png"),
    new Texture("res/explossion/2.png"),
    new Texture("res/explossion/3.png"),
    new Texture("res/explossion/4.png"),
    new Texture("res/explossion/5.png"),
    new Texture("res/explossion/6.png")
};

Explossion::Explossion(double size, double x, double y) {
    this->size = size;
    this->x = x;
    this->y = y;
    this->a = rand();
}

void Explossion::render() {
    if (t < 30) {
        glEnable(GL_BLEND);
        glColor3f(1, 1, 1);
        texture[t / 5]->bind();
        glTranslated(x, y, 0);
        glRotated(a, 0, 0, 1);
        glBegin(GL_QUADS);
        {
            int linesize = size;
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
        glRotated(a, 0, 0, -1);
        glTranslated(-x, -y, 0);
        texture[t / 5]->unbind();
    }
}

void Explossion::tick() {
    t++;
}

Explossion::Explossion() {
}

Explossion::Explossion(const Explossion& orig) {
}

Explossion::~Explossion() {
}

