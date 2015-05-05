/* 
 * File:   Faction.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 5, 2015, 9:29 PM
 */

#include "Faction.hpp"

using namespace std;

Faction::Faction(string name, Color* color) {
    this->name = name;
    this->color = color;
}

Faction::Faction(const Faction& orig) {
}

Faction::~Faction() {
    color->~Color();
}

