/* 
 * File:   Element.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 18, 2015, 8:17 PM
 */

#include <cstddef>
#include <GL/glut.h>

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
    this->align = GUI_ELEMENT_NONE_ALIGN;
}

bool Element::handleElement(Mouse* m, Keyboard* k) {
    if (!visible)return false;
    if (m->x >= getX() & m->x <= getX() + w & m->x >= getX() & m->x <= getX() + w) {
        hovered(m);
        if (m->isLeftReleased)
            clicked(m);
        return true;
    }
    return false;
}

int Element::getX() {
    switch (align) {
        case GUI_ELEMENT_LEFT_ALIGN:
            if (parent != NULL) {
                return parent->getX();
            } else {
                return 0;
            }
            break;
        case GUI_ELEMENT_CENTER_ALIGN:
            if (parent != NULL) {
                return parent->getX() + (parent->w - w) / 2;
            } else {
                return (glutGet(GLUT_WINDOW_WIDTH) - w) / 2;
            }
            break;
        case GUI_ELEMENT_RIGHT_ALIGN:
            if (parent != NULL) {
                return parent->getX() - w;
            } else {
                return glutGet(GLUT_WINDOW_WIDTH) - w;
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
    if (parent != NULL) {
        return parent->getY() + y;
    } else {
        return y;
    }
}

void Element::clicked(Mouse*) {

}

void Element::hovered(Mouse*) {

}

void Element::render() {

}
