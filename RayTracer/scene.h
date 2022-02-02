//
//  scene.hpp
//  
//
//  Created by José Magalhaes  on 19/01/2022.
//

#include <vector>

#include "sphere.h"

#ifndef scene_h
#define scene_h

class Scene{
    std::vector<Sphere> _spheres;
    
    Vector _light_center;
    Vector _light_power;
    
    int _n_brdf;
    std::vector<Vector> _vect_brdf;
    float _roh_brdf;
    
    
public:
    Scene(){
        _spheres = {};
        _n_brdf = 0;
        _roh_brdf = 0.;
    }
    Scene(Scene& sc);
    
    void add_sphere(Sphere sphere_);
    void set_light(Vector light_center_, float light_power_);
    void set_light(Vector light_center_, Vector light_power_);
    void set_n_brdf(int n_brdf_);
    void set_roh_brdf(float roh_brdf_);
    Vector get_color(Ray& r, int n_reflect);
    
};

#endif /* scene_h */
