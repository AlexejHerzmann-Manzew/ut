/* 
 * File:   Texture.hpp
 * Author: yew_mentzaki
 *
 * Created on May 6, 2015, 10:29 PM
 */

#include <string>

#ifndef TEXTURE_HPP
#define	TEXTURE_HPP

class Texture {
public:
    Texture();
    Texture(std::string);
    Texture(const Texture& orig);
    void bind();
    virtual ~Texture();
private:
    std::string path;
    int texture;
};

#endif	/* TEXTURE_HPP */

