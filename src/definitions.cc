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

void compute_light(Sphere* selected_sphere,Point intersect,Ray normal_vec,std::vector<Light> lights){
	double intensity = 0;
	double tmp_prod;

	for(auto& light: lights){
		switch(light.type){
			case AMBIENT:
				intensity += light.intensity;
				break;

			case POINT:
				Ray tmp;
				tmp.x = std::get<0>(light.src) - std::get<0>(intersect);
				tmp.y = std::get<1>(light.src) - std::get<1>(intersect);
				tmp.z = std::get<2>(light.src) - std::get<2>(intersect);
				
				tmp_prod = light.intensity*dot_prod(normal_vec,tmp)/(tmp.length()*normal_vec.length());
				intensity += (tmp_prod > 0 ? tmp_prod : 0); 
				break;
			case DIFFUSE:
				tmp_prod = light.intensity*dot_prod(normal_vec,light.direction)/(light.direction.length()*normal_vec.length());
				intensity += (tmp_prod > 0 ? tmp_prod : 0); 
				break;
		}
	}

 	std::get<0>(selected_sphere->surf_color) *= intensity; 
 	std::get<1>(selected_sphere->surf_color) *= intensity; 
 	std::get<2>(selected_sphere->surf_color) *= intensity; 
}
