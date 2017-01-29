#include <SDL.h>
#include "sprite.h"

Sprite::Sprite() {}

Sprite::Sprite(int ti, int w, int h, int cx, int cy, int wx, int wy, bool b, Uint8 al, bool r) {
	textureIndex = ti; clip.w = w; clip.h = h; clip.x = cx; clip.y = cy; worldX = wx; worldY = wy; flip = SDL_FLIP_NONE;
	angle = 0.0; centre.x = 0; centre.y = 0; blend = b; alpha = al; render = r;
}

Sprite::Sprite(int ti, int w, int h, int cx, int cy, int wx, int wy, SDL_RendererFlip f, int centreX, int centreY, double a, bool b, Uint8 al, bool r) {
	textureIndex = ti; clip.w = w; clip.h = h; clip.x = cx; clip.y = cy; worldX = wx; worldY = wy; flip = f;
	angle = a; centre.x = centreX; centre.y = centreY; blend = b; alpha = al; render = r;
}

void Sprite::setupSprite(int ti, int w, int h, int cx, int cy, int wx, int wy, bool b, Uint8 al, bool r) {
	textureIndex = ti; clip.w = w; clip.h = h; clip.x = cx; clip.y = cy; worldX = wx; worldY = wy; flip = SDL_FLIP_NONE;
	angle = 0.0; centre.x = 0; centre.y = 0; blend = b; alpha = al; render = r;
}

void Sprite::setupSprite(int ti, int w, int h, int cx, int cy, int wx, int wy, SDL_RendererFlip f, int centreX, int centreY, double a, bool b, Uint8 al, bool r) {
	textureIndex = ti; clip.w = w; clip.h = h; clip.x = cx; clip.y = cy; worldX = wx; worldY = wy; flip = f;
	angle = a; centre.x = centreX; centre.y = centreY; blend = b; alpha = al; render = r;
}

void Sprite::setAlpha(bool b, Uint8 a) {
	blend = b;
	alpha = a;
}

void Sprite::setTextureAlpha(Texture &texture) {
	if (!texture.blendSet) {
		SDL_SetTextureBlendMode(texture.texture, SDL_BLENDMODE_BLEND);
		texture.blendSet = true;
	}
	SDL_SetTextureAlphaMod(texture.texture, alpha);
}

void Sprite::setRender(bool r) {
	render = r;
}