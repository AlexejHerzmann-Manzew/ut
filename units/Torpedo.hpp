/* 
 * File:   BattleDriller.hpp
 * Author: yew_mentzaki
 *
 * Created on May 10, 2015, 11:37 AM
 */

#include "../Unit.hpp"
#include "../Texture.hpp"

#ifndef TORPEDO_HPP
#define	TORPEDO_HPP

class Torpedo : public Unit{
public:
    Torpedo();
    
    Torpedo(double x, double y, double a, int f);
    
    Torpedo(double x, double y, double tx, double ty, int target);
    
    virtual void init();

    virtual void renderIntefaceVirtual();

    virtual void renderVirual();

    virtual void smallTickVirtual();

    virtual void tickVirtual();
    
    virtual ~Torpedo();
private:
    static Texture texture;
};

#endif	/* TORPEDO_HPP */

