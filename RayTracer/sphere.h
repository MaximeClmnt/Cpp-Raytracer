//
//  sphere.hpp
//  
//
//  Created by José Magalhaes  on 19/01/2022.
//
#include "vector.h"
#include "ray.h"
#include "material.h"

#ifndef sphere_h
#define sphere_h

class Sphere{
    Vector _center;
    Material _material;
    
    float _radius;
    float _sq_radius;
    
public:
    Sphere(){}
    Sphere(Vector center_, float radius_): _center(center_), _radius(radius_){
        _sq_radius = _radius*_radius;
        _material = Material();
    }
    
    Sphere(Vector center_, float radius_, Material material_): _center(center_), _radius(radius_), _material(material_){
        _sq_radius = _radius*_radius;
    }
    
    bool intersect(Ray& r, Vector& hit_pos, Vector& hit_norm, float& hit_dist);
    
    void set_radius(const float radius_);
    
    Material& get_material();
    
    
};

#endif /* sphere_h */
