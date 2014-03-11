//
//  Vector.cpp
//  FlightSim
//
//  Created by Rahul Bhatia on 3/10/14.
//  Copyright (c) 2014 Dastardly Design. All rights reserved.
//

#include "Vector.h"


template <typename T>
Vector<T>::Vector(){
    Vector::value = (T *)malloc(sizeof(T) * 3);
    Vector::width = 3;
    Vector::height = 1;
}

template <typename T>
Vector<T>::Vector(T x, T y, T z){
    Vector::value = (T *)malloc(sizeof(T) * 3);
    Vector::width = 3;
    Vector::height = 1;
    
    Vector::value[0] = x;
    Vector::value[1] = y;
    Vector::value[2] = z;

}

template <typename T>
void Vector<T>::setX(T x){
    Vector::value[0] = x;
}

template <typename T>
T Vector<T>::getX(){
    return Vector::value[0];
}
template<typename T>
void Vector<T>::setY(T x){
    Vector::value[1] = x;
}

template<typename T>
T Vector<T>::getY(){
    return Vector::value[1];
}

template<typename T>
void Vector<T>::setZ(T x){
    Vector::value[2] = x;
}

template<typename T>
T Vector<T>::getZ(){
    return Vector::value[2];
}

template<typename T>
double Vector<T>::getMagnitude()
{
    return sqrt(pow(getX(), 2) + pow(getY(), 2) + pow(getZ(), 2));
}

template<typename T>
Vector<T> Vector<T>::cross(const Vector<T> &a, const Vector<T> &b)
{
    Vector<T> product = Vector<T>();
    
    product.setX(a.getY() * b.getZ() - b.getY() * a.getZ());
    product.setY(a.getX() * b.getZ() - b.getX() * a.getZ());
    product.setZ(a.getX() * b.getY() - b.getX() * a.getY());
    
    return product; 
}

template<typename T>
void Vector<T>::rotateAroundVector(Vector<T> axis, double angle)
{
    
    
    
}





