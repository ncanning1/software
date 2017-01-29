#pragma once

class Overhead {
public:
	void create(int &w, int &h, int windowType);
	void display(int w, int h, int windowType);
	void closeOverhead();
	SDL_Window *window;
	SDL_Renderer *renderer;
};