#define _CRT_SECURE_NO_WARNINGS 1
#include <vector>
 
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#define _USE_MATH_DEFINES
#include <math.h>

#include <assert.h>
#include <iostream>

#include "vector.h"
#include "scene.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
 
int main() {
    int W = 512;
    int H = 512;
    
    Vector cam_center(-0.,.6,0.);
    float fov = M_PI/2;
    
    Scene scene;
    
    //Walls
    /*
    scene.add_sphere(Sphere(Vector(0.,0.,-104.),100,MATERIAL_RED));
    scene.add_sphere(Sphere(Vector(0.,0.,+104.),100,MATERIAL_CYAN));
    scene.add_sphere(Sphere(Vector(-103.,0.,0.),100,MATERIAL_BLUE));
    scene.add_sphere(Sphere(Vector(+103.,0.,0.),100,MATERIAL_YELLOW));
    scene.add_sphere(Sphere(Vector(0.,-100.,0.),100,MATERIAL_GREEN));
    scene.add_sphere(Sphere(Vector(0.,+103.,0.),100,MATERIAL_MAGENTA));
    */
   
    //Center Sphere
    //scene.add_sphere(Sphere(Vector(0.4,0.4,-2.),.4,MATERIAL_MIRROR));
    scene.add_sphere(Sphere(Vector(0.,0.6,-1.),0.5,Material(Vector(0, 0, 0),MATERIAL_TYPE_TRANSPARENT,1.1)));
    //scene.add_sphere(Sphere(Vector(0.,0.6,-1.),-0.49,Material(Vector(0, 0, 0),MATERIAL_TYPE_TRANSPARENT,1.1)));
    
    scene.set_light(Vector(1.,2.,0.), 1000000.);
    scene.set_n_brdf(0);
    scene.set_roh_brdf(0.6);
    
    std::vector<unsigned char> image(W*H * 3, 0);
    
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            Vector ray_dir(j-W/2+.5,-i+H/2-.5,-H/(2*tan(fov/2)));
            Ray r(cam_center,ray_dir);
            
            Vector color = scene.get_color(r,5);
            
            image[(i*W + j) * 3 + 0] = fmin(255,pow(color.get_x(),1/2.2));
            image[(i*W + j) * 3 + 1] = fmin(255,pow(color.get_y(),1/2.2));
            image[(i*W + j) * 3 + 2] = fmin(255,pow(color.get_z(),1/2.2));
        }
        std::cout << i << std::endl;

    }
    
    stbi_write_png("C:\\Users\\ASUS\\OneDrive\\Documents\\Cours\\ECL-3A\\MOS_2.2-Informatique_Graphique\\CG\\RayTracer\\RayTracer\\image.png", W, H, 3, &image[0], 0);
    
    return 0;
}
