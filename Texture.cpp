/* 
 * File:   Texture.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 6, 2015, 10:29 PM
 */

#include <IL/il.h>
#include <IL/ilu.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include "Texture.hpp"

using namespace std;

unsigned int Texture::nextTextureIndex = 1;

void Texture::bind() {
    if (texture == 100500) {
        texture = nextTextureIndex;
        nextTextureIndex++;
        bool b = ilLoadImage(name.c_str());
        int err = ilGetError();
        if (err != IL_NO_ERROR) {
            cerr << "Texture loading error! [" << err << "]" << endl;
            cerr << iluErrorString(err) << endl;
            texture = 228500;
            return;
        }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        width = ilGetInteger(IL_IMAGE_WIDTH);
        height = ilGetInteger(IL_IMAGE_HEIGHT);
        cout << ilGetInteger(IL_IMAGE_FORMAT) << endl;
        cout << ilGetInteger(IL_IMAGE_TYPE) << endl;
        cout << width << ":" << height << endl;
        unsigned int type;
        switch (ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL)) {
            case 1:
                type = GL_RGB8;
                break;
            case 3:
                type = GL_RGB;
                break;
            case 4:
                type = GL_RGBA;
                break;
        }
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, type,
                GL_UNSIGNED_BYTE, ilGetData());
    } else if (texture == 228500) {
        glBindTexture(GL_TEXTURE_2D, 0);
        return;
    } else {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture() {

}

Texture::Texture(const Texture& origin){
    
}

Texture::Texture(Texture* t) {
    name = t->name;
    cout << name << endl;
}

Texture::Texture(std::string n) {
    name = n;
    texture = 100500;
}

Texture::~Texture() {

}
