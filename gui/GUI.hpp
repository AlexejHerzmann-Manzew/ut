/* 
 * File:   GUI.hpp
 * Author: yew_mentzaki
 *
 * Created on May 18, 2015, 11:21 PM
 */

#ifndef GUI_HPP
#define	GUI_HPP

#include "Button.hpp"
#include "Container.hpp"
#include "Element.hpp"

class GUI {
public:
    GUI();
    GUI(const GUI& orig);
    virtual ~GUI();
    bool handleElement(Mouse, Keyboard);
    void add(Element*);
    void remove(Element*);
    void render();
private:
    Element* elements[64];
};

#endif	/* GUI_HPP */

