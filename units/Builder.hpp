/* 
 * File:   BattleDriller.hpp
 * Author: yew_mentzaki
 *
 * Created on May 10, 2015, 11:37 AM
 */

#include "../Unit.hpp"
#include "../Texture.hpp"

#ifndef BUILDER_HPP
#define	BUILDER_HPP

class Builder : public Unit{
public:
    Builder();
    
    Builder(double x, double y, double a, int f);
    
    virtual void init();

    virtual void renderIntefaceVirtual();

    virtual void renderVirual();

    virtual void smallTickVirtual();

    virtual void tickVirtual();
    
    virtual ~Builder();
private:
    static Texture texture;
    static Texture texture_team;
};

#endif	/* BUILDER_HPP */

