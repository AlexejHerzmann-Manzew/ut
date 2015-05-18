/* 
 * File:   Math.cpp
 * Author: yew_mentzaki
 * 
 * Created on May 18, 2015, 7:55 PM
 */

#include "Math.hpp"

double abs(double a) {
    if(a >= 0)
        return a;
    else
        return -a;
}

double max(double a, double b) {
    if(a>b)
        return a;
    else
        return b;
}

double min(double a, double b) {
    if(a<b)
        return a;
    else
        return b;
}