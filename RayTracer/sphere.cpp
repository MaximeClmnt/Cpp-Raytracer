#include <math.h>

#include "sphere.h"
#include "vector.h"
#include "ray.h"


void Sphere::intersect(Ray& ray, Hit& hit){
    Vector diff(ray.get_origin()-_center);
    float b = 2 * ray.get_direction().dot(diff);
    float c = diff.sq_norm() - _sq_radius;
    float delta = b*b - 4*c; //Hypothese que a=1 car on normalise les direction des rays
    float t;
    bool hit_flag = false;
    if(delta > 0){ //HIT !!
        t = (-b-sqrt(delta))/2.;
        if(t<=0)
            t = (-b+sqrt(delta))/2.;
        if(t > 0){
            hit.update_if_closer(this, t);
        }
    }
}

Vector Sphere::get_normal_at(Vector& position){
    if(_radius > 0)
        return (position - _center).normalize();
    else
        return (_center - position).normalize();
}

void Sphere::set_radius(const float radius_){
    _radius = radius_;
    _sq_radius = _radius*_radius;
}


Material& Sphere::get_material(){
    return _material;
}

Vector Sphere::getCenter(){
    return _center;
}

void Sphere::set_light(){
    isLight = true;
}

bool Sphere::is_light(){
    return isLight;
}


float Sphere::getRadius(){
    return _radius;
}
