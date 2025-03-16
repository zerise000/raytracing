#ifndef __RAYTRACING_H__
#define __RAYTRACING_H__

#include "definitions.h"
#include <SDL.h>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

double random_double();
Color render_color(Ray ray,std::vector<Sphere> spheres,std::vector<Light> lights,Point origin);
void drawAt(SDL_Renderer* renderer,Color color,int x,int y,int width,int height);
void sendRays(SDL_Renderer* renderer,int width,int height);
Color raysPerPixel(std::vector<Sphere> spheres,
		std::vector<Light> lights,
		int width,
		int height,
		int canvas_x,
		int canvas_y,
		int samples_per_row);

#endif
