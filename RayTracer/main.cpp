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


//#include <pthread.h>
#include <omp.h>

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
    
    scene.add_sphere(Sphere(Vector(0.,0.,-104.),100,MATERIAL_RED));
    scene.add_sphere(Sphere(Vector(0.,0.,+104.),100,MATERIAL_CYAN));
    scene.add_sphere(Sphere(Vector(-103.,0.,0.),100,MATERIAL_BLUE));
    scene.add_sphere(Sphere(Vector(+103.,0.,0.),100,MATERIAL_YELLOW));
    scene.add_sphere(Sphere(Vector(0.,-100.,0.),100,MATERIAL_GREEN));
    scene.add_sphere(Sphere(Vector(0.,+103.,0.),100,MATERIAL_MAGENTA));
    
   
    //Center Sphere
    scene.add_sphere(Sphere(Vector(0.4,0.4,-2.),.4,MATERIAL_MIRROR));
    scene.add_sphere(Sphere(Vector(0.,0.6,-1.),0.5,Material(Vector(0, 0, 0),MATERIAL_TYPE_TRANSPARENT,1.1)));
    scene.add_sphere(Sphere(Vector(0.,0.6,-1.),-0.49,Material(Vector(0, 0, 0),MATERIAL_TYPE_TRANSPARENT,1.1)));
    
    scene.set_light(Vector(1.,2.,0.), 1000000.);
    scene.set_n_brdf(50);
    scene.set_roh_brdf(0.6);
    
    std::vector<unsigned char> image(W*H * 3, 0);
    #pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < H; i++) {
        //std::cout<< omp_get_num_threads() << std::endl;
        for (int j = 0; j < W; j++) {
<<<<<<< Updated upstream
            if(true || (i==H/2 && j == W/2+1)){
=======
<<<<<<< Updated upstream
>>>>>>> Stashed changes
            Vector ray_dir(j-W/2+.5,-i+H/2-.5,-H/(2*tan(fov/2)));
            Ray r(cam_center,ray_dir);
            
            Vector color = scene.get_color(r,3);
            
            image[(i*W + j) * 3 + 0] = fmin(255,pow(color.get_x(),1/2.2));
            image[(i*W + j) * 3 + 1] = fmin(255,pow(color.get_y(),1/2.2));
            image[(i*W + j) * 3 + 2] = fmin(255,pow(color.get_z(),1/2.2));
<<<<<<< Updated upstream
            }
=======
=======
            int sqrt_n_path = 3;
            Vector color(0,0,0);
            for(int k = 0; k < sqrt_n_path * sqrt_n_path ; k++){

                Vector ray_dir(j-W/2 + (float)(k/sqrt_n_path)/sqrt_n_path , -i+H/2 - (float)(k%sqrt_n_path)/sqrt_n_path ,-H/(2*tan(fov/2)));
                Ray r(cam_center,ray_dir);
                
                color = color + scene.get_color(r,3);
            }
                color = color/(sqrt_n_path*sqrt_n_path);
                
                image[(i*W + j) * 3 + 0] = fmin(255,pow(color.get_x(),1/2.2));
                image[(i*W + j) * 3 + 1] = fmin(255,pow(color.get_y(),1/2.2));
                image[(i*W + j) * 3 + 2] = fmin(255,pow(color.get_z(),1/2.2));
>>>>>>> Stashed changes
>>>>>>> Stashed changes
        }
        std::cout << i << std::endl;

    }
    
    stbi_write_png("C:\\Users\\ASUS\\OneDrive\\Documents\\Cours\\ECL-3A\\MOS_2.2-Informatique_Graphique\\CG\\RayTracer\\RayTracer\\image.png", W, H, 3, &image[0], 0);
    
    return 0;
}
