/* 
 * File:   Explossion.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 16, 2015, 11:16 AM
 */

#include <stdlib.h>

#include "Explossion.hpp"

Explossion::Explossion(double size, double x, double y) {
    this->size = size;
    this->x = x;
    this->y = y;
    this->a = rand();
}

void Explossion::render() {

}

void Explossion::tick() {

}

Explossion::Explossion() {
}

Explossion::Explossion(const Explossion& orig) {
}

Explossion::~Explossion() {
}

