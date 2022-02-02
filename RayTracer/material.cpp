#include "material.h"
#include "vector.h"

Material::Material(){
    _albedo = Vector(1.,1.,1.);
    _type = false;
}

Material::Material(Vector albedo_){
    _albedo = albedo_;
    _type = false;
}

Material::Material(Vector albedo_,int type_){
    _albedo = Vector(1.,1.,1.);
    _type = type_;
    _n_index = 1.5;
}

Material::Material(Vector albedo_,int type_,float n_index_){
    _albedo = Vector(1.,1.,1.);
    _type = type_;
    _n_index = n_index_;
}

Vector& Material::get_albedo(){
    return _albedo;
}

float Material::get_n_index(){
    return _n_index;
}

bool Material::is_mirror(){
    return _type == MATERIAL_TYPE_MIRROR;
}
bool Material::is_transparent(){
    return _type == MATERIAL_TYPE_TRANSPARENT;
}
