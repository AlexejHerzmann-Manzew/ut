/* 
 * File:   Lebel.hpp
 * Author: yew_mentzaki
 *
 * Created on May 24, 2015, 1:19 PM
 */

#ifndef LEBEL_HPP
#define	LEBEL_HPP

#include <string>

#include "Element.hpp"


class Lebel : public Element{
public:
    std::string value;
    Lebel();
    Lebel(int x, int y, int w, int h, std::string str);
    Lebel(int x, int y, int w, int h, int align, std::string str);
    Lebel(const Lebel& orig);
    virtual void render();
    virtual ~Lebel();
private:

};

#endif	/* LEBEL_HPP */

