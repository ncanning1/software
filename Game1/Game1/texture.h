#pragma once
#include <string>
#include <SDL_ttf.h>
#include "overhead.h"
#include "font.h"

class Texture {
public:
	void setFontIndex(int i);
	void removeTexture();
	void setupTexture(Overhead &overhead);
	void setupTexture(Overhead &overhead, std::string t, SDL_Color c, int x, int y, Font &font);
	void setIsText(bool i);
	SDL_Texture *texture;
	int fontIndex;
	std::string text;
	SDL_Rect textData;
	bool isText;
	SDL_Color color;
	bool blendSet;
};