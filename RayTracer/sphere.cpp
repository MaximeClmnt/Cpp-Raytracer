//
//  sphere.cpp
//  
//
//  Created by José Magalhaes  on 19/01/2022.
//

#include "sphere.h"
#include <math.h>


bool Sphere::intersect(Ray& r, Vector& hit_pos, Vector& hit_norm, float& hit_dist){
    Vector diff(r.get_origin()-_center);
    float b = 2 * r.get_direction().dot(diff);
    float c = diff.sq_norm() - _sq_radius;
    float delta = b*b - 4*c; //Hypothese que a=1 car on normalise les direction des rays
    float t = 0;
    
    
    if(delta > 0.00001){
        t = (-b-sqrt(delta))/2.;
        if(t<=0)
            t = (-b+sqrt(delta))/2.;
        hit_pos = r.get_point_at(t);
        hit_norm = (hit_pos - _center).normalize();
        if(_radius < 0)
            hit_norm = (_center - hit_pos).normalize();;
        hit_dist = (r.get_origin()-hit_pos).norm();
        
    }
    
    return delta > 0.00001 && t>=0;
}

void Sphere::set_radius(const float radius_){
    _radius = radius_;
    _sq_radius = _radius*_radius;
}


Material& Sphere::get_material(){
    return _material;
}
