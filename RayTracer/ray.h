//
//  ray.hpp
//  
//
//  Created by José Magalhaes  on 19/01/2022.
//
#include "vector.h"

#ifndef ray_h
#define ray_h

class Ray{
    Vector _origin;
    Vector _direction;
    
public:
    Ray(){}
    Ray(Vector origin_, Vector direction_);
    
    Vector& get_origin();
    Vector& get_direction();
    
    Vector get_point_at(const float t); //ori + t * dir
};

#endif /* ray_h */
