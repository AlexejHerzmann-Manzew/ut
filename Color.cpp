/* 
 * File:   Color.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 5, 2015, 9:29 PM
 */

#include <GL/gl.h>

#include "Color.hpp"

Color::Color() {
}


Color::Color(const Color& orig) {
}

Color::~Color() {
}

Color::Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 1;
}

Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Color::bind() {
    glColor4f(r, g, b, a);
}
