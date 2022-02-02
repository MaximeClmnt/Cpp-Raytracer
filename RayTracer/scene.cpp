#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <random>

#include "scene.h"
#include "sphere.h"
#include "vector.h"
#include "ray.h"

std::default_random_engine engine;
std::uniform_real_distribution<double> distrib(0,1);


Scene::Scene(Scene& sc){
//    for(auto& sph: _spheres){
//        _spheres.push_back(sc);
//    }
    
    _light_center = sc._light_center;
    _light_power = sc._light_power;
    _n_brdf = sc._n_brdf;
    _roh_brdf = sc._roh_brdf;
}

void Scene::add_sphere(Sphere sphere_){
    _spheres.push_back(sphere_);
}

void Scene::set_light(Vector light_center_, Vector light_power_){
    _light_power = light_power_;
    _light_center = light_center_;
}

void Scene::set_light(Vector light_center_, float light_power_){
    _light_power = light_power_ * Vector(1.,1.,1.);
    _light_center = light_center_;
}

void Scene::set_n_brdf(int n_brdf_){
    _n_brdf = n_brdf_;
}

void Scene::set_roh_brdf(float roh_brdf_){
    _roh_brdf = roh_brdf_;
}

Vector Scene::get_color(Ray& r, int n_reflect){

    Hit hit(r);
    Vector color = Vector(0,0,0);
    
    for(Sphere& sph: _spheres) {
        sph.intersect(r,hit);
    }
    if(hit.compute()){
        color = Vector(1000.,1000.,1000);
    }

    return color;
}
