/* 
 * File:   Lebel.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 24, 2015, 1:19 PM
 */

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "Element.hpp"
#include "Lebel.hpp"

Lebel::Lebel() {
}

Lebel::Lebel(const Lebel& orig) {
}

Lebel::~Lebel() {
}

Lebel::Lebel(int x, int y, int w, int h, std::string str) : Element(x, y, w, h) {
    value = str;
    align = GUI_NONE_ALIGN;
}

Lebel::Lebel(int x, int y, int w, int h, int align, std::string str) : Element(x, y, w, h, align) {
    value = str;
    align = align;
}

void Lebel::render() {
    int x = getX();
    int y = getY();
    glColor3f(0, 1, 0);
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*) value.c_str());
}