/* 
 * File:   Game.hpp
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 12:25 AM
 */

#ifndef GAME_HPP
#define	GAME_HPP

#include "Unit.hpp"

class Game {
public:
    Game();
    Game(const Game& orig);
    ~Game();
    void render();
    void addUnit(Unit* unit);
    void removeUnit(Unit* unit);
    Unit* unit[256];
};

#endif	/* GAME_HPP */

