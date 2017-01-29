#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "overhead.h"
#include <stdio.h>
#include <fstream>

void Overhead::create(int &w, int &h, int windowType) {
	window = NULL;
	renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_DisplayMode current;
	if (windowType == 0 && w == 0) {
		SDL_GetCurrentDisplayMode(0, &current);
		w = current.w;
		h = current.h;
		if (!(w == 1920 && h == 1080) && !(w == 1366 && h == 768) && !(w == 1600 && h == 900) && !(w == 1440 && h == 900)) {
			if (h >= 1080 && w >= 1920) {
				w = 1920; h = 1080;
			}
			else if (w >= 1600 && h >= 900) {
				w = 1600; h = 900;
			}
			else if (w >= 1440 && h >= 900) {
				w = 1440; h = 900;
			}
			else {
				w = 1366; h = 768;
			}
		}
		window = SDL_CreateWindow("Neon and Noise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_FULLSCREEN_DESKTOP);
		std::ofstream out("setup.txt", std::ios::out | std::ios::beg);
		out << "1 " << w << " " << h << " " << windowType;
		out.close();
		out.clear();
	}
	else if (windowType == 0)
		window = SDL_CreateWindow("Neon and Noise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_FULLSCREEN);
	else if (windowType == 1) {
		window = SDL_CreateWindow("Neon and Noise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_BORDERLESS);
	}
	else if(windowType == 2)
		window = SDL_CreateWindow("Neon and Noise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
	TTF_Init();
}



void Overhead::display(int w, int h, int windowType) {
	closeOverhead();
	create(w, h, windowType);
}

void Overhead::closeOverhead() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}