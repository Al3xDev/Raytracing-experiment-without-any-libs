#include <iostream>
#include <ctime>
#include "ray_tracing.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

using namespace std;


int main(int argc, char const *argv[])
{

	vec3f v1, v2, v3;
	ray_tracing ray_t;
	ray_t.viewport_width = 500;
	ray_t.viewport_height = 500;
	ray_t.camera_pos = { .x=0, .y=0, .z=0};
	ray_t.image = new vec3f[ ray_t.viewport_height*ray_t.viewport_width];

	ray_t.lights_size = 1;
	ray_t.lights = new light[ ray_t.lights_size];

	ray_t.lights[0].pos = { 3, 0, 5};
    ray_t.lights[0].color = { 1, 1, 1};

	ray_t.spheres_size = 1;
	ray_t.spheres = new sphere[ ray_t.spheres_size];

	ray_t.spheres[0].r = 1;
	ray_t.spheres[0].pos = { .x=0, .y=5, .z=0};
	ray_t.spheres[0].color = { .x=0.2, .y=1.0, .z=0.3};


    clear_image_buffer( &ray_t);

    time_t t1 = clock();
	start_ray_tracing( &ray_t);
    time_t t2 = clock();

    std::cerr<<"\n"<<float( t2-t1)/CLOCKS_PER_SEC<<"\n";



	return 0;
}
