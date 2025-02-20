#ifndef __DEF_H__
#define __DEF_H__

#include <iostream>
#include <cmath>
#include <tuple>
#include <random>
#include <cstdlib>

typedef std::tuple<double,double,double> Point;
typedef std::tuple<double,double,double> Color;

typedef struct{
	double x;
	double y;
	double z;
	
	double length_squared();
	double length();
	void normalize();
}Ray;

typedef enum LightType{
  AMBIENT,
  POINT,
  DIFFUSE
} LightType;

typedef struct {
  LightType type;
  double intensity;
	Point src;
	Ray direction;
} Light;

typedef struct{
	Point center;
	double radius;
	Color surf_color;

	std::tuple<double,double> hit_sphere(Ray dir,Point origin,double t_min,double t_max);
} Sphere;

void compute_light(Sphere* selected_sphere,Point intersect,Ray normal_vec,std::vector<Light> lights);
double dot_prod(Ray v1,Ray v2,double t_min,double t_max);
double random_double();
double random_range();
Ray random(double min,double max);

#endif
