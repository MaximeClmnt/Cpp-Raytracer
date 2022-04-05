#ifndef scene_h
#define scene_h

#include "vector.h"
#include "sphere.h"
#include "ray.h"
#include <random>

class Scene{
    std::vector<Sphere> _spheres;
    
    Sphere *_light;
    Vector _light_power;
    
    int _n_brdf;
    std::vector<Vector> _vect_brdf;
    float _roh_brdf;

    
    std::default_random_engine engine;
    std::uniform_real_distribution<double> distrib;
    
    
public:
    Scene(){
        _spheres = {};
        _n_brdf = 0;
        _roh_brdf = 0.;
    }
    Scene(Scene& sc);
    
    void add_sphere(Sphere sphere_);
    void set_light(Sphere* light_, float light_power_);
    void set_n_brdf(int n_brdf_);
    void set_roh_brdf(float roh_brdf_);
    Vector get_color(Ray& r, int n_reflect, bool show_light = true);
    
};

#endif /* scene_h */
