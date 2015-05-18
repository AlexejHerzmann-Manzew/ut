/* 
 * File:   Mouse.hpp
 * Author: yew_mentzaki
 *
 * Created on May 7, 2015, 10:19 PM
 */

#ifndef MOUSE_HPP
#define	MOUSE_HPP

#include "Point.hpp"


class Mouse : public Point{
public:
    Mouse();
    Mouse(const Mouse& orig);
    void handleMouse(int, int, int, int);
    void handleMouseMotion(int, int);
    virtual ~Mouse();
    bool left, middle, right;
    bool isLeftReleased, isMiddleReleased, isRightReleased;
    bool isLeftPressed, isMiddlePressed, isRightPressed;
    double dx, dy;
private:

};

#endif	/* MOUSE_HPP */

