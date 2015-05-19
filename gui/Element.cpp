/* 
 * File:   Element.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 18, 2015, 8:17 PM
 */

#include <cstddef>
#include <GL/glut.h>
#include <GL/freeglut_std.h>

#include "../Keyboard.hpp"
#include "../Mouse.hpp"

#include "Element.hpp"

Element::Element() {
}

Element::Element(const Element& orig) {
}

Element::~Element() {
}

Element::Element(int x, int y, int w, int h, int align) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->align = align;
}

Element::Element(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->align = GUI_NONE_ALIGN;
}

bool Element::handleElement(Mouse* m, Keyboard* k) {
    if (!visible)return false;
    if (m->x >= getX() & m->x <= getX() + w & m->y >= getY() & m->y <= getY() + h) {
        hovered(m);
        if (m->isLeftReleased){
            clicked(m);
            m->isLeftReleased = false;
        }
        return true;
    }
    return false;
}

int Element::getX() {
    switch (align) {
        case GUI_LEFT_ALIGN:
            if (parent != NULL) {
                return parent->getX() + x;
            } else {
                return x;
            }
            break;
        case GUI_CENTER_ALIGN:
            if (parent != NULL) {
                return parent->getX() + (parent->w - w) / 2 + x;
            } else {
                return (glutGet(GLUT_WINDOW_WIDTH) - w) / 2 + x;
            }
            break;
        case GUI_RIGHT_ALIGN:
            if (parent != NULL) {
                return parent->getX() - w + x;
            } else {
                return glutGet(GLUT_WINDOW_WIDTH) - w + x;
            }
            break;
        default:
            if (parent != NULL) {
                return parent->getX() + x;
            } else {
                return x;
            }
            break;
    }
}

int Element::getY() {
    switch (verticalAlign) {
        case GUI_TOP_ALIGN:
            if (parent != NULL) {
                return parent->getY() + y;
            } else {
                return y;
            }
            break;
        case GUI_CENTER_ALIGN:
            if (parent != NULL) {
                return parent->getY() + (parent->h - h) / 2 + y;
            } else {
                return (glutGet(GLUT_WINDOW_HEIGHT) - h) / 2 + y;
            }
            break;
        case GUI_BOTTOM_ALIGN:
            if (parent != NULL) {
                return parent->getY() - h + y;
            } else {
                return glutGet(GLUT_WINDOW_HEIGHT) - h + y;
            }
            break;
        default:
            if (parent != NULL) {
                return parent->getY() + y;
            } else {
                return y;
            }
            break;
    }
}

void Element::clicked(Mouse*) {

}

void Element::hovered(Mouse*) {

}

void Element::render() {

}
