#include "definitions.h"

double Ray::length_squared(){
	return x*x+y*y+z*z;
}

double Ray::length(){
	return sqrt(this->length_squared());
}

void Ray::normalize(){
	double len = this->length();
	this->x /= len;
	this->y /= len;
	this->z /= len;
}

double random_double(){
	return std::rand()/(RAND_MAX+1.0);
}

double random_range(double min,double max){
	return min + (max-min)*random_double(); 
}

Ray random(double min,double max){
	return Ray{
		random_range(min,max),
		random_range(min,max),
		random_range(min,max)
	};
}

double dot_prod(Ray v1,Ray v2){
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

std::tuple<double,double> Sphere::hit_sphere(Ray dir,Point origin,double t_min,double t_max){
	Ray diff = {
		std::get<0>(origin)-std::get<0>(this->center),
		std::get<1>(origin)-std::get<1>(this->center),
		std::get<2>(origin)-std::get<2>(this->center)
	};

	double b = 2.0*dot_prod(dir,diff);
	double a = dir.length_squared();
	double c = diff.length_squared() - (this->radius*this->radius);
	double discriminant = b*b - 4*a*c;

	if(discriminant < 0) 
		return {-1,-1};

	double t1 = (-b - sqrt(discriminant))/(2*a);
	double t2 = (-b + sqrt(discriminant))/(2*a);

	if((t1<t_min && t1 > t_max) && (t2<t_min && t2>t_max))
		return {-1,-1};

	return {t1,t2};
}

