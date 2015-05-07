/* 
 * File:   main.cpp
 * Author: yew_mentzaki
 *
 * Created on May 3, 2015, 2:11 PM
 */

#include <iostream>
#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <thread>
#include <ctime>

////////////////////////////////////////////

#include "Game.hpp"

using namespace std;

void setUpDisplay() {
    glClearColor(0.4, 0.8, 1.0, 1.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
}

int fps = 0;
int frame = 0, ttime, timebase = 0;

Game game;
bool done = false;

void handleMouse(int button, int state, int x, int y) {
    game.handleMouse(button, state, x, y);
}

void handleMouseMotion(int x, int y) {
    game.handleMouseMotion(x, y);
}

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
    glFlush();
    
    frame++;
    ttime = glutGet(GLUT_ELAPSED_TIME);

    if (ttime - timebase > 1000) {
        fps = frame * 1000.0 / (ttime - timebase);
        timebase = ttime;
        frame = 0;
        cout << "fps: " << fps << endl;
    }
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
    glutPassiveMotionFunc(handleMouseMotion);
    thread tickT(tickThread);
    tickT.detach();
    thread smallTickT(smallTickThread);
    smallTickT.detach();
    glutMainLoop();
    return 0;
}