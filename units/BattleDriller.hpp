/* 
 * File:   BattleDriller.hpp
 * Author: yew_mentzaki
 *
 * Created on May 10, 2015, 11:37 AM
 */

#include "../Unit.hpp"
#include "../Texture.hpp"

#ifndef BATTLEDRILLER_HPP
#define	BATTLEDRILLER_HPP

class BattleDriller : public Unit{
public:
    BattleDriller();
    
    BattleDriller(double x, double y, double a, int f);
    
    virtual void init();

    virtual void renderIntefaceVirtual();

    virtual void renderVirual();

    virtual void smallTickVirtual();

    virtual void tickVirtual();
    
    virtual ~BattleDriller();
private:
    static Texture texture;
    static Texture texture_team;
    static Texture texture_turret;
};

#endif	/* BATTLEDRILLER_HPP */

