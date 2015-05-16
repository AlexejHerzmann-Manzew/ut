/* 
 * File:   BattleDriller.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 10, 2015, 11:37 AM
 */

#include <GL/gl.h>
#include <math.h>

#include "BattleDriller.hpp"
#include "Torpedo.hpp"
#include "../Texture.hpp"

Texture BattleDriller::texture("res/driller_standing.png");
Texture BattleDriller::texture_team("res/driller_team.png");
Texture BattleDriller::texture_turret("res/driller_turret.png");

void BattleDriller::init() {
    this->reloadTime = 1000;
    this->tx = this->ty = -1;
    this->radius = 40;
    this->turnSpeed = 0.03;
    this->speed = 8;
    this->range = 350;
}

BattleDriller::BattleDriller() : Unit() {
    init();
}

BattleDriller::BattleDriller(double x, double y, double a, int f) : Unit(x, y, a, f) {
    init();
}

BattleDriller::~BattleDriller() {

}

void BattleDriller::renderVirual() {
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
    if (target != -1) {
        double a = atan2(game->unit[target]->y - y, game->unit[target]->x - x);
        glRotated((a - this->a) / 3.1415 * 180, 0, 0, 1);
        glColor3f(1, 1, 1);
        texture_turret.bind();
        glBegin(GL_QUADS);
        {
            int linesize = 32;
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
        texture_turret.unbind();
        glRotated((a - this->a) / 3.1415 * 180, 0, 0, -1);
    }
}

void BattleDriller::renderIntefaceVirtual() {

}

void BattleDriller::smallTickVirtual() {
    if (target != -1 && game->unit[target] != NULL && game->unit[target]->hp > 0) {
        double d = sqrt(pow(game->unit[target]->x - x, 2) + pow(game->unit[target]->y - y, 2));
        double a = atan2(game->unit[target]->y - y, game->unit[target]->x - x);
        if (d > range) {
            if (forcedAttack) {
                tx = game->unit[target]->x - cos(a) * range * 0.9;
                ty = game->unit[target]->y - sin(a) * range * 0.9;
            } else {
                target = -1;
            }
        } else if (d < range / 2) {
            tx = game->unit[target]->x - cos(a) * range * 0.9;
            ty = game->unit[target]->y - sin(a) * range * 0.9;
        } else {
            if (currentReload == 0) {
                game->addUnit(new Torpedo(x, y, game->unit[target]->x, game->unit[target]->y, target));
                currentReload = reloadTime;
            } else
                currentReload--;
        }
    } else {
        target = -1;
        if (px1 != -1 & (tx != px1 & tx != px2)) {
            if (sqrt(pow(px1 - x, 2) + pow(py1 - y, 2)) < sqrt(pow(px2 - x, 2) + pow(py2 - y, 2))) {
                tx = px2;
                ty = py2;
            } else {
                tx = px1;
                ty = py1;
            }
        }
        if (tx == -1 | px1 != -1) {
            for (int i = 0; i < 256; i++) {
                if (game->unit[i] != NULL) {
                    double d = sqrt(pow(game->unit[i]->x - x, 2) + pow(game->unit[i]->y - y, 2));
                    if (d < range) {
                        if (game->unit[i]->faction != this->faction && !game->unit[i]->untargetable && game->unit[i]->hp > 0) {
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
}

void BattleDriller::tickVirtual() {

}
