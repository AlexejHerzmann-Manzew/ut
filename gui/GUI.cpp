/* 
 * File:   GUI.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 18, 2015, 11:21 PM
 */


#include <cstddef>
#include <iostream>
#include <GL/glut.h>

#include "../Keyboard.hpp"
#include "../Mouse.hpp"

#include "GUI.hpp"

using namespace std;

GUI::GUI() {
}

GUI::GUI(const GUI& orig) {
}

GUI::~GUI() {
}

bool GUI::handleElement(Mouse* m, Keyboard* k) {
    for (int i = 63; i >= 0; i--) {
        if (elements[i] != NULL && elements[i]->handleElement(m, k))
            return true;
    }
    return false;
}

void GUI::add(Element* e) {
    for (int i = 0; i < 64; i++) {
        if (elements[i] == NULL) {
            elements[i] = e;
            return;
        }
    }
}

void GUI::remove(Element* e) {
    for (int i = 0; i < 64; i++) {
        if (elements[i] == e) {
            elements[i] = NULL;
            return;
        }
    }
}

void GUI::render() {
    for (int i = 0; i < 64; i++) {
        if (elements[i] != NULL)
            elements[i]->render();

    }
}
