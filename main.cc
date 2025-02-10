#include <iostream>
#include <SDL.h>
#include "src/raytracing.h"

#define INIT_ASSERT(cond) \
	if(cond){ \
		std::cerr << std::endl << "ERROR SDL: " << SDL_GetError(); \
		return -1; \
	} 


void keep_win_alive(){
	SDL_Event event;
	bool quit = false;

	while(!quit){
		SDL_WaitEvent(&event);

		switch(event.type){
			case SDL_QUIT:
				quit = true;
				break;
			default:
				break;
		}
	}
}

int main(){

	INIT_ASSERT(SDL_Init(SDL_INIT_EVERYTHING) < 0);
	float ratio = 16/9;

	int width = 800;
	int height = width/ratio;

	SDL_Window* win = SDL_CreateWindow(
			"Raytracing",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_SHOWN
	);

	INIT_ASSERT(!win);
	SDL_Renderer* renderer = SDL_CreateRenderer(win,-1,0);
	
	sendRays(renderer,width,height);

	SDL_RenderPresent(renderer);
	keep_win_alive();

	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
