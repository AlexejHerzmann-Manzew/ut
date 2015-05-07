/* 
 * File:   Texture.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 6, 2015, 10:29 PM
 */

#include <GL/gl.h>
#include <string>

#include "Texture.hpp"

using namespace std;

static int textureIndex = 0;

Texture::Texture() {
    this->texture = -1;
}

Texture::Texture(string path) {
    this->path = path;
    this->texture = -1;
}

void Texture::bind() {
    if (this->texture == -1) {
    }
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

Texture::Texture(const Texture& orig) {
}

Texture::~Texture() {
}

