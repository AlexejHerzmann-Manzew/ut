/* 
 * File:   Mouse.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 7, 2015, 10:19 PM
 */

#include <GL/freeglut.h>

#include "Mouse.hpp"

Mouse::Mouse() {
}

Mouse::Mouse(const Mouse& orig) {
}

Mouse::~Mouse() {
}

void Mouse::handleMouse(int button, int state, int x, int y) {
    this->dx = x - this->x;
    this->dy = y - this->y;
    this->x = x;
    this->y = y;
    if (button == GLUT_LEFT_BUTTON)
        this->left = state == GLUT_DOWN;
    if (button == GLUT_MIDDLE_BUTTON)
        this->middle = state == GLUT_DOWN;
    if (button == GLUT_RIGHT_BUTTON)
        this->right = state == GLUT_DOWN;
}

void Mouse::handleMouseMotion(int x, int y) {
    this->dx = x - this->x;
    this->dy = y - this->y;
    this->x = x;
    this->y = y;
}

