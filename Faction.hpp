/* 
 * File:   Faction.hpp
 * Author: yew_mentzaki
 *
 * Created on May 5, 2015, 9:29 PM
 */

#include <string>

#include "Color.hpp"

#ifndef FACTION_HPP
#define	FACTION_HPP

class Faction {
public:
    Faction(std::string, Color*);
    Faction(const Faction& orig);
    virtual ~Faction();
    Color* color;
    std::string name;
private:

};

#endif	/* FACTION_HPP */

