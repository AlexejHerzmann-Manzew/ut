/* 
 * File:   Terrain.hpp
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 10:25 PM
 */

#include "Point.hpp"

#ifndef TERRAIN_HPP
#define	TERRAIN_HPP

class Terrain {
public:
    Terrain();
    Terrain(const Terrain& orig);
    unsigned short int getTerrain(int, int);
    void setTerrain(unsigned short int, int, int);
    void render(double, double);
    virtual ~Terrain();
private:
    unsigned short int terrain[4096][4096];
};

#endif	/* TERRAIN_HPP */

