#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "overhead.h"
#include "font.h"
#include "texture.h"
#include "state.h"
#include "archive.h"
#include <iostream>
#include "sprite.h"
#include "audio.h"

void render(Overhead &overhead, Sprite sprite, SDL_Rect* clip, SDL_Point* centre, Texture &texture) {
	SDL_Rect render;
	if(texture.isText)
		render = { texture.textData.x, texture.textData.y, texture.textData.w, texture.textData.h };
	else
		render = { sprite.worldX, sprite.worldY, sprite.clip.w, sprite.clip.h };
	SDL_RenderCopyEx(overhead.renderer, texture.texture, clip, &render, sprite.angle, centre, sprite.flip);
}

void intro(Overhead &overhead, int w, int h) {
	Sprite sprite[4];
	int spriteSize = 4;
	std::vector<int> getFiles;
	if (w == 1920) {
		getFiles.push_back(0);
		getFiles.push_back(4);
		sprite[0].setupSprite(1, 1920, 1080, 0, 0, 0, 0, false, 0, true);
		sprite[1].setupSprite(1, 1920, 1080, 1920, 0, 0, 0, false, 0, false);
		sprite[2].setupSprite(1, 1920, 1080, 3840, 0, 0, 0, false, 0, false);
		sprite[3].setupSprite(0, 1533, 377, 0, 0, w/2 - 1533 / 2, h / 2 - 377 / 2, true, 0, true);
	}
	else if (w == 1366) {
		getFiles.push_back(1);
		getFiles.push_back(5);
		sprite[0].setupSprite(1, 1366, 768, 0, 0, 0, 0, false, 0, true);
		sprite[1].setupSprite(1, 1366, 768, 1366, 0, 0, 0, false, 0, false);
		sprite[2].setupSprite(1, 1366, 768, 2732, 0, 0, 0, false, 0, false);
		sprite[3].setupSprite(0, 1302, 253, 0, 0, w / 2 - 1302 / 2, h / 2 - 253 / 2, true, 0, true);
	}
	else if (w == 1600) {
		getFiles.push_back(2);
		getFiles.push_back(6);
		sprite[0].setupSprite(1, 1600, 900, 0, 0, 0, 0, false, 0, true);
		sprite[1].setupSprite(1, 1600, 900, 1600, 0, 0, 0, false, 0, false);
		sprite[2].setupSprite(1, 1600, 900, 3200, 0, 0, 0, false, 0, false);
		sprite[3].setupSprite(0, 1409, 323, 0, 0, w / 2 - 1409 / 2, h / 2 - 323 / 2, true, 0, true);
	}
	else if (w == 1440) {
		getFiles.push_back(3);
		getFiles.push_back(7);
		sprite[0].setupSprite(1, 1440, 900, 0, 0, 0, 0, false, 0, true);
		sprite[1].setupSprite(1, 1440, 900, 1440, 0, 0, 0, false, 0, false);
		sprite[2].setupSprite(1, 1440, 900, 2880, 0, 0, 0, false, 0, false);
		sprite[3].setupSprite(0, 1409, 323, 0, 0, w / 2 - 1409 / 2, h / 2 - 323 / 2, true, 0, true);
	}
	std::vector<Texture> texture;
	archiveReader(texture, getFiles, overhead);
	for (int a = 0; a < texture.size(); ++a) {
		texture[a].blendSet = false;
		texture[a].setIsText(false);
	}
	//audio stuff
	std::vector<Audio> audio;
	std::vector<bool> isEffect = { false };
	getFiles.clear();
	std::vector<int> tmp;
	getFiles.swap(tmp);
	getFiles.push_back(8);
	archiveReader(audio, getFiles, overhead, isEffect);
	for (int a = 0; a < audio.size(); ++a) {
		audio[a].music->openFromMemory(audio[a].memblock, audio[a].size);
	}
	std::cout << "size of audio is " << audio.size() << std::endl;
	Uint32 startTime1, startTime2, totalTime, elapsedTime;
	startTime1 = SDL_GetTicks();
	startTime2 = SDL_GetTicks();
	totalTime = SDL_GetTicks();
	sprite[3].setAlpha(true, 0);
	sprite[3].setTextureAlpha(texture[sprite[3].textureIndex]);
	bool game = true;
	SDL_Event event;
	bool startFade = false;
	while (game) {
		SDL_RenderClear(overhead.renderer);
		for (int a = 0; a < spriteSize; ++a) {
			if(sprite[a].render)
				render(overhead, sprite[a], &sprite[a].clip, &sprite[a].centre, texture[sprite[a].textureIndex]);
		}
		SDL_RenderPresent(overhead.renderer);
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				game = false;
			}
		}
		elapsedTime = SDL_GetTicks() - startTime2;
		if (elapsedTime > 50) {
			if (sprite[0].render) {
				sprite[0].setRender(false);
				sprite[1].setRender(true);
			}
			else if (sprite[1].render) {
				sprite[1].setRender(false);
				sprite[2].setRender(true);
			}
			else if (sprite[2].render) {
				sprite[2].setRender(false);
				sprite[0].setRender(true);
			}
			startTime2 = SDL_GetTicks();
		}
		elapsedTime = SDL_GetTicks() - startTime1;
		if (elapsedTime > 1000) {
			startFade = true;
			startTime1 = SDL_GetTicks();
		}
		if (startFade) {
			if (elapsedTime > 5 && sprite[3].alpha < 255) {
				sprite[3].setAlpha(true, sprite[3].alpha + 1);
				sprite[3].setTextureAlpha(texture[sprite[3].textureIndex]);
				startTime1 = SDL_GetTicks();
			}
		}
		elapsedTime = SDL_GetTicks() - totalTime;
		if (elapsedTime > 3500 && audio[0].music->getStatus() != sf::Music::Playing) {
			audio[0].music->play();
		}
		if (elapsedTime > 7000) {
			game = false;
			audio[0].music->stop();
		}
	}
	for (int a = 0; a < texture.size(); ++a) {
		texture[a].removeTexture();
	}
	for (int a = 0; a < audio.size(); ++a) {
		if (!audio[a].isEffect) {
			delete[] audio[a].memblock;
			audio[a].memblock = NULL;
		}
	}
}