/* 
 * File:   Keyboard.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 8, 2015, 9:03 PM
 */

#include <X11/X.h>

#include "Keyboard.hpp"

Keyboard::Keyboard() {
}

Keyboard::Keyboard(const Keyboard& orig) {
}

Keyboard::~Keyboard() {
}

bool Keyboard::isButtonDownChar(unsigned char key) {
    return keyChar[key];
}

bool Keyboard::isButtonDownCode(int key) {
    return keySpecial[key];
}

void Keyboard::updateChar(unsigned char c, int x, int y) {
    keyChar[c] = true;
}

void Keyboard::updateSpecial(int c, int x, int y) {
    keySpecial[c] = true;
}

void Keyboard::updateCharUp(unsigned char c, int x, int y) {
    keyChar[c] = false;
}

void Keyboard::updateSpecialUp(int c, int x, int y) {
    keySpecial[c] = false;
}
