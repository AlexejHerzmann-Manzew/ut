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
Texture Builder::texture_team("res/driller_team.png");

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
    /*
    if (target != -1 && game->unit[target] != NULL) {
        double d = sqrt(pow(game->unit[target]->x - x, 2) + pow(game->unit[target]->y - y, 2));
        double a = atan2(game->unit[target]->y - y, game->unit[target]->x - x);
        if (d > range) {
            tx = game->unit[target]->x - cos(a) * range * 0.9;
            ty = game->unit[target]->y - sin(a) * range * 0.9;
        } else if (d < range / 2) {
            tx = game->unit[target]->x - cos(a) * range * 0.9;
            ty = game->unit[target]->y - sin(a) * range * 0.9;
        } else {

        }
    } else {
        target = -1;
        if (px1 != -1) {
            tx = px1;
            ty = py1;
        }
        if (tx == -1 | px1 != -1) {
            for (int i = 0; i < 256; i++) {
                if (game->unit[i] != NULL) {
                    double d = sqrt(pow(game->unit[i]->x - x, 2) + pow(game->unit[i]->y - y, 2));
                    if (d < range) {
                        if (game->unit[i]->faction != this->faction) {
                            target = i;
                            tx = -1;
                            ty = -1;
                            break;
                        }
                    }
                }
            }
        }
     }
     */
}

void Builder::tickVirtual() {

}
