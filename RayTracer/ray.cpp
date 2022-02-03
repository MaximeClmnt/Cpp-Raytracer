#include "ray.h"
#include "vector.h"
#include "sphere.h"

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

bool Hit::has_hit(){
    return _has_hit;
}

bool Hit::compute(){
    if(_has_hit){
        _position = _ray.get_point_at(_distance_from_camera);
        _normal = _sphere->get_normal_at(_position);
        _has_hit = false;
        return true;
    }
    else 
        return false;
}


void Hit::update_if_closer(Sphere* new_sphere, float new_distance){
    if(new_distance < _distance_from_camera){
        _distance_from_camera = new_distance;
        _sphere = new_sphere;
        _has_hit = true;
    }
}

Vector& Hit::get_position(){
    return _position;
}
Vector& Hit::get_normal(){
    return _normal;
}

Material& Hit::get_material(){
    return _sphere->get_material();
}

float Hit::get_distance_from_camera(){
    return _distance_from_camera;
}

