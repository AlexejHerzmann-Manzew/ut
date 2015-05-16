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
#include <iostream>

#include "Unit.hpp"
#include "Game.hpp"

using namespace std;

const double PI = 3.14159265;

Texture Unit::destroyed("res/destroyed.png");

Unit::Unit(double x, double y, double a, int faction) {
    this->x = x;
    this->y = y;
    this->a = 0;
    this->faction = faction;
    init();
}

Unit::Unit() {
    init();
}

Unit::~Unit() {
}

void Unit::init() {
    this->radius = 28;
    this->target = tx = ty = -1;
    this->turnSpeed = 0.05;
    this->speed = 3;
    this->hp = this->maxHp = 100;
}

void Unit::render() {
    if (hp == 0) {
        glTranslated(x, y, 0);
        glRotated(a / PI * 180, 0, 0, 1);
        glColor4f(1, 1, 1, (1000.0f - (float) removeTimer) / 1000.0f);
        destroyed.bind();
        glBegin(GL_QUADS);
        {
            glVertex2f(-radius * 2, -radius * 2);
            glTexCoord2f(0, 0);

            glVertex2f(radius * 2, -radius * 2);
            glTexCoord2f(1, 0);

            glVertex2f(radius * 2, radius * 2);
            glTexCoord2f(1, 1);

            glVertex2f(-radius * 2, radius * 2);
            glTexCoord2f(0, 1);
        }
        glEnd();
        destroyed.unbind();
        glRotated(a / PI * 180, 0, 0, -1);
        glTranslated(-x, -y, 0);
        return;
    }
    double x = this->x, y = this->y, a = this->a;
    glTranslated(x, y, 0);
    glRotated(a / PI * 180, 0, 0, 1);
    this->renderVirual();
    glRotated(a / PI * 180, 0, 0, -1);
    glTranslated(-x, -y, 0);
}

void Unit::renderVirual() {
    this->game->faction[faction]->color->bind();
    glBegin(GL_QUADS);
    {
        glVertex2f(-radius, -radius);
        glTexCoord2f(0, 0);

        glVertex2f(radius, -radius);
        glTexCoord2f(1, 0);

        glVertex2f(radius, radius);
        glTexCoord2f(1, 1);

        glVertex2f(-radius, radius);
        glTexCoord2f(0, 1);
    }
    glEnd();
}

void Unit::renderInterface() {
    if (hp == 0) {
        return;
    }
    double x = this->x, y = this->y, a = this->a;
    glTranslated(x, y, 0);
    if (hp < maxHp && hp > 0) {
        glColor4f(0, 0, 0, 0.2f);
        glBegin(GL_POLYGON);
        {
            glVertex2f(-radius - 1, -radius - 1);
            glVertex2f(radius + 1, -radius - 1);
            glVertex2f(radius + 1, -radius - 6);
            glVertex2f(-radius - 1, -radius - 6);
        }
        glEnd();
        if (hp > maxHp / 4)
            glColor3f(0, 1, 0);
        else
            glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        {
            glVertex2f(-radius, -radius - 2);
            glVertex2f(-radius + (2 * radius * ((float) hp / (float) maxHp)), -radius - 2);
            glVertex2f(-radius + (2 * radius * ((float) hp / (float) maxHp)), -radius - 5);
            glVertex2f(-radius, -radius - 5);
        }
        glEnd();
    }
    if (this->selected) {
        glColor3f(1, 1, 1);
        glBegin(GL_LINES);
        {
            glVertex2f(-radius + 5, -radius);
            glVertex2f(-radius, -radius);

            glVertex2f(-radius, -radius);
            glVertex2f(-radius, -radius + 5);
            //////
            //////
            glVertex2f(radius - 5, -radius);
            glVertex2f(radius, -radius);

            glVertex2f(radius, -radius);
            glVertex2f(radius, -radius + 5);
            //////
            //////
            glVertex2f(radius - 5, radius);
            glVertex2f(radius, radius);

            glVertex2f(radius, radius);
            glVertex2f(radius, radius - 5);
            //////
            //////
            glVertex2f(-radius + 5, radius);
            glVertex2f(-radius, radius);

            glVertex2f(-radius, radius);
            glVertex2f(-radius, radius - 5);

        }
        glEnd();
    }
    this->renderIntefaceVirtual();
    glTranslated(-x, -y, 0);
    if (this->selected) {
        if (this->tx != -1) {
            glColor3f(0, 1, 0);
            glBegin(GL_LINES);
            {
                glVertex2f(x, y);
                glVertex2f(tx, ty);
            }
            glEnd();
            glBegin(GL_QUADS);
            {
                glVertex2f(tx - 2, ty - 2);
                glVertex2f(tx + 2, ty - 2);
                glVertex2f(tx + 2, ty + 2);
                glVertex2f(tx - 2, ty + 2);
            }
            glEnd();
        }
        if (this->target != -1) {
            if (this->game->unit[target] != NULL) {
                glColor3f(1, 0, 0);
                glBegin(GL_LINES);
                {
                    glVertex2f(x, y);
                    glVertex2f(game->unit[target]->x, game->unit[target]->y);
                }
                glEnd();
                glBegin(GL_QUADS);
                {
                    glVertex2f(game->unit[target]->x - 2, game->unit[target]->y - 2);
                    glVertex2f(game->unit[target]->x + 2, game->unit[target]->y - 2);
                    glVertex2f(game->unit[target]->x + 2, game->unit[target]->y + 2);
                    glVertex2f(game->unit[target]->x - 2, game->unit[target]->y + 2);
                }
                glEnd();
            } else {
                this->target = -1;
            }
        }
        if (this->px1 != -1) {
            glColor3f(0, 1, 0);
            glBegin(GL_LINES);
            {
                glVertex2f(px1, py1);
                glVertex2f(px2, py2);
            }
            glEnd();
            glBegin(GL_QUADS);
            {
                glVertex2f(px1 - 2, py1 - 1);
                glVertex2f(px1 + 2, py1 - 2);
                glVertex2f(px1 + 2, py1 + 2);
                glVertex2f(px1 - 2, py1 + 2);

                glVertex2f(px2 - 2, py2 - 2);
                glVertex2f(px2 + 2, py2 - 2);
                glVertex2f(px2 + 2, py2 + 2);
                glVertex2f(px2 - 2, py2 + 2);

            }
            glEnd();
        }
    }
}

