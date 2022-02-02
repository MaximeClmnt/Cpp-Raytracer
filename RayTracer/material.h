//
//  material.hpp
//  
//
//  Created by José Magalhaes  on 19/01/2022.
//
#include "vector.h"

#ifndef material_h
#define material_h

#define MATERIAL_RED Material(Vector(1.,0.00001,0.00001))
#define MATERIAL_GREEN Material(Vector(0.00001,1.,0.00001))
#define MATERIAL_BLUE Material(Vector(0.00001,0.00001,1.00001))
#define MATERIAL_CYAN Material(Vector(0.00001,1.,1.))
#define MATERIAL_YELLOW Material(Vector(1.,1.,0.00001))
#define MATERIAL_MAGENTA Material(Vector(1.,0.00001,1.))
#define MATERIAL_WHITE Material(Vector(1.,1.,1.))

#define MATERIAL_MIRROR Material(Vector(1.,1.,1.),1)
#define MATERIAL_TRANSPARENT Material(Vector(1.,1.,1.),2)

#define MATERIAL_TYPE_DIFFUSE 0
#define MATERIAL_TYPE_MIRROR 1
#define MATERIAL_TYPE_TRANSPARENT 2

class Material{
    int _type;
    float _n_index;
    Vector _albedo;
    
public:
    Material();
    Material(Vector albedo_);
    Material(Vector albedo_,int type_);
    Material(Vector albedo_,int type_,float n_index_);
    
    Vector& get_albedo();
    bool is_mirror();
    bool is_transparent();
    float get_n_index();
};

#endif /* material_h */
