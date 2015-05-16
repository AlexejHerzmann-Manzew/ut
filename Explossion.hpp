/* 
 * File:   Explossion.hpp
 * Author: yew_mentzaki
 *
 * Created on May 16, 2015, 11:16 AM
 */

#ifndef EXPLOSSION_HPP
#define	EXPLOSSION_HPP

class Explossion {
public:
    double x, y, a, size;
    Explossion();
    Explossion(double, double, double);
    Explossion(const Explossion& orig);
    void tick();
    void render();
    virtual ~Explossion();
private:

};

#endif	/* EXPLOSSION_HPP */

