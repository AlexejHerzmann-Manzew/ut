/* 
 * File:   Button.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 18, 2015, 9:47 PM
 */

#include <cstddef>
#include <GL/gl.h>

#include "Button.hpp"

Button::Button(int x, int y, int w, int h) : Element(x, y, w, h) {
    visible = true;
}

Button::Button(int x, int y, int w, int h, int align) : Element(x, y, w, h, align) {
    visible = true;
}

Button::Button() {
    visible = true;
}

Button::Button(const Button& orig) {
    visible = true;
}

Button::~Button() {
}

void Button::render() {
    if(!visible)return;
    glTranslated(getX(), getY(), 0);
    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    {
        glVertex2d(0, 0);
        glVertex2d(w, 0);
        glVertex2d(w, h);
        glVertex2d(0, h);
    }
    glEnd();
    glTranslated(-getX(), -getY(), 0);
}

void Button::clicked(Mouse* m) {
    if(click != NULL)
        click(m);
}

void Button::hovered(Mouse* m) {
    if(hover != NULL)
        hover(m);
}

void Button::setClickListener(void(*callback)(Mouse*)) {
    click = callback;
}

void Button::setHoverListener(void(*callback)(Mouse*)) {
    hover = callback;
}
