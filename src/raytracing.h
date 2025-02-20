#ifndef __RAYTRACING_H__
#define __RAYTRACING_H__

#include "definitions.h"
#include <SDL.h>
#include <vector>
#include <limits>

Color render_color(Ray ray,std::vector<Sphere> spheres,std::vector<Light> lights,Point origin);
void drawAt(SDL_Renderer* renderer,Color color,int x,int y,int width,int height);
void sendRays(SDL_Renderer* renderer,int width,int height);

#endif
