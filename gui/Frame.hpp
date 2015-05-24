/* 
 * File:   Frame.hpp
 * Author: yew_mentzaki
 *
 * Created on May 20, 2015, 8:31 PM
 */

#include <string>

#include "../Texture.hpp"

#ifndef FRAME_HPP
#define	FRAME_HPP

class Frame {
public:
    Texture angleTop, angleBottom, frameTop, frameBottom;
    Texture frameLeft, center;
    void render(int, int, int, int);
    Frame();

    Frame(std::string element) :
    center("res/gui/" + element + "/frame_center.png"),
    angleTop("res/gui/" + element + "/angle_top.png"),
    angleBottom("res/gui/" + element + "/angle_bottom.png"),
    frameTop("res/gui/" + element + "/frame_top.png"),
    frameLeft("res/gui/" + element + "/frame_left.png"),
    frameBottom("res/gui/" + element + "/frame_bottom.png") {
    }
    Frame(const Frame& orig);
    virtual ~Frame();
private:
    static void renderQuad(int, int);
    static void renderMirroredQuad(int, int);
};

#endif	/* FRAME_HPP */

