#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "texture.h"
#include "overhead.h"
#include "font.h"

void Texture::setIsText(bool i) {
	isText = i;
}

void Texture::setFontIndex(int i) {
	fontIndex = i;
	texture = NULL;
}

void Texture::removeTexture() {
	SDL_DestroyTexture(texture);
	texture = NULL;
	fontIndex = -1;
}

void Texture::setupTexture(Overhead &overhead, std::string text, SDL_Color color, int x, int y, Font &font) {
	SDL_Surface *surface = TTF_RenderText_Solid(font.font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(overhead.renderer, surface);
	textData.w = surface->w;
	textData.h = surface->h;
	SDL_FreeSurface(surface);
	textData.x = x; textData.y = y;
	blendSet = false;
}