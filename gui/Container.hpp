/* 
 * File:   Container.hpp
 * Author: yew_mentzaki
 *
 * Created on May 18, 2015, 8:33 PM
 */

#ifndef CONTAINER_HPP
#define	CONTAINER_HPP

#include "../Keyboard.hpp"
#include "../Mouse.hpp"

#include "Element.hpp"

class Container : public Element{
public:
    Container();
    Container(int, int, int, int, int);
    Container(int, int, int, int);
    Container(const Container& orig);

    virtual void render();
    bool transperent;

    virtual bool handleElement(Mouse*, Keyboard*);

    void add(Element*);
    void remove(Element*);

    virtual ~Container();
private:
    Element* elements[64];
};

#endif	/* CONTAINER_HPP */

