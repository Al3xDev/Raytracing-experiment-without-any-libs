#include "vec.h"
#include <string.h>
#include <iostream>

typedef struct sphere_s
{
	float r;
	vec3f pos;
	vec3f color;
} sphere;

typedef struct light_s
{
    vec3f pos;
    vec3f color;
} light;

typedef struct ray_tracing_s
{
	vec3f const base_camera_pos = { .x = 0, .y = 0, .z = 0};
	vec3f const base_camera_dir = { .x = 0, .y = 1, .z = 0};
	vec3f const base_camera_up = { .x = 0, .y = 0, .z = 1};
	vec3f const base_camera_rig = { .x = 1, .y = 0, .z = 0};

	vec3f const clear_color = { 0, 0, 0};

	vec3f camera_pos;
	vec3f camera_dir;

	const float half_p_h = 0.5;
	float half_p_w;

	int viewport_width, viewport_height;

	sphere *spheres;
	int spheres_size;

	light *lights;
	int lights_size;

	float ambient = 0.5;

	vec3f *image;

} ray_tracing;

float max( float x, float y) { return x >y ? x : y;}

void get_ray( ray_tracing *ray_tracing_t, int x, int y, vec3f *ray)
{
    ray_tracing_t->half_p_w = float( ray_tracing_t->viewport_width)/ray_tracing_t->viewport_height/2.0;

	ray->x = ((float)x) / ray_tracing_t->viewport_width * ray_tracing_t->half_p_w * 2.0 - ray_tracing_t->half_p_w;
	ray->y = 1;
	ray->z = ((float)y) / ray_tracing_t->viewport_height - ray_tracing_t->half_p_h;

	normalize( ray);
}

int ray_intersec_sphere( ray_tracing *ray_tracing_t, vec3f *ray, sphere *sphere_t)
{
	vec3f np = { sphere_t->pos.x - ray_tracing_t->camera_pos.x,
					sphere_t->pos.y - ray_tracing_t->camera_pos.y,
						sphere_t->pos.z - ray_tracing_t->camera_pos.z};

	float d = length( &np);

	normalize( &np);

	float cos_a = dot( &np, ray);

	if( d*sqrt( 1.0/( cos_a*cos_a)-1) <= sphere_t->r)
    {
        return d*cos_a - sqrt( d*d*(cos_a*cos_a-1)+sphere_t->r*sphere_t->r);
    }
    else
    {
        return 0;
    }
}

void clear_image_buffer( ray_tracing *ray_tracing_t)
{
    for( int i=0; i<ray_tracing_t->viewport_width; ++i)
	{
		for( int j=0; j<ray_tracing_t->viewport_height; ++j)
		{
            ray_tracing_t->image[ i + j*ray_tracing_t->viewport_width].x = ray_tracing_t->clear_color.x;
            ray_tracing_t->image[ i + j*ray_tracing_t->viewport_width].y = ray_tracing_t->clear_color.y;
            ray_tracing_t->image[ i + j*ray_tracing_t->viewport_width].z = ray_tracing_t->clear_color.z;
		}
	}
}

void start_ray_tracing( ray_tracing *ray_tracing_t)
{
	vec3f ray;
	for( int i=0; i<ray_tracing_t->viewport_width; ++i)
	{
		for( int j=0; j<ray_tracing_t->viewport_height; ++j)
		{
			get_ray( ray_tracing_t, i, ray_tracing_t->viewport_height - j - 1, &ray);
			for( int k=0; k<ray_tracing_t->spheres_size; ++k)
			{
			    float r_min = ray_intersec_sphere( ray_tracing_t, &ray, (ray_tracing_t->spheres+k));
				if( r_min > 0)
				{
                    /*
					ray_tracing_t->image[ i + j*ray_tracing_t->viewport_width].x = (ray_tracing_t->spheres+k)->color.x;
					ray_tracing_t->image[ i + j*ray_tracing_t->viewport_width].y = (ray_tracing_t->spheres+k)->color.y;
					ray_tracing_t->image[ i + j*ray_tracing_t->viewport_width].z = (ray_tracing_t->spheres+k)->color.z;

					*/

                    vec3f intersec_point = { ray.x*r_min, ray.y*r_min, ray.z*r_min};
                    vec3f p_neg = { -(ray_tracing_t->spheres+k)->pos.x + ray_tracing_t->camera_pos.x,
					 - (ray_tracing_t->spheres+k)->pos.y + ray_tracing_t->camera_pos.y,
                     - (ray_tracing_t->spheres+k)->pos.z + ray_tracing_t->camera_pos.z};

                    vec3f normal = { intersec_point.x+p_neg.x, intersec_point.y+p_neg.y, intersec_point.z+p_neg.z};
                    normalize( &normal);

                    for( int l=0; l<ray_tracing_t->lights_size; ++l)
                    {
                        vec3f lp = { intersec_point.x - ray_tracing_t->lights[l].pos.x,
                                        intersec_point.y - ray_tracing_t->lights[l].pos.y,
                                            intersec_point.z - ray_tracing_t->lights[l].pos.z};
                        normalize( &lp);

                        float cos_i = dot( &lp, &normal);
                        float alpha = max( -cos_i, 0);

                        ray_tracing_t->image[ i + j*ray_tracing_t->viewport_width].x =
                                (ray_tracing_t->spheres+k)->color.x * alpha*ray_tracing_t->lights[i].color.x;
                        ray_tracing_t->image[ i + j*ray_tracing_t->viewport_width].y =
                                (ray_tracing_t->spheres+k)->color.y * alpha*ray_tracing_t->lights[l].color.y;
                        ray_tracing_t->image[ i + j*ray_tracing_t->viewport_width].z =
                                (ray_tracing_t->spheres+k)->color.z * alpha*ray_tracing_t->lights[l].color.z;

                    }

                }

			}

		}
	}
}
