/* 
 * File:   Texture.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 5, 2015, 6:17 PM
 */

#include <GL/freeglut.h>
#include <string>
#include <GL/gl.h>

#include "Texture.h"

using namespace std;

Texture::Texture(string path) {
    this->path = path;
    this->texture = -1;
}

Texture::Texture(const Texture& orig) {
}

Texture::~Texture() {
    
}

void Texture::bind() {
    if (texture != -1) {
        glBindTexture(GL_TEXTURE_2D, texture);
    }else{
        
    }
}


