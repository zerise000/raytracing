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

#ifndef __RAYTRACING_H__
#define __RAYTRACING_H__

#include "definitions.h"
#include <SDL.h>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

#define CHECK_INTERVAL(color) color>1.0 ? 1.0 : (color<0.0 ? 0.0 : color)
	

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
