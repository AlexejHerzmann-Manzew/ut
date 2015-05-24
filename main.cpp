/* 
 * File:   main.cpp
 * Author: yew_mentzaki
 *
 * Created on May 3, 2015, 2:11 PM
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <thread>
#include <ctime>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

////////////////////////////////////////////

#include "Game.hpp"
#include "Texture.hpp"

using namespace std;

void setUpDisplay() {
    glClearColor(0.4, 0.8, 1.0, 1.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_TEXTURE_2D);
    ilutRenderer(ILUT_OPENGL);
    ilInit();
    iluInit();
    ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);
    ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);
    ilutEnable(ILUT_OPENGL_CONV);
    ilutEnable(ILUT_GL_USE_S3TC);
}

int fps = 0;
int frame = 0, ttime, timebase = 0;

Game game;
bool done = false;

int mx, my;

void handleMouse(int button, int state, int x, int y) {
    game.handleMouse(button, state, x, y);
    mx = x;
    my = y;
}

void handleMouseMotion(int x, int y) {
    game.handleMouseMotion(x, y);
    mx = x;
    my = y;
}

int copyrastTimer = 15;
Texture by("res/by.png");
Texture cursorNormal("res/cursor/normal.png");

void render() {

    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    game.render();
    glEnd();
    glColor3f(1, 1, 1);

    glRasterPos2i(100, 120);
    string str = "Hello";
    cursorNormal.bind();
    glEnable(GL_BLEND);
    glBegin(GL_QUADS);
    {
        glVertex2d(mx, my + 32);
        glTexCoord2d(0, 0);

        glVertex2d(mx, my);
        glTexCoord2d(1, 0);

        glVertex2d(mx + 32, my);
        glTexCoord2d(1, 1);

        glVertex2d(mx + 32, my + 32);
        glTexCoord2d(0, 1);
    }
    glEnd();
    if (copyrastTimer > 0) {
        by.bind();
        glBegin(GL_QUADS);
        {
            glVertex2d(5, 69);
            glTexCoord2d(0, 0);

            glVertex2d(5, 5);
            glTexCoord2d(1, 0);

            glVertex2d(69, 5);
            glTexCoord2d(1, 1);

            glVertex2d(69, 69);
            glTexCoord2d(0, 1);
        }
        glEnd();
    }
    glDisable(GL_BLEND);
    Texture::unbind();
    glFlush();
    frame++;
    ttime = glutGet(GLUT_ELAPSED_TIME);

    if (ttime - timebase > 1000) {
        if(copyrastTimer > 0)
        copyrastTimer--;
        fps = frame * 1000.0 / (ttime - timebase);
        timebase = ttime;
        frame = 0;
        cout << "fps: " << fps << endl;
    }
}

void updateChar(unsigned char c, int x, int y) {
    game.updateChar(c, x, y);
}

void updateSpecial(int c, int x, int y) {
    game.updateSpecial(c, x, y);
}

void updateCharUp(unsigned char c, int x, int y) {
    game.updateCharUp(c, x, y);
}

void updateSpecialUp(int c, int x, int y) {
    game.updateSpecialUp(c, x, y);
}

void close() {
    glutDestroyWindow(0);
}

void tickThread() {
    while (true) {
        game.tick();
    }
}

void smallTickThread() {
    while (true) {
        game.smallTick();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Underground Terror");
    setUpDisplay();
    glutIdleFunc(render);
    glutCloseFunc(close);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMotion);
    glutKeyboardFunc(updateChar);
    glutKeyboardUpFunc(updateCharUp);
    glutSpecialFunc(updateSpecial);
    glutSpecialUpFunc(updateSpecialUp);
    glutPassiveMotionFunc(handleMouseMotion);
    glutSetCursor(GLUT_CURSOR_NONE);
    thread tickT(tickThread);
    tickT.detach();
    thread smallTickT(smallTickThread);
    smallTickT.detach();
    glutMainLoop();
    return 0;
}