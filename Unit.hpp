/* 
 * File:   Unit.hpp
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 4:53 PM
 */

#include "Game.hpp"
#include "Texture.hpp"

#ifndef UNIT_HPP
#define	UNIT_HPP

class Game;
class Unit {
public:
    static Texture destroyed;
    Unit();
    Unit(double, double, double, int);
    ~Unit();
    void hit(int);
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
    int faction, hp, maxHp, target, removeTimer;
    int reloadTime, reloadAmmoTime, currentReload, currentAmmo;
    bool selected, forcedAttack;
    bool phantom, untargetable;
    double tx, ty, px1, py1, px2, py2;
    double range;
    double turnSpeed, speed;
    double x, y, a, radius;
    Game *game = NULL;
private:

};

#endif	/* UNIT_HPP */

