#ifndef ray_h
#define ray_h

#include "vector.h"
#include "sphere.h"
class Sphere;

class Ray{
    Vector _origin;
    Vector _direction;
    
public:
    Ray(){}
    Ray(Vector origin_, Vector direction_);
    
    Vector& get_origin();
    Vector& get_direction();

    void setDirection();
    //void test(Sphere sph){}
    
    Vector get_point_at(const float t); //ori + t * dir
};



class Hit{
    Ray& _ray;
    Sphere* _sphere;
    bool _has_hit;
    float _distance_from_camera;
    //To be computed once closest has been found
    Vector _position;
    Vector _normal;

public:
    static constexpr float max_distance = 1000.0;

    Hit();
    Hit(Ray& ray_): _ray(ray_),_has_hit(false),_distance_from_camera(max_distance){}; //1000 = max distances

    bool has_hit();
    bool compute();
    void update_if_closer(Sphere* new_sphere, float new_distance);
    Vector& get_position();
    Vector& get_normal();
    Material& get_material();
    float get_distance_from_camera();
};

#endif /* ray_h */
