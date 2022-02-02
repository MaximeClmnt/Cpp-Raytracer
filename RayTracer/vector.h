//
//  sphere.h
//  
//
//  Created by Maxime CLEMENT  on 18/01/2022.
//
#include <iostream>

#ifndef vector_h
#define vector_h

class Vector{
    float _x;
    float _y;
    float _z;
    
public :
    Vector(){}
    Vector(float x_, float y_, float z_):_x(x_),_y(y_),_z(z_){}
    Vector(const Vector &v);
    //~Vector()
    
    //Operators
    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector &v);
    Vector& operator*=(const float f);
    Vector& operator/=(const float f);
    
    void show(std::ostream &os) const;
    
    float dot(const Vector &v);
    Vector cross(const Vector &v);
    
    //norms
    float sq_norm();
    float norm();
    Vector& normalize();
    
    //getters
    float get_x() const;
    float get_y() const;
    float get_z() const;
};

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);
Vector operator*(const Vector& v, const float f);
Vector operator*(const Vector& a, const Vector& b);
Vector operator*(const float f, const Vector& v);
Vector operator/(const Vector& v, const float f);

std::ostream &operator<<( std::ostream &os, Vector const& v);

#endif /* vector_h */
