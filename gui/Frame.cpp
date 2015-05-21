/* 
 * File:   Frame.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 20, 2015, 8:31 PM
 */

#include <GL/gl.h>

#include "Frame.hpp"
#include "../Texture.hpp"

Frame::Frame() {
}

Frame::Frame(const Frame& orig) {
}

Frame::~Frame() {
}

Texture Frame::center("res/gui/frame_center.png");
Texture Frame::frameBottom("res/gui/frame_bottom.png");
Texture Frame::frameLeft("res/gui/frame_left.png");
Texture Frame::frameTop("res/gui/frame_top.png");
Texture Frame::angleBottom("res/gui/angle_bottom.png");
Texture Frame::angleTop("res/gui/angle_top.png");

void Frame::render(int x, int y, int w, int h) {
    w /= 16;
    h /= 16;
    w--;
    h--;
    glTranslated(x, y, 0);
    angleTop.bind();
    renderQuad(0, 0);
    renderMirroredQuad(w, 0);
    angleBottom.bind();
    renderQuad(0, h);
    renderMirroredQuad(w, h);
    for (int i = 1; i < w; i++) {
        frameTop.bind();
        renderQuad(i, 0);
        frameBottom.bind();
        renderQuad(i, h);
    }
    frameLeft.bind();
    for (int i = 1; i < h; i++) {
        renderQuad(0, i);
        renderMirroredQuad(w, i);
    }
    center.bind();
    for (int i = 1; i < w; i++) {
        for (int j = 1; j < h; j++) {
            renderQuad(i, j);
        }
    }
    glTranslated(-x, -y, 0);
    Texture::unbind();
}

void Frame::renderQuad(int x, int y) {
    glTranslated(x * 16, y * 16, 0);
    glBegin(GL_QUADS);
    {
        int linesize = 8;
        glVertex2f(-linesize, linesize);
        glTexCoord2f(0, 0);

        glVertex2f(-linesize, -linesize);
        glTexCoord2f(1, 0);

        glVertex2f(linesize, -linesize);
        glTexCoord2f(1, 1);

        glVertex2f(linesize, linesize);
        glTexCoord2f(0, 1);
    }
    glEnd();
    glTranslated(-x * 16, -y * 16, 0);
}

void Frame::renderMirroredQuad(int x, int y) {
    glTranslated(x * 16, y * 16, 0);
    glBegin(GL_QUADS);
    {
        int linesize = 8;
        glVertex2f(linesize, linesize);
        glTexCoord2f(0, 0);

        glVertex2f(linesize, -linesize);
        glTexCoord2f(1, 0);

        glVertex2f(-linesize, -linesize);
        glTexCoord2f(1, 1);

        glVertex2f(-linesize, linesize);
        glTexCoord2f(0, 1);
    }
    glEnd();
    glTranslated(-x * 16, -y * 16, 0);
}
