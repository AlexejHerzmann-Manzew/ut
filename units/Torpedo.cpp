/* 
 * File:   BattleDriller.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 10, 2015, 11:37 AM
 */

#include <GL/gl.h>
#include <math.h>

#include "Torpedo.hpp"
#include "../Texture.hpp"

Texture Torpedo::texture("res/torpedo.png");

void Torpedo::init() {
    this->phantom = true;
    this->untargetable = true;
    this->tx = this->ty = -1;
    this->radius = 10;
    this->turnSpeed = 0.02;
    this->speed = 20;
    this->range = -1;
    this->faction = -1;
}

Torpedo::Torpedo() : Unit() {
    init();
}

Torpedo::Torpedo(double x, double y, double a, int f) : Unit(x, y, a, f) {
    init();
}

Torpedo::Torpedo(double x, double y, double tx, double ty, int target) {
    init();
    this->x = x;
    this->y = y;
    this->a = atan2(ty - y, tx - x);
    this->tx = tx;
    this->ty = ty;
    this->target = target;
}

Torpedo::~Torpedo() {

}

void Torpedo::renderVirual() {
    glColor3f(1, 1, 1);
    texture.bind();
    glBegin(GL_QUADS);
    {
        int linesize = 16;
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
}

void Torpedo::renderIntefaceVirtual() {

}

void Torpedo::smallTickVirtual() {
    if (game->unit[target] != NULL) {
        if (sqrt(pow(x - tx, 2) + pow(y - ty, 2)) <= 10) {
            game->terrain.digg(100, x, y);
            for (int i = 1; i <= 5; i++) {
                game->fow.open(i * 50, x, y);
            }
            game->unit[target]->hit(10);
            game->addExplossion(new Explossion(50, x, y));
            game->removeUnit(this);
        }
        this->tx = game->unit[target]->x;
        this->ty = game->unit[target]->y;
        this->a = atan2(ty - y, tx - x);
    } else {
        game->removeUnit(this);
        game->addExplossion(new Explossion(25, x, y));
        for (int i = 1; i <= 5; i++) {
            game->fow.open(i * 50, x, y);
        }
    }
}

void Torpedo::tickVirtual() {

}
