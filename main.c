#include <stdio.h>
#include "ray_tracing.h"

int main(int argc, char const *argv[])
{
	
	vec3f v1, v2, v3;	

	ray_tracing ray_t; 
	ray_t.viewport_width = 800;
	ray_t.viewport_height = 600;

	get_ray( &ray_t, 400, 330, &v3);

	printf("v = %f %f %f\n", v3.x, v3.y, v3.z);

	return 0;
}