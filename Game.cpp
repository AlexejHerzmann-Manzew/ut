/* 
 * File:   Game.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 5, 2015, 12:25 AM
 */

#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Game.hpp"
#include "Unit.hpp"

using namespace std;

Game::Game() {
    
}

Game::Game(const Game& orig) {
    Game();
}

Game::~Game() {
    for(int i = 0; i < 256; i++){
        if(this->unit[i] != NULL){
            this->unit[i]->~Unit();
        }
    }
    delete unit;
}

void Game::render() {
    glBegin(GL_LINES);
    {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0, 0);
        glVertex2f(50, 50);
    }
    for(int i = 0; i < 256; i++){
        if(this->unit[i] != NULL){
            this->unit[i]->render();
        }
    }
}

void Game::addUnit(Unit* unit) {
    for(int i = 0; i < 256; i++){
        if(this->unit[i] == NULL){
            this->unit[i] = unit;
            return;
        }
    }
}

void Game::removeUnit(Unit* unit) {
    for(int i = 0; i < 256; i++){
        if(this->unit[i] == unit){
            this->unit[i] = NULL;
            unit->~Unit();
            return;
        }
    }
}

