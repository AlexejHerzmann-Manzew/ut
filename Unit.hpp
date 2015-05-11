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
    virtual void init();
    void render();
    virtual void renderVirual();
    void renderInterface();
    virtual void renderIntefaceVirtual();
    void tick();
    virtual void tickVirtual();
    void smallTick();
    virtual void smallTickVirtual();
    virtual void deploy();
    int faction, hp, maxHp, target;
    bool selected, hasAttack;
    double tx, ty, px1, py1, px2, py2;
    double range;
    double turnSpeed, speed;
    double x, y, a, radius;
    Game *game = NULL;
private:

};

#endif	/* UNIT_HPP */

