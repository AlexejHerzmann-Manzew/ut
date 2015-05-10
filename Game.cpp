/* 
 * File:   Game.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 5, 2015, 12:25 AM
 */

#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>

#include "Game.hpp"
#include "Unit.hpp"
#include "Faction.hpp"
#include "Keyboard.hpp"

using namespace std;

Game::Game() {
    display.width = 800;
    display.height = 600;
    this->faction[0] = new Faction("Ruby", new Color(0.8f, 0.1f, 0.2f));
    this->faction[1] = new Faction("Lapis", new Color(0, 0.4f, 1));
    for (int i = 0; i < 5; i++) {
        addUnit(new Unit(1000, 850, 1, 0));
        addUnit(new Unit(2000, 851, 0.1, 1));
    }

}

void Game::updateChar(unsigned char c, int x, int y) {
    keyboard.updateChar(c, x, y);
}

void Game::updateSpecial(int c, int x, int y) {
    keyboard.updateSpecial(c, x, y);
}

void Game::updateCharUp(unsigned char c, int x, int y) {
    keyboard.updateCharUp(c, x, y);
}

void Game::updateSpecialUp(int c, int x, int y) {
    keyboard.updateSpecialUp(c, x, y);
}

double Game::abs(double a) {
    if (a >= 0)
        return a;
    else
        return -a;
}

void Game::handleMouse(int button, int state, int x, int y) {
    mouse.handleMouse(button, state, x, y);
    if (mouse.right) {
        int maxRadius = 0;
        for (int i = 0; i < 256; i++) {
            if (unit[i] != NULL) {
                if (unit[i]->selected && unit[i]->radius > maxRadius)
                    maxRadius = unit[i]->radius;
                if (abs(unit[i]->x - camera.x - mouse.x) <= unit[i]->radius & abs(unit[i]->y - camera.y - mouse.y) <= unit[i]->radius) {
                    if (unit[i]->selected & !(keyboard.isButtonDownCode(GLUT_KEY_CTRL_L) | keyboard.isButtonDownCode(GLUT_KEY_CTRL_R)))
                        unit[i]->deploy();
                    else if (unit[i]->faction != player | (keyboard.isButtonDownCode(GLUT_KEY_CTRL_L) | keyboard.isButtonDownCode(GLUT_KEY_CTRL_R))) {
                        for (int j = 0; j < 256; j++) {
                            if (unit[j] != NULL && unit[j]->selected)
                                unit[j]->target = i;
                        }
                    }
                    return;
                }
            }
        }
        int dx = camera.x + mouse.x, dy = camera.y + mouse.y, d = 0;
        for (int i = 0; i < 256; i++) {
            if (unit[i] != NULL && unit[i]->selected) {
                if (keyboard.isButtonDownCode(GLUT_KEY_SHIFT_L) | keyboard.isButtonDownCode(GLUT_KEY_SHIFT_R)) {
                    unit[i]->tx = unit[i]->px1 = camera.x + mouse.x;
                    unit[i]->ty = unit[i]->py1 = camera.y + mouse.y;
                    unit[i]->px2 = unit[i]->x;
                    unit[i]->py2 = unit[i]->y;
                    unit[i]->target = -1;
                } else {
                    unit[i]->tx = camera.x + mouse.x;
                    unit[i]->ty = camera.y + mouse.y;
                    unit[i]->px1 = unit[i]->px2 = -1;
                    unit[i]->py1 = unit[i]->py2 = -1;
                    unit[i]->target = -1;
                }
            }
            switch (d){
                
            }
        }
    }
}

void Game::handleMouseMotion(int x, int y) {
    mouse.handleMouseMotion(x, y);
    if (mouse.middle) {
        dcamera.x -= mouse.dx;
        dcamera.y -= mouse.dy;
        if (dcamera.x < 0)
            dcamera.x = 0;
        if (dcamera.y < -40)
            dcamera.y = -40;
        if (dcamera.x >= 20480 - display.width)
            dcamera.x = 20480 - display.width;
        if (dcamera.y >= 20480 - display.height)
            dcamera.y = 20480 - display.height;
    }
}

Game::~Game() {
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            this->unit[i]->~Unit();
        }
    }
}

double max(double a, double b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

double min(double a, double b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void Game::render() {
    display.width = glutGet(GLUT_WINDOW_WIDTH);
    display.height = glutGet(GLUT_WINDOW_HEIGHT);
    camera.x = dcamera.x;
    camera.y = dcamera.y;
    if (mouse.left) {
        if (select) {
            p2.x = camera.x + mouse.x;
            p2.y = camera.y + mouse.y;
        } else {
            select = true;
            p1.x = p2.x = camera.x + mouse.x;
            p1.y = p2.y = camera.y + mouse.y;
        }
    } else {
        if (select) {
            select = false;
            for (int i = 0; i < 256; i++) {
                if (unit[i] != NULL && unit[i]->faction == this->player &&
                        unit[i]->x <= max(p1.x, p2.x) + unit[i]->radius &
                        unit[i]->y <= max(p1.y, p2.y) + unit[i]->radius &
                        unit[i]->x >= min(p1.x, p2.x) - unit[i]->radius &
                        unit[i]->y >= min(p1.y, p2.y) - unit[i]->radius
                        ) {
                    unit[i]->selected = true;
                } else if (unit[i] != NULL && !(keyboard.isButtonDownCode(GLUT_KEY_SHIFT_R) | keyboard.isButtonDownCode(GLUT_KEY_SHIFT_L))) {
                    unit[i]->selected = false;
                }
            }
        }
    }
    glTranslated(-dcamera.x, -dcamera.y, 0);
    this->terrain.render(dcamera.x, dcamera.y);
    glEnable(GL_BLEND);
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            this->unit[i]->render();
        }
    }
    this->fow.render(camera.x, camera.y);
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            this->unit[i]->renderInterface();
        }
    }
    glEnable(GL_BLEND);
    if (select) {
        glColor4f(1, 1, 1, 0.2f);
        glBegin(GL_QUADS);
        {
            glVertex2d(p1.x, p1.y);
            glVertex2d(p2.x, p1.y);
            glVertex2d(p2.x, p2.y);
            glVertex2d(p1.x, p2.y);
        }
        glEnd();

        glColor4f(1, 1, 1, 1);
        glBegin(GL_LINES);
        {
            glVertex2d(p1.x, p1.y);
            glVertex2d(p2.x, p1.y);

            glVertex2d(p2.x, p1.y);
            glVertex2d(p2.x, p2.y);

            glVertex2d(p2.x, p2.y);
            glVertex2d(p1.x, p2.y);

            glVertex2d(p1.x, p2.y);
            glVertex2d(p1.x, p1.y);
        }
        glEnd();
    }
    glDisable(GL_BLEND);
}

void Game::smallTick() {
    if (mouse.x < 50)dcamera.x -= 5;
    if (mouse.y < 50)dcamera.y -= 5;
    if (mouse.x > display.width - 50)dcamera.x += 5;
    if (mouse.y > display.height - 50)dcamera.y += 5;


    if (dcamera.x < 0)
        dcamera.x = 0;
    if (dcamera.y < -40)
        dcamera.y = -40;
    if (dcamera.x >= 20480 - display.width)
        dcamera.x = 20480 - display.width;
    if (dcamera.y >= 20480 - display.height)
        dcamera.y = 20480 - display.height;


    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            this->unit[i]->smallTick();
        }
    }
}

void Game::tick() {

    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            this->unit[i]->tick();
        }
    }
    this->fow.update();
}

void Game::addUnit(Unit* unit) {
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] == NULL) {
            this->unit[i] = unit;
            unit->game = this;
            return;
        }
    }
}

void Game::removeUnit(Unit* unit) {
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] == unit) {
            this->unit[i] = NULL;
            unit->~Unit();
            return;
        }
    }
}

