/* 
		raytracing algorithm	
    Copyright (C) 2025 Mattia Santaniello 

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
