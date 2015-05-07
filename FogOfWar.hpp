/* 
 * File:   Terrain.hpp
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 10:25 PM
 */

#include "Point.hpp"

#ifndef FOGOFWAR_HPP
#define	FOGOFWAR_HPP

class FogOfWar {
public:
    FogOfWar();
    unsigned short int getFog(int, int);
    void setFog(unsigned short int, int, int);
    void render(double, double);
    void open(int, int, int);
    void update();
    virtual ~FogOfWar();
private:
    unsigned short int terrain[1024][1024], realFog[1024][1024];
};

#endif	/* FOGOFWAR_HPP */

