/* 
 * File:   main.cpp
 * Author: yew_mentzaki
 *
 * Created on May 3, 2015, 2:11 PM
 */



#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////

#include "Game.hpp"

using namespace std;

void setUpDisplay() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

Game game;
bool done = false;

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
}

void close(){
    glutDestroyWindow(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Underground Terror");
    setUpDisplay();
    glutIdleFunc(render);
    glutCloseFunc(close);
    glutMainLoop();
    return 0;
}