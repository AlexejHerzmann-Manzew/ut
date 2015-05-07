/* 
 * File:   Game.hpp
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 12:25 AM
 */

#ifndef GAME_HPP
#define	GAME_HPP

#include "Unit.hpp"
#include "Faction.hpp"
#include "Terrain.hpp"
#include "Point.hpp"
#include "Mouse.hpp"
#include "Size.hpp"
#include "FogOfWar.hpp"

class Game {
public:
    Game();
    ~Game();
    void render();
    void tick();
    void smallTick();
    void addUnit(Unit* unit);
    void removeUnit(Unit* unit);
    void handleMouse(int, int, int, int);
    void handleMouseMotion(int, int);
    Size display;
    Point camera; Mouse mouse;
    Faction* faction[2];
    Unit* unit[256];
    Terrain terrain;
    FogOfWar fow;
};

#endif	/* GAME_HPP */

