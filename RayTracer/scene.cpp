//
//  scene.cpp
//  
//
//  Created by José Magalhaes  on 19/01/2022.
//

#include "scene.h"
#include <math.h>
#include <iostream>
#include <random>

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
    Vector hit_pos;
    Vector hit_norm;
    float hit_dist;
    
    
    Vector hit_pos_1;
    Vector hit_norm_1;
    float hit_dist_1;
    
    float nearest = 100;
    
    Vector color;
    Vector color_global;
    
    for(auto& sph: _spheres) {
        if(sph.intersect(r, hit_pos, hit_norm, hit_dist) && hit_dist < nearest){
            //TODO : Record Hit and compute color after finding the nearest object  + delay compute hitinfo (pointer -> sphere, t = hit_dist) sufficient to compute all info?)
            hit_pos_1 = Vector(hit_pos);
            hit_norm_1 = Vector(hit_norm);
            hit_dist_1 = hit_dist;
            
            nearest = hit_dist;
            Material material = sph.get_material();
            
            if(material.is_mirror() && n_reflect>0){
                Ray reflect_ray(
                            hit_pos,
                            r.get_direction()-2.*(r.get_direction().dot(hit_norm))*hit_norm
                            );
                color = get_color(reflect_ray,n_reflect-1);
            }
            else if(material.is_transparent() && n_reflect>0){
                float n_mat = material.get_n_index(); //propritété du materiaux
                
                float n_frac;
                float inv_normal;
                float i_dot_n = hit_norm.dot(r.get_direction());
                if(i_dot_n < 0){ // on rentre dans le materiau
                    n_frac = 1./n_mat;
                    inv_normal = 1;
                }
                else{//on sort du materiaux
                    n_frac = n_mat;
                    inv_normal = -1;
                }
                
                double in_sqrt = 1. - n_frac*n_frac*(1.-i_dot_n*i_dot_n);
                if(in_sqrt<0){ //reflection
                    Ray reflect_ray(
                                    hit_pos + 0.0001 * hit_norm * inv_normal,
                                    r.get_direction()-2.*i_dot_n*hit_norm
                                    );
                    color = get_color(reflect_ray,n_reflect-1);

                }
                else{
                    Ray refract_ray(
                                    hit_pos - 0.0001 * hit_norm * inv_normal,
                                    n_frac*r.get_direction() - (n_frac*i_dot_n*inv_normal + sqrt(in_sqrt))*hit_norm*inv_normal
                                    );
                    Ray reflect_ray(
                                    hit_pos + 0.0001 * hit_norm * inv_normal,
                                    r.get_direction()-2.*i_dot_n*hit_norm
                                    );
                    float k0 = pow((1.0-n_mat),2)/pow((1.0+n_mat),2);
                    float R;
                    if(n_frac > 1) // 
                        R = k0 + (1.0-k0)*pow(1 - i_dot_n,5);
                    else
                        R = k0 + (1.0-k0)*pow(1 + i_dot_n,5);
                    color = get_color(refract_ray,n_reflect-1) * (1.0-R) + get_color(reflect_ray,n_reflect-1) * R;
                }
            }
            else{
                //Calcul de l'intensité lumineuse par la lumière directe
                Vector hit_to_light = (_light_center-hit_pos);
                float dist_to_light = hit_to_light.norm();
                Vector light_intensity = fmax(0.,(hit_to_light/dist_to_light).dot(hit_norm)) *_light_power/(dist_to_light*dist_to_light);
                
                Ray to_light = Ray(hit_pos+.0001*hit_norm,hit_to_light);
                bool inShadow = false;
                for(auto& sph: _spheres) {
                    if(sph.intersect(to_light, hit_pos, hit_norm, hit_dist) && hit_dist < dist_to_light){
                        inShadow = true;
                        break;
                    }
                }
                
                if(!inShadow){
                    color = light_intensity * material.get_albedo();
                }
                else{
                    color = Vector(0.,0.,0.);
                }
                
                //Prise en compte de la luminausié globale
                if(n_reflect>0 && _n_brdf){
                    Vector z = Vector(hit_norm_1);
                    Vector x = z.cross(Vector(1.,0.,0.));
                    if(x.sq_norm()<=0.01)
                        x = z.cross(Vector(0.,1.,0.));
                    x.normalize();
                    Vector y = z.cross(x);
                    
                    color_global = Vector(0.,0.,0.);
                    for(int k=0; k<_n_brdf ; k++){
                        float r1 = distrib(engine);
                        float r2 = distrib(engine);
                        
                        Vector ray_dir(
                                cos(2.*M_PI*r1)*sqrt(1.-r2) * x +
                                sin(2.*M_PI*r1)*sqrt(1.-r2) * y +
                                sqrt(r2) * z
                                       );
                        ray_dir.normalize();
                        
                        Ray random_ray(hit_pos_1+.0001*hit_norm_1,ray_dir);
                        
                        color_global = color_global + get_color(random_ray, 0);
                    }
                    color = color + color_global * material.get_albedo()/(float)(_n_brdf) * _roh_brdf;
                }
            }
        }
    }
    return color;
}
