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

Ray Sphere::get_normal_vec(Point surf_point){
	Ray tmp = {
		std::get<0>(surf_point)-std::get<0>(this->center),
		std::get<1>(surf_point)-std::get<1>(this->center),
		std::get<2>(surf_point)-std::get<2>(this->center)
	};

	tmp.normalize();
	return tmp;
}

Light::Light(LightType type,double intensity,Point src,Ray direction) : type{type},intensity{intensity},src{src},direction{direction} {}

double Light::get_intensity(Point intersect,double s_coeff,Ray render_ray,Ray normal_vec) {

	double tmp_prod,dot_nl;
	double final_intensity;
	double dot_light;
	Ray r;
	Ray tmp;

	switch(this->type){
			case AMBIENT:
				return this->intensity;
			case POINT:
				tmp.x = std::get<0>(this->src) - std::get<0>(intersect);
				tmp.y = std::get<1>(this->src) - std::get<1>(intersect);
				tmp.z = std::get<2>(this->src) - std::get<2>(intersect);

				break;

			case DIRECTIONAL:
				tmp.x = this->direction.x;
				tmp.y = this->direction.y;
				tmp.z = this->direction.z;
				break;
		}
		
		dot_nl = dot_prod(normal_vec,tmp);

		r.x=2*dot_nl*normal_vec.x-tmp.x;
		r.y=2*dot_nl*normal_vec.y-tmp.y;
		r.z=2*dot_nl*normal_vec.z-tmp.z;

		tmp_prod = dot_nl/(tmp.length()*normal_vec.length());
		final_intensity = (tmp_prod > 0 ? tmp_prod : 0);

		dot_light = dot_prod(render_ray,r);

		if(dot_light > 0 && s_coeff != -1)
			final_intensity += std::pow(dot_light/(r.length()*render_ray.length()),s_coeff);

		final_intensity*=this->intensity;
	
		return final_intensity;
}

void compute_light(Sphere* selected_sphere,Ray render_ray,Point intersect,Ray normal_vec,std::vector<Light> lights){
	double intensity = 0;

	for(auto& light: lights){
		intensity += light.get_intensity(intersect,selected_sphere->s_coeff,render_ray,normal_vec);
	}

 	std::get<0>(selected_sphere->surf_color) *= intensity; 
 	std::get<1>(selected_sphere->surf_color) *= intensity; 
 	std::get<2>(selected_sphere->surf_color) *= intensity; 
}
