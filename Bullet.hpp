/* 
 * File:   Bullet.hpp
 * Author: yew_mentzaki
 *
 * Created on May 10, 2015, 5:45 PM
 */

#ifndef BULLET_HPP
#define	BULLET_HPP

class Bullet {
public:
    Bullet();
    Bullet(const Bullet& orig);
    virtual ~Bullet();
    double x, y;
private:

};

#endif	/* BULLET_HPP */

