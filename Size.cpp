/* 
 * File:   Size.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 7, 2015, 10:46 PM
 */

#include "Size.hpp"

Size::Size() {
}

Size::Size(const Size& orig) {
}

Size::~Size() {
}

Size::Size(double width, double height) {
    this->width = width;
    this->height = height;
}
