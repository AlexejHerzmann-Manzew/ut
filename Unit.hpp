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
    Unit(double, double, double, int);
    Unit(const Unit& orig);
    ~Unit();
    void render();
    void tick();
    void smallTick();
    int faction;
    double x, y, a, radius;
    Game *game = NULL;
private:

};

#endif	/* UNIT_HPP */

