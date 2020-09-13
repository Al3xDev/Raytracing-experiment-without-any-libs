#include <math.h>

typedef struct vec3i_s
{
	int x,y,z;
} vec3i;

typedef struct vec3f_s
{
	float x,y,z;
} vec3f;

float dot( vec3f *v1, vec3f *v2)
{
	return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

void cross( vec3f *v1, vec3f *v2, vec3f *v3)
{
	v3->x = v1->y*v2->z - v2->y*v1->z;
	v3->y = v1->z*v2->x - v2->x*v1->z;
	v3->z = v1->x*v2->y - v2->x*v1->y;
}

void normalize( vec3f *v)
{
	float r = sqrt( v->x*v->x + v->y*v->y+ v->z*v->z);
	v->x = v->x / r;
	v->y = v->y / r;
	v->z = v->z / r;
}

float length( vec3f *v)
{
	return sqrt( v->x*v->x + v->y*v->y + v->z*v->z);
}

float distance( vec3f *p1, vec3f *p2)
{
	float dx = p1->x-p2->x;
	float dy = p1->y-p2->y;
	float dz = p1->z-p2->z;

	return sqrt( dx*dx + dy*dy + dz*dz);

}
