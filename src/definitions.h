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
 	DIRECTIONAL 
} LightType;


class Light{
	private:
		LightType type;
		double intensity;
		Point src;
		Ray direction;
	public:
		Light(LightType,double,Point,Ray);
		double get_intensity(Point intersect,double s_coeff,Ray render_ray,Ray normal_vec);
};

typedef struct{
	Point center;
	double radius;
	Color surf_color;
	double s_coeff;

	std::tuple<double,double> hit_sphere(Ray dir,Point origin,double t_min,double t_max);
	Ray get_normal_vec(Point surf_point);
} Sphere;

void compute_light(Sphere* selected_sphere,Ray render_ray,Point intersect,Ray normal_vec,std::vector<Light> lights);
double dot_prod(Ray v1,Ray v2,double t_min,double t_max);

#endif
