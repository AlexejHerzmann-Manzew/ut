/* 
 * File:   Size.hpp
 * Author: yew_mentzaki
 *
 * Created on May 7, 2015, 10:46 PM
 */

#ifndef SIZE_HPP
#define	SIZE_HPP

class Size {
public:
    Size();
    Size(double, double);
    Size(const Size& orig);
    double width, height;
    virtual ~Size();
private:

};

#endif	/* SIZE_HPP */

