//
//  ray.cpp
//  
//
//  Created by José Magalhaes  on 19/01/2022.
//

#include "ray.h"

Ray::Ray(Vector origin_, Vector direction_){
    _origin = origin_;
    _direction = Vector(direction_).normalize();
}

Vector& Ray::get_origin(){
    return _origin;
}

Vector& Ray::get_direction(){
    return _direction;
}

Vector Ray::get_point_at(const float t){
    return _origin + t * _direction;
}
