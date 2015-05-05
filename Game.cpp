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
#include <string>

#include "Game.hpp"
#include "Unit.hpp"
#include "Faction.hpp"

using namespace std;

Game::Game() {
    this->faction[0] = new Faction("Ruby", new Color(1, 0, 0));
    this->faction[1] = new Faction("Lapis", new Color(0, 0.2f, 1));
    addUnit(new Unit(250, 150, 1, 0));
    addUnit(new Unit(50, 50, 0.4, 0));
    addUnit(new Unit(150, 350, 0.1, 1));
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
}

void Game::render() {
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
            unit->game = this;
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

