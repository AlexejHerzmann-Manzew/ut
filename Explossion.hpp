/* 
 * File:   Explossion.hpp
 * Author: yew_mentzaki
 *
 * Created on May 16, 2015, 11:16 AM
 */

#include "Texture.hpp"

#ifndef EXPLOSSION_HPP
#define	EXPLOSSION_HPP

class Explossion {
public:
    static Texture* texture[];
    double x, y, a, size;
    int t = 0;
    Explossion();
    Explossion(double, double, double);
    Explossion(const Explossion& orig);
    void tick();
    void render();
    virtual ~Explossion();
private:

};

#endif	/* EXPLOSSION_HPP */

