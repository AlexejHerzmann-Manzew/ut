/* 
 * File:   Keyboard.hpp
 * Author: yew_mentzaki
 *
 * Created on May 8, 2015, 9:03 PM
 */

#ifndef KEYBOARD_HPP
#define	KEYBOARD_HPP

class Keyboard {
public:
    Keyboard();
    Keyboard(const Keyboard& orig);
    virtual ~Keyboard();
    bool isButtonDownChar(unsigned char);
    bool isButtonDownCode(int);
    void updateChar(unsigned char, int, int);
    void updateCharUp(unsigned char, int, int);
    void updateSpecial(int, int, int);
    void updateSpecialUp(int, int, int);
private:
    bool keyChar[256];
    bool keySpecial[256];
};

#endif	/* KEYBOARD_HPP */

