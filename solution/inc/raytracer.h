#ifndef _RAYTRACER_
#define _RAYTRACER_

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#include <stdlib.h>
#include <time.h>
#include "scene.h"
#include "camera.h"
#include "image.h"
#include "ray.h"

typedef struct _intersection {
  Vector normal;
  Material material;
  Pixel color;
  Triangle *triangle;
  Ray ray;
  double t;
} Intersection;

Image* raytracer_render(Scene *scene, Camera *camera);
Ray calculate_ray(int x, int y, Camera *camera);
Pixel raytracer_trace(Ray ray, Scene *scene);
int raytracer_scene_intersection(Ray ray, Scene *scene, 
                                 Intersection **intersection);
int raytracer_object_intersection(Ray ray, Object *object, Intersection **intersection);
int raytracer_triangle_intersection(Ray ray, Triangle *triangle, Intersection **intersection);
int raytracer_ray_is_intersecting_bounding_sphere(Ray r, Sphere bounding_sphere);
Pixel raytracer_phong(Intersection *intersection, Scene *scene);
Pixel raytracer_phongv2(Intersection *intersection, Scene *scene);
void get_sampled_lights(PointLight* lights, int n_lights, PointLight** light_out, int* n_sampled_lights);

Intersection *new_intersection(void);

#endif