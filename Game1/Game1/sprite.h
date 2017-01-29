#pragma once
#include <SDL.h>
#include "texture.h"

class Sprite {
public:
	Sprite();
	Sprite(int ti, int w, int h, int cx, int cy, int wx, int wy, bool b, Uint8 al, bool r);
	Sprite(int ti, int w, int h, int cx, int cy, int wx, int wy, SDL_RendererFlip f, int centreX, int centreY, double a, bool b, Uint8 al, bool r);
	void setupSprite(int ti, int w, int h, int cx, int cy, int wx, int wy, bool b, Uint8 al, bool r);
	void setupSprite(int ti, int w, int h, int cx, int cy, int wx, int wy, SDL_RendererFlip f, int centreX, int centreY, double a, bool b, Uint8 al, bool r);
	void setAlpha(bool b, Uint8 a);
	void setTextureAlpha(Texture &texture);
	void setRender(bool r);
	int textureIndex;
	SDL_Rect clip;
	int worldX, worldY;
	double angle;
	SDL_Point centre;
	SDL_RendererFlip flip;
	bool blend;
	Uint8 alpha;
	bool render;
};