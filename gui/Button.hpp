/* 
 * File:   Button.hpp
 * Author: yew_mentzaki
 *
 * Created on May 18, 2015, 9:47 PM
 */

#include "Element.hpp"
#include "Frame.hpp"

#ifndef BUTTON_HPP
#define	BUTTON_HPP

class Button : public Element{
public:
    static Frame frame;
    
    Button();
    Button(const Button& orig);
    Button(int, int, int, int);
    Button(int, int, int, int, int);
    virtual void render();
    virtual ~Button();

    virtual void clicked(Mouse*);
    virtual void hovered(Mouse*);

    
    void setClickListener(void (*callback)(Mouse*));
    void setHoverListener(void (*callback)(Mouse*));

private:
    void (*click)(Mouse*);
    void (*hover)(Mouse*);
};

#endif	/* BUTTON_HPP */

