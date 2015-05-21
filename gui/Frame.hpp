/* 
 * File:   Frame.hpp
 * Author: yew_mentzaki
 *
 * Created on May 20, 2015, 8:31 PM
 */

#include "../Texture.hpp"

#ifndef FRAME_HPP
#define	FRAME_HPP

class Frame {
public:
    static Texture angleTop, angleBottom, frameTop, frameBottom;
    static Texture frameLeft, center;
    static void render(int, int, int, int);
    Frame();
    Frame(const Frame& orig);
    virtual ~Frame();
private:
    static void renderQuad(int, int);
    static void renderMirroredQuad(int, int);
};

#endif	/* FRAME_HPP */

