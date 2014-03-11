//
//  Matrix.h
//  FlightSim
//
//  Created by Rahul Bhatia on 3/10/14.
//  Copyright (c) 2014 Dastardly Design. All rights reserved.
//

#ifndef __FlightSim__Matrix__
#define __FlightSim__Matrix__

#include <iostream>

template<typename T> class Matrix {


public:
    
    Matrix();
    Matrix(int h, int w);
    Matrix(const Matrix<T> &cpy);
    
    
    void setValue(T value, int height, int width);
    
    T getValue(int height, int width) const;
    
    int getWidth() const { return width;};
    int getHeight() const { return height;};
    
    void setValuesFromArray( T * arr, int length);
    
    void print();
    
    Matrix<T> operator*(const double &b) ;
    void operator*=(const double &b) ;
    
    Matrix<T> operator*(const Matrix<T> &b) ;
    void operator*=(const Matrix<T> &b) ;
    
    Matrix<T> operator+(const Matrix<T> &other) ;
    void operator+=(const Matrix<T> &other) ;
    
    void operator=(const Matrix<T> &other); 
    
protected:
    T * value;
    int height,width;
    
    
    
};



#endif /* defined(__FlightSim__Matrix__) */
