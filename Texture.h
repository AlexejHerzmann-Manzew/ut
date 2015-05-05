/* 
 * File:   Texture.h
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 6:17 PM
 */

#include <string>

#ifndef TEXTURE_H
#define	TEXTURE_H

class Texture {
public:
    Texture(std::string);
    Texture(const Texture& orig);
    virtual ~Texture();
    void bind();
    unsigned int width = 256, height = 256;
private:
    std::string path;
    int texture;
};

#endif	/* TEXTURE_H */

