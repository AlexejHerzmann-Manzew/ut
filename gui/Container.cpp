/* 
 * File:   Container.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 18, 2015, 8:33 PM
 */

#include <cstddef>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../Keyboard.hpp"
#include "../Mouse.hpp"

#include "Frame.hpp"
#include "Container.hpp"

Frame Container::frame("container");

Container::Container() {
    visible = true;
}

Container::Container(int x, int y, int w, int h) : Element(x, y, w, h) {
    visible = true;
}

Container::Container(int x, int y, int w, int h, int align) : Element(x, y, w, h, align) {
    visible = true;
}

Container::Container(const Container& orig) {
    visible = true;
}

Container::~Container() {
    visible = true;
}

bool Container::handleElement(Mouse* m, Keyboard* k) {
    if (!visible)return false;
    if (m->x >= getX() & m->x <= getX() + w & m->y >= getY() & m->y <= getY() + h) {
        for (int i = 63; i >= 0; i--) {
            if (elements[i] != NULL)
                if (elements[i]->handleElement(m, k))
                    return true;
        }
        hovered(m);
        if (m->isLeftReleased) {
            clicked(m);
            m->isLeftReleased = false;
        }
        return !transperent;
    }
    return false;
}

void Container::add(Element* e) {
    for (int i = 0; i < 64; i++) {
        if (elements[i] == NULL) {
            elements[i] = e;
            elements[i]->parent = this;
            return;
        }
    }
}

void Container::remove(Element* e) {
    for (int i = 0; i < 64; i++) {
        if (elements[i] == e) {
            elements[i]->parent = NULL;
            elements[i] = NULL;
            return;
        }
    }
}

void Container::render() {
    if (visible) {
        if (!transperent) {
            glColor3f(1, 1, 1);
            frame.render(getX(), getY(), w, h);
        }
        for (int i = 0; i < 64; i++) {
            if (elements[i] != NULL) {
                elements[i]->render();
            }
        }
    }
}
