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

#include "raytracing.h"

double random_double(){
	return std::rand()/2*RAND_MAX;
}

Color render_color(Ray ray,std::vector<Sphere> spheres,std::vector<Light> lights,Point origin){

	double inf = std::numeric_limits<double>::max();
	double t_min = inf;
	std::tuple<double,double> t;

	double t1;
	double t2;
	Sphere s_min;

	for(auto& sphere:spheres){
		t = sphere.hit_sphere(ray,origin,1,t_min);
		t1 = std::get<0>(t);
		t2 = std::get<1>(t);

		if(t1 < t_min && t1 != -1){
      t_min = t1;
			s_min = sphere;
		}
		
		if(t2 < t_min && t2 != -1){
      t_min = t2;
			s_min = sphere;
		}

	}

	if(t_min < inf){
		Point intersect = {
			std::get<0>(origin) + t_min*ray.x,
			std::get<1>(origin) + t_min*ray.y,
			std::get<2>(origin) + t_min*ray.z,
		};

		compute_light(&s_min,ray,intersect,s_min.get_normal_vec(intersect),lights);
		return s_min.surf_color;
	}

	ray.normalize();

	double a = 0.5*(ray.y+1.0);

	return {
		1.0-0.5*a,
		1.0-0.3*a,
		1.0	
	};
}


void drawAt(SDL_Renderer* renderer,Color color,int x,int y,int width,int height){
	double r = CHECK_INTERVAL(std::get<0>(color));
	double g = CHECK_INTERVAL(std::get<1>(color));
	double b = CHECK_INTERVAL(std::get<2>(color));



	SDL_SetRenderDrawColor(
		renderer,
		(r*255.999),
		(g*255.999),	
		(b*255.999),
		255
	);


	double screen_x =  width/2 + x;
	double screen_y =  height/2 + y;


	SDL_RenderDrawPoint(renderer,screen_x,screen_y);
}

Color raysPerPixel(std::vector<Sphere> spheres,std::vector<Light> lights,int width,int height,int canvas_x,int canvas_y,int samples_per_row){
	double step = 1.0/samples_per_row;
	double v_height = 1.0;
	double v_width = v_height*(double(width)/height); // width/height = v_width / v_height 
	double foc_len = 1.0;

	Color acc = {0.0,0.0,0.0};
	Color iter;
	Ray ray;

	Point camera = {0.0,0.0,0.0};

	for(int i=0; i<samples_per_row; i++){
		for(int j=0; j<samples_per_row; j++){
			ray.x =  ((canvas_x+j*step)*v_width/width) - std::get<0>(camera);
			ray.y =  ((canvas_y+i*step)*v_height/height) - std::get<1>(camera);
			ray.z = std::get<2>(camera)-foc_len;

			iter = render_color(ray,spheres,lights,camera);	
			std::get<0>(acc) += std::get<0>(iter);
			std::get<1>(acc) += std::get<1>(iter);
			std::get<2>(acc) += std::get<2>(iter);
		}
	}

	int total_samples = samples_per_row*samples_per_row;
  std::get<0>(acc) /= total_samples;
	std::get<1>(acc) /= total_samples;
	std::get<2>(acc) /= total_samples;


	//std::cout << std::endl << std::get<0>(acc) << " " <<std::get<1>(acc) << " " << std::get<2>(acc);
	return acc;
}

void sendRays(SDL_Renderer* renderer,int width,int height){
	
	int samples_per_row = 3;

	std::vector<Light> lights;
	lights.push_back({AMBIENT,0.2,{0,0,0},{0,0,0}});
	lights.push_back({POINT,0.3,{0,2,0},{0,0,0}});
	lights.push_back({DIRECTIONAL,0.5,{0,0,0},{2,3,4}});

	std::vector<Sphere> spheres;
	Sphere s1;
	s1.center = {0,0,3};
	s1.radius = 1;
	s1.surf_color = {1,0,0};
	s1.s_coeff = 10;
	srand(time(NULL));
	
	/*Sphere s2;
	s2.center = {2,0,4};
	s2.radius = 1;
	s2.surf_color = {0,0,1};


	Sphere s3;
	s3.center = {-2,0,4};
	s3.radius = 1;
	s3.surf_color = {0,1,0};*/

	spheres.push_back(s1);
	/*spheres.push_back(s2);
	spheres.push_back(s3);*/


	Color color;

	for(int canvas_x=-width/2; canvas_x<width/2; canvas_x++){
		for(int canvas_y=-height/2; canvas_y<height/2; canvas_y++){
			color = raysPerPixel(spheres,lights,width,height,canvas_x,canvas_y,samples_per_row);

			drawAt(renderer,color,canvas_x,canvas_y,width,height);
		}
	}
}
