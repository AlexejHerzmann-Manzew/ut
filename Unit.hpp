/* 
 * File:   Unit.hpp
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 4:53 PM
 */

#ifndef UNIT_HPP
#define	UNIT_HPP

class Unit {
public:
    Unit();
    Unit(const Unit& orig);
    ~Unit();
    void render();
    double x, y, a;
private:

};

#endif	/* UNIT_HPP */

