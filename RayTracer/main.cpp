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
#include <random>

#include <chrono>
#include <iostream>
#include <ctime>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
 
int main() {
    int W = 128;
    int H = 128;
    int rays_per_pixel = 10;
    int n_reflect = 1;
    
    Vector cam_center(-0.,.6,0.);
    float focus_dist = 2;
    float aperture = 0.0;
    float fov = M_PI/2;
    
    Scene scene;
    
    std::default_random_engine engine;
    std::uniform_real_distribution<double>distrib(0,1);

    
    //Walls
    
    scene.add_sphere(Sphere(Vector(0.,0.,-104.),100,MATERIAL_RED));
    scene.add_sphere(Sphere(Vector(0.,0.,+104.),100,MATERIAL_CYAN));
    scene.add_sphere(Sphere(Vector(-103.,0.,0.),100,MATERIAL_BLUE));
    scene.add_sphere(Sphere(Vector(+103.,0.,0.),100,MATERIAL_YELLOW));
    scene.add_sphere(Sphere(Vector(0.,-100.,0.),100,MATERIAL_GREEN));
    scene.add_sphere(Sphere(Vector(0.,+103.,0.),100,MATERIAL_WHITE));

    
   
    //Center Sphere
    scene.add_sphere(Sphere(Vector(0.4,0.4,-2.),.4,MATERIAL_MIRROR));
    scene.add_sphere(Sphere(Vector(0.3,0.6,-1.),0.5,Material(Vector(0, 0, 0),MATERIAL_TYPE_TRANSPARENT,1.1)));
    scene.add_sphere(Sphere(Vector(0.3,0.6,-1.),-0.49,Material(Vector(0, 0, 0),MATERIAL_TYPE_TRANSPARENT,1.1)));
    scene.add_sphere(Sphere(Vector(-0.5,0.3,-1.5),0.3,Material(Vector(0, 0, 0),MATERIAL_TYPE_TRANSPARENT,1.1)));
    scene.add_sphere(Sphere(Vector(-0.9,1.4,-1.),0.5,Material(Vector(1, 1, 1),MATERIAL_TYPE_DIFFUSE)));
    scene.add_sphere(Sphere(Vector(-0.9,1.4,-2.),0.5,Material(Vector(1, 1, 1),MATERIAL_TYPE_DIFFUSE)));
    scene.add_sphere(Sphere(Vector(-0.9,1.4,-3.),0.5,Material(Vector(1, 1, 1),MATERIAL_TYPE_DIFFUSE)));
    //scene.add_sphere(Sphere(Vector(0.,0.6,-1.),0.5,MATERIAL_MIRROR));

    //Light
    float light_radius = 0.2;
    Sphere light(Vector(0.3,2,-1.4),light_radius,MATERIAL_WHITE);
    scene.set_light(&light,1000000 * 4. * M_PI / (4. * M_PI * light_radius * light_radius * M_PI));
    scene.add_sphere(light);
    
    scene.set_n_brdf(rays_per_pixel);
    scene.set_roh_brdf(0.6);
    
    std::vector<unsigned char> image(W*H * 3, 0);
    auto start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    #pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < H; i++) {
        //std::cout<< omp_get_num_threads() << std::endl;
        for (int j = 0; j < W; j++) {

            Vector color(0,0,0);
            for(int l = 0; l<rays_per_pixel ; l++){
                Vector ray_dir(j-W/2-0.5 , -i+H/2-0.5 ,-H/(2*tan(fov/2)));

                double x = distrib(engine);
                double y = distrib(engine);
                double R = sqrt(-2*log(x));

                Vector anti_aliazing(R * cos(2*M_PI*y)*0.5, R * sin(2*M_PI*y)*0.5, 0);
                Vector direction = (ray_dir+anti_aliazing);
                Vector destination = cam_center + direction / abs(direction.get_z()) * focus_dist; 

                double radius = sqrt(distrib(engine))*aperture;
                double theta = distrib(engine) * M_PI * 2;
                Vector origin = cam_center+Vector(cos(theta)*radius,sin(theta)*radius,0.0);
                Vector new_dir = (destination-origin).normalize();
                Ray r(origin,new_dir);
            
                color = color + scene.get_color(r,n_reflect);
            }
            color = color / rays_per_pixel;
            image[(i*W + j) * 3 + 0] = fmin(255,pow(color.get_x(),1/2.2));
            image[(i*W + j) * 3 + 1] = fmin(255,pow(color.get_y(),1/2.2));
            image[(i*W + j) * 3 + 2] = fmin(255,pow(color.get_z(),1/2.2));
        }
        //std::cout << i << std::endl;
        
    }
    auto end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    std::cout << "durration : " << end_time-start_time << std::endl;

    stbi_write_png("C:\\Users\\ASUS\\OneDrive\\Documents\\Cours\\ECL-3A\\MOS_2.2-Informatique_Graphique\\CG\\RayTracer\\RayTracer\\image.png", W, H, 3, &image[0], 0);
    
    return 0;
}



