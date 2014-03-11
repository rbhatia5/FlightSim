//
//  Matrix.cpp
//  FlightSim
//
//  Created by Rahul Bhatia on 3/10/14.
//  Copyright (c) 2014 Dastardly Design. All rights reserved.
//

#include "Matrix.h"

using namespace std;

template <typename T>

Matrix<T>::Matrix()
{
    height = 1;
    width = 1;
    value = (T *)malloc(sizeof(T) * height * width);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &cpy)
{
    height = cpy.height;
    width = cpy.width;
    value = (T *)malloc(sizeof(T) * height * width);
    
    for(int j = 0; j < height; j++)
        for(int i = 0; i < width; i++)
            this->setValue(cpy.getValue(i,j), i,j);
    
}

template<typename T>
Matrix<T>::Matrix(int h, int w)
{
    height = h;
    width = w;
    value = (T *)malloc(sizeof(T) * h * w);
    
}


template <typename T>
void Matrix<T>::setValue(T value, int y, int x)
{
    this->value[x + y*width] = value;
}

template <typename T>
T Matrix<T>::getValue(int y, int x) const
{
    return value[x + width*y];
}



template <typename T>
void Matrix<T>::setValuesFromArray( T arr[], int length)
{
    if(length == height*width)
    {
        for(int j = 0; j < height; j++)
            for(int i = 0; i < width; i++)
                value[i+width*j] = arr[i+width*j];
    }
}


template <typename T>
void Matrix<T>::print()
{
    cout << "{ ";
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            cout << value[i + width*j] << ",";
        }
        cout << "\n";
    }
    cout << "}" << endl;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const double &b)
{
    Matrix<T> cpy = *this;
    cpy *= b;
    
    return cpy;
}

template <typename T>
void Matrix<T>::operator*=(const double &b)
{
    for(int j = 0; j < height; j++)
        for(int i =0; i < width; i++)
            value[i+i*j] *= b;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other)
{
    if(this->getHeight() != other.getHeight() || this->getWidth() != other.getWidth())
        return Matrix<T>();
    else
    {
        Matrix<T> ret = Matrix<T>(*this);
        for(int j = 0; j < ret.getHeight(); j++)
            for(int i = 0; i < ret.getWidth(); i++)
                ret.setValue(other.getValue(j,i) + ret.getValue(j,i), j , i);
        
        return ret;
    }
}

template <typename T>
void Matrix<T>::operator+=(const Matrix<T> &other)
{
    if(this->getHeight() != other.getHeight() || this->getWidth() != other.getWidth())
        return;
    else
        for(int j = 0; j < this->getHeight(); j++)
            for(int i = 0; i < this->getWidth(); i++)
                this->setValue(other.getValue(j,i) + this->getValue(j,i), j , i);

    
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &b)
{
    if(getWidth() != b.getHeight())
        return Matrix<T>();
    
    Matrix<T> product = Matrix<T>(this->getHeight(), b.getWidth());
    
    for(int j = 0; j < product.getHeight(); j++)
        for(int i = 0; i < product.getWidth(); i++)
        {
            
            T sum= 0;
            
            for(int k = 0; k < this->getWidth(); k++)
            {
                sum += this->getValue(j,k) * b.getValue(k,i);
                
            }
            //cout << sum<<endl;
            product.setValue( sum, j, i);
        }
    
    return product;
}


template <typename T>
void Matrix<T>::operator*=(const Matrix<T> &b)
{
    if(getWidth() != b.getHeight())
        return;
    
    Matrix<T> product = Matrix<T>(this->getHeight(), b.getWidth());
    
    for(int j = 0; j < product.getHeight(); j++)
        for(int i = 0; i < product.getWidth(); i++)
        {
            
            T sum= 0;
            
            for(int k = 0; k < this->getWidth(); k++)
            {
                sum += this->getValue(j,k) * b.getValue(k,i);
                
            }
            //cout << sum<<endl;
            product.setValue( sum, j, i);
        }

    for(int j = 0; j < product.getHeight(); j++)
        for(int i = 0; i < product.getWidth(); i++)
            setValue(product.getValue(j,i), j, i);
    
}


template <typename T>
void Matrix<T>::operator=(const Matrix<T> &other)
{
    height = other.getHeight();
    width = other.getWidth();
    
    for(int  j = 0; j < other.getHeight(); j++)
        for( int i = 0; i < other.getWidth(); i++)
            setValue(other.getValue(j,i), j,i);
}




