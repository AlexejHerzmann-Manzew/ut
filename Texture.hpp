/* 
 * File:   Texture.hpp
 * Author: yew_mentzaki
 *
 * Created on May 6, 2015, 10:29 PM
 */

#include <string>
#include <vector>
#include <GL/gl.h>
#include <IL/il.h>

#ifndef TEXTURE_HPP
#define	TEXTURE_HPP


class Texture {
public:
    static void unbind();
    void bind();
    Texture();
    Texture(const Texture&);
    Texture(Texture*);
    Texture(std::string);
    ~Texture();
    std::string name;
    int width, height;
private:
    static unsigned int nextTextureIndex;
    ILuint texture;
};

#endif	/* TEXTURE_HPP */

