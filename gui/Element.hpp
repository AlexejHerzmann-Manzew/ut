/* 
 * File:   Element.hpp
 * Author: yew_mentzaki
 *
 * Created on May 18, 2015, 8:17 PM
 */

#include "../Keyboard.hpp"
#include "../Mouse.hpp"

#ifndef ELEMENT_HPP
#define	ELEMENT_HPP

#define GUI_ELEMENT_NONE_ALIGN 0
#define GUI_ELEMENT_LEFT_ALIGN 1
#define GUI_ELEMENT_CENTER_ALIGN 2
#define GUI_ELEMENT_RIGHT_ALIGN 3

class Element {
public:
    int x, y, w, h, align;
    bool visible;
    int getX();
    int getY();
    Element();
    Element(int, int, int, int);
    Element(int, int, int, int, int);
    Element(const Element& orig);
    Element* parent;
    virtual bool handleElement(Mouse*, Keyboard*);
    virtual void clicked(Mouse*);
    virtual void hovered(Mouse*);
    virtual void render();
    virtual ~Element();
private:

};

#endif	/* ELEMENT_HPP */

