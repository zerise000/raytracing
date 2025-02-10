#include "raytracing.h"

Color render_color(Ray ray,std::vector<Sphere> spheres,Point origin){

	double inf = std::numeric_limits<double>::max();
	double t_min = inf;
	std::tuple<double,double> t;

	double t1;
	double t2;
	Color c_min;

	for(auto& sphere:spheres){
		t = sphere.hit_sphere(ray,origin,1,t_min);
		t1 = std::get<0>(t);
		t2 = std::get<1>(t);

		if(t1 < t_min && t1 != -1){
			Ray N = {
				(std::get<0>(origin)+t1*ray.x)-std::get<0>(sphere.center),
				(std::get<1>(origin)+t1*ray.y)-std::get<1>(sphere.center),
				(std::get<2>(origin)+t1*ray.z)-std::get<2>(sphere.center)
			};

			N.normalize();
			c_min = {0.5*(N.x+1),0.5*(N.y+1),0.5*(N.z+1)};
			t_min = t1;
		}
		
		if(t2 < t_min && t2 != -1){
			Ray N = {
				(std::get<0>(origin)+t2*ray.x)-std::get<0>(sphere.center),
				(std::get<1>(origin)+t2*ray.y)-std::get<1>(sphere.center),
				(std::get<2>(origin)+t2*ray.z)-std::get<2>(sphere.center)
			};

			N.normalize();
			c_min = {0.5*(N.x+1),0.5*(N.y+1),0.5*(N.z+1)};
			t_min = t2;
		}

	}

	if(t_min < inf)
		return c_min;

	ray.normalize();

	double a = 0.5*(ray.y+1.0);

	return {
		1.0-0.5*a,
		1.0-0.3*a,
		1.0	
	};
}


void drawAt(SDL_Renderer* renderer,Color color,int x,int y,int width,int height){
	SDL_SetRenderDrawColor(
		renderer,
		int(std::get<0>(color)*255.999),
		int(std::get<1>(color)*255.999),	
		int(std::get<2>(color)*255.999),
		255
	);


	double screen_x =  width/2 + x;
	double screen_y =  height/2 + y;


	SDL_RenderDrawPoint(renderer,screen_x,screen_y);
}

void sendRays(SDL_Renderer* renderer,int width,int height){
	double v_height = 2.0;
	double v_width = v_height*(double(width)/height); // width/height = v_width / v_height 
	double foc_len = 2;
	Ray ray;

	std::vector<Sphere> spheres;
	Sphere s1;
	s1.center = {0,0,3};
	s1.radius = 1;
	s1.surf_color = {1,0,0};

	spheres.push_back(s1);

	Point camera = {0.0,0.0,0.0};

	Color color;

	for(int canvas_x=-width/2; canvas_x<width/2; canvas_x++){
		for(int canvas_y=-height/2; canvas_y<height/2; canvas_y++){

			ray.x =  (canvas_x*v_width/width) - std::get<0>(camera);
			ray.y =  (canvas_y*v_height/height) - std::get<1>(camera);
			ray.z = std::get<2>(camera)-foc_len;

			color = render_color(ray,spheres,camera);	

			
			
			drawAt(renderer,color,canvas_x,canvas_y,width,height);
		}
	}
}
