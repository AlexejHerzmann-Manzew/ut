/* 
 * File:   Unit.hpp
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 4:53 PM
 */

#include "Game.hpp"

#ifndef UNIT_HPP
#define	UNIT_HPP

class Game;
class Unit {
public:
    Unit();
    Unit(double, double, double, int);
    ~Unit();
    void render();
    void renderInterface();
    void tick();
    void smallTick();
    void deploy();
    int faction, hp, maxHp, target;
    bool selected;
    double tx, ty, px1, py1, px2, py2;
    double turnSpeed, speed;
    double x, y, a, radius;
    Game *game = NULL;
private:

};

#endif	/* UNIT_HPP */

