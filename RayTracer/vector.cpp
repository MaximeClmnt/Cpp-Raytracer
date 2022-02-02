//
//  sphere.cpp
//  
//
//  Created by Maxime CLEMENT  on 18/01/2022.
//
#include <math.h>

#include "vector.h"

Vector::Vector(const Vector &v){
    _x = v._x;
    _y = v._y;
    _z = v._z;
}
//~Vector()

//Opérators
Vector& Vector::operator+=(const Vector& v){
    _x+=v._x;
    _y+=v._y;
    _z+=v._z;
    return *this;
}

Vector& Vector::operator-=(const Vector& v){
    _x-=v._x;
    _y-=v._y;
    _z-=v._z;
    return *this;
}

Vector& Vector::operator*=(const float f){
    _x*=f;
    _y*=f;
    _z*=f;
    return *this;
}

Vector& Vector::operator/=(const float f){
    _x/=f;
    _y/=f;
    _z/=f;
    return *this;
}

float Vector::dot(const Vector &v){
    return _x*v._x + _y*v._y + _z*v._z;
}

Vector Vector::cross(const Vector &v){
    Vector crs(_y*v._z - _z*v._y,
               _z*v._x - _x*v._z,
               _x*v._y - _y*v._x);
    return crs;
}

float Vector::sq_norm(){
    return _x*_x +_y*_y + _z*_z;
}

float Vector::norm(){
    return sqrt(sq_norm());
}

Vector& Vector::normalize(){
    float nrm = norm();
    *this/=nrm;
    return *this;
}


float Vector::get_x() const{
    return _x;
}
float Vector::get_y() const{
    return _y;
}
float Vector::get_z() const{
    return _z;
}


Vector operator+(const Vector& a, const Vector& b){
    Vector cpy(a);
    cpy += b;
    return cpy;
}

Vector operator-(const Vector& a, const Vector& b){
    Vector cpy(a);
    cpy -= b;
    return cpy;
}

Vector operator*(const Vector& v, const float f){
    Vector cpy(v);
    cpy *= f;
    return cpy;
}

Vector operator*(const float f, const Vector& v){
    Vector cpy(v);
    cpy *= f;
    return cpy;
}

Vector operator*(const Vector& a, const Vector& b){
    return Vector(a.get_x()*b.get_x(),a.get_y()*b.get_y(),a.get_z()*b.get_z());
}

Vector operator/(const Vector& v, const float f){
    Vector cpy(v);
    cpy /= f;
    return cpy;
}

void Vector::show(std::ostream &flux) const{
    flux << "(" << _x << "," << _y << "," << _z <<")";
}

std::ostream &operator<<( std::ostream &os, Vector const& v)
{
    v.show(os) ;
    return os;
}

