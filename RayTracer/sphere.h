
#ifndef sphere_h
#define sphere_h

#include "vector.h"
#include "material.h"
#include "ray.h"
class Ray;
class Hit;

class Sphere{
    Vector _center;
    Material _material;
    bool isLight;
    
    float _radius;
    float _sq_radius;
    
public:
    Sphere(){}
    Sphere(Vector center_, float radius_): _center(center_), _radius(radius_){
        _sq_radius = _radius*_radius;
        _material = Material();
        isLight = false;
    }
    
    Sphere(Vector center_, float radius_, Material material_): _center(center_), _radius(radius_), _material(material_){
        _sq_radius = _radius*_radius;
        isLight = false;
    }
    
    void intersect(Ray& r, Hit& hit); 

    Vector get_normal_at(Vector& position);
    
    void set_radius(const float radius_);
    
    Material& get_material();

    void set_light();
    bool is_light();

    Vector getCenter();
    float getRadius();
    
    
};

#endif /* sphere_h */