void Unit::renderIntefaceVirtual() {
}

void Unit::hit(int damage) {
    if (damage > hp) {
        hp = 0;
    } else {
        hp -= damage;
    }
}

double abs(double a) {
    if (a >= 0)
        return a;
    else
        return -a;
}

void Unit::smallTick() {
    if (hp == 0) {
        phantom = true;
        untargetable = true;
        return;
    }
    this->smallTickVirtual();
    if (!phantom)
        for (int i = 0; i < 256; i++) {
            if (game->unit[i] != NULL && !game->unit[i]->phantom) {
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

    if (tx != -1 & ty != -1) {
        if (abs(px1 - x) + abs(py1 - y) < radius) {
            tx = px2;
            ty = py2;
        } else if (abs(px2 - x) + abs(py2 - y) < radius) {
            tx = px1;
            ty = py1;
        } else if (abs(tx - x) + abs(ty - y) < radius) {
            tx = -1;
            ty = -1;
        }

        double ta = atan2(ty - y, tx - x);
        if (a < -PI) {
            a += 2 * PI;
        }
        if (a > +PI) {
            a -= 2 * PI;
        }
        if (a != ta) {
            if (abs(ta - a) > turnSpeed) {
                int v = (abs(ta - a) <= 2 * PI - abs(ta - a)) ? 1 : -1;

                if (ta < a) {
                    a -= turnSpeed * v;
                } else if (ta > a) {
                    a += turnSpeed * v;
                }
            } else {
                a = ta;
            }
        }

        double d = this->game->terrain.speed(x + cos(a) * radius / 3 * 2, y + sin(a) * radius / 3 * 2);
        x += cos(a) * 2 * d;
        y += sin(a) * 2 * d;
        this->game->terrain.digg(radius / 2, x, y);
    }

    if (y < radius)y += 3;

    if (x < radius)x += 3;
    if (x > 20480 - radius)x -= 3;

}

void Unit::smallTickVirtual() {

}

void Unit::tick() {
    if (hp == 0) {
        if (removeTimer == 0){
            game->addExplossion(new Explossion(radius * 2, x, y));
        }
        if (removeTimer < 5) {
            for (int i = 1; i <= 10; i++) {
                game->fow.open(i * 30 / (removeTimer + 1), x, y);
            }
        }
        removeTimer++;
        if (removeTimer == 1000) {
            game->removeUnit(this);
        }
        return;
    }
    this->tickVirtual();
    if (this->faction == game->player) {
        this->game->fow.open(150, x, y);
    }
}

void Unit::tickVirtual() {

}

void Unit::deploy() {
    cout << "Unit deployed!" << endl;
}
