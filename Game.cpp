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
#include <string>

#include "Game.hpp"
#include "Unit.hpp"
#include "Faction.hpp"

using namespace std;

Game::Game() {
    display.width = 800;
    display.height = 600;
    this->faction[0] = new Faction("Ruby", new Color(1, 0, 0));
    this->faction[1] = new Faction("Lapis", new Color(0, 0.4f, 1));
    addUnit(new Unit(750, 850, 1, 0));
    addUnit(new Unit(1250, 1250, 0.4, 0));
    addUnit(new Unit(2150, 1350, 0.1, 1));
    addUnit(new Unit(2350, 1300, -0.2, 1));
}

void Game::handleMouse(int button, int state, int x, int y) {
    mouse.handleMouse(button, state, x, y);
}

void Game::handleMouseMotion(int x, int y) {
    mouse.handleMouseMotion(x, y);
    if (mouse.right) {
        camera.x -= mouse.dx;
        camera.y -= mouse.dy;
        if (camera.x < 0)
            camera.x = 0;
        if (camera.y < -40)
            camera.y = -40;
        if (camera.x >= 20480 - display.width)
            camera.x = 20480 - display.width;
        if (camera.y >= 20480 - display.height)
            camera.y = 20480 - display.height;
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
    glTranslated(-camera.x, -camera.y, 0);
    this->terrain.render(camera.x, camera.y);
    glEnable(GL_BLEND);
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            this->unit[i]->render();
        }
    }
    this->fow.render(camera.x, camera.y);
    glDisable(GL_BLEND);
}

void Game::smallTick() {
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            this->unit[i]->smallTick();
        }
    }
    this->fow.update();
}

void Game::tick() {
    for (int i = 0; i < 256; i++) {
        if (this->unit[i] != NULL) {
            this->unit[i]->tick();
        }
    }
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

