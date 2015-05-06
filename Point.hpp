/* 
 * File:   Point.hpp
 * Author: yew_mentzaki
 *
 * Created on May 6, 2015, 4:36 PM
 */

#ifndef POINT_HPP
#define	POINT_HPP

class Point {
public:
    Point();
    Point(double, double);
    Point(const Point& orig);
    virtual ~Point();
    double x, y;
private:

};

#endif	/* POINT_HPP */

