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
#include "Keyboard.hpp"
#include "Texture.hpp"
#include "Explossion.hpp"

#include "gui/GUI.hpp"
#include "gui/Lebel.hpp"

class Game {
public:
    Game();
    ~Game();
    void render();
    void tick();
    void smallTick();
    void addUnit(Unit* unit);
    void addExplossion(Explossion* explossion);
    void updateChar(unsigned char, int, int);
    void updateCharUp(unsigned char, int, int);
    void updateSpecial(int, int, int);
    void updateSpecialUp(int, int, int);
    void removeUnit(Unit* unit);
    void handleMouse(int, int, int, int);
    void handleMouseMotion(int, int);
    double abs(double);
    Texture* sonarPics[6];
    Size display;
    GUI gui;
    Lebel* unitLebel;
    Point camera, dcamera;
    Mouse mouse;
    Keyboard keyboard;
    Point p1, p2; bool select;
    Faction* faction[3];
    Unit* unit[256];
    Explossion* explossion[64];
    Terrain terrain;
    FogOfWar fow;
    int player;
private:
    static Texture grass;
};

#endif	/* GAME_HPP */

