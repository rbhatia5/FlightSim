//
//  Vector.h
//  FlightSim
//
//  Created by Rahul Bhatia on 3/10/14.
//  Copyright (c) 2014 Dastardly Design. All rights reserved.
//

#ifndef __FlightSim__Vector__
#define __FlightSim__Vector__

#include <iostream>
#include "Matrix.h"


template <typename T> class Vector : public Matrix<T>
{
public:
    Vector();
    Vector(T x, T y, T z);
    
    void setX(T x);
    T getX();
    void setY(T x);
    T getY();
    void setZ(T x);
    T getZ();
    
    double getMagnitude();
    
    static Vector<T> cross(const Vector<T> &a, const Vector<T> &b);
    
    void rotateAroundVector(Vector<T> axis, double angle);
    
private:
    
    
    
};
#endif /* defined(__FlightSim__Vector__) */
