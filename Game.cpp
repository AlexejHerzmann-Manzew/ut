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
#include <functional>

#include "Game.hpp"
#include "Unit.hpp"
#include "Faction.hpp"
#include "Keyboard.hpp"
#include "Math.hpp"

#include "gui/GUI.hpp"

#include "units/BattleDriller.hpp"
#include "units/Builder.hpp"

using namespace std;

Texture Game::grass("res/grass.png");

void bClicked(Mouse* m) {
    cout << "Button's clicked!" << endl;
}

Game::Game() {
    display.width = 800;
    display.height = 600;
    this->faction[0] = new Faction("Ruby", new Color(1.0f, 0.1f, 0.0f));
    this->faction[1] = new Faction("Lapis", new Color(0, 0.4f, 1));
    for (int i = 0; i < 2; i++) {
        addUnit(new BattleDriller(1000, 850, 1, 0));
        addUnit(new BattleDriller(2000, 851, 0.1, 1));
    }
    addUnit(new Builder(2000, 851, 0.1, 1));
    addUnit(new Builder(1000, 851, 0.1, 0));
    Button* b = new Button(-50, 50, 30, 30, GUI_RIGHT_ALIGN);
    //b->setClickListener(bClicked);
    gui.add(b);
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
                            if (unit[j] != NULL && unit[j]->selected && unit[j]->range != -1) {
                                unit[j]->target = i;
                                unit[j]->forcedAttack = true;
                            }
                        }
                    }
                    return;
                }
            }
        }
        int dx = camera.x + mouse.x, dy = camera.y + mouse.y, d = 0, dm = 1, m = 1;
        for (int i = 0; i < 256; i++) {
            if (unit[i] != NULL && unit[i]->selected) {
                if (keyboard.isButtonDownCode(GLUT_KEY_SHIFT_L) | keyboard.isButtonDownCode(GLUT_KEY_SHIFT_R)) {
                    unit[i]->tx = unit[i]->px1 = dx;
                    unit[i]->ty = unit[i]->py1 = dy;
                    unit[i]->px2 = unit[i]->x;
                    unit[i]->py2 = unit[i]->y;
                    unit[i]->target = -1;
                    unit[i]->forcedAttack = false;
                } else {
                    unit[i]->tx = dx;
                    unit[i]->ty = dy;
                    unit[i]->px1 = unit[i]->px2 = -1;
                    unit[i]->py1 = unit[i]->py2 = -1;
                    unit[i]->target = -1;
                    unit[i]->forcedAttack = false;
                }
                switch (d) {
                    case 0:
                        dx = dx - 2 * maxRadius;
                        break;
                    case 1:
                        dy = dy - 2 * maxRadius;
                        break;
                    case 2:
                        dx = dx + 2 * maxRadius;
                        break;
                    case 3:
                        dy = dy + 2 * maxRadius;
                        break;
                }
                dm--;
                if (dm == 0) {
                    if (d == 1 | d == 3)m++;
                    dm = m;
                    d++;
                    if (d > 3)d = 0;
                }
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
                try {
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
                } catch (const exception &e) {

                }
            }
        }
    }
    glTranslated(-camera.x, -camera.y, 0);
    this->terrain.render(camera.x, camera.y);
    glEnable(GL_BLEND);
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            try {
                this->unit[i]->render();
            } catch (const exception &e) {

            }
        }
        glLoadIdentity();
        glTranslated(-camera.x, -camera.y, 0);
    }
    this->fow.render(camera.x, camera.y);
    for (int i = 0; i < 64; i++) {
        if (this->explossion[i] != NULL) {
            this->explossion[i]->render();
            if (this->explossion[i]->t >= 30) {
                this->explossion[i]->~Explossion();
                this->explossion[i] = NULL;
            }
        }
        glLoadIdentity();
        glTranslated(-camera.x, -camera.y, 0);
    }
    glEnable(GL_BLEND);
    if (camera.y < 5) {
        glColor3f(1, 1, 1);
        grass.bind();
        glBegin(GL_QUADS);
        for (int x = camera.x / 64 - 1; x <= (camera.x + display.width) / 64 + 1; x++) {
            glVertex2f(x * 64, 20);
            glTexCoord2f(0, 0);

            glVertex2f(x * 64, -44);
            glTexCoord2f(1, 0);

            glVertex2f((x + 1)*64, -44);
            glTexCoord2f(1, 1);

            glVertex2f((x + 1)*64, 20);
            glTexCoord2f(0, 1);
        }
        glEnd();
        grass.unbind();
    }
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
    glLoadIdentity();
    gui.render();
    glDisable(GL_BLEND);
}

void Game::smallTick() {
    if (mouse.x < 50 | keyboard.isButtonDownCode(GLUT_KEY_LEFT))dcamera.x -= 5;
    if (mouse.y < 50 | keyboard.isButtonDownCode(GLUT_KEY_UP))dcamera.y -= 5;
    if (mouse.x > display.width - 50 | keyboard.isButtonDownCode(GLUT_KEY_RIGHT))dcamera.x += 5;
    if (mouse.y > display.height - 50 | keyboard.isButtonDownCode(GLUT_KEY_DOWN))dcamera.y += 5;


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
            try {
                this->unit[i]->smallTick();
            } catch (const exception &e) {

            }
        }
        if (i < 64 & this->explossion[i] != NULL) {
            this->explossion[i]->tick();
        }
    }
}

void Game::tick() {
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            try {
                this->unit[i]->tick();
            } catch (const exception &e) {

            }
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

void Game::addExplossion(Explossion* explossion) {
    for (int i = 0; i < 64; i++) {
        if (this->explossion[i] == NULL) {
            this->explossion[i] = explossion;
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