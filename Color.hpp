/* 
 * File:   Color.hpp
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 9:29 PM
 */

#ifndef COLOR_HPP
#define	COLOR_HPP

class Color {
public:
    Color();
    Color(float, float, float);
    Color(float, float, float, float);
    Color(const Color& orig);
    float r, g, b, a;
    void bind();
    virtual ~Color();
private:

};

#endif	/* COLOR_HPP */

