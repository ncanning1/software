#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include "archive.h"
#include "texture.h"
#include "overhead.h"
#include "audio.h"
#include <iostream>

void archiveReader(std::vector<Texture> &texture, std::vector<int> &getFiles, Overhead &overhead) {
	char * memblock;
	Texture sTexture;
	std::string container;
	long long container2;
	std::vector<std::streampos> sizeVec;
	std::vector<std::streampos> startVec;
	std::ifstream in;
	startVec.push_back(0);
	in.open("archivedata.txt");
	int s = 0;
	bool totalCheck = true;
	while (std::getline(in, container)) {
		container2 = std::stol(container);
		if (!totalCheck) {
			sizeVec.push_back(container2);
			startVec.push_back(container2 + startVec[s]);
			++s;
		}
		else
			totalCheck = false;
	}
	in.close();
	in.clear();
	std::ofstream out;
	in.open("trash.violent", std::ios::in | std::ios::binary | std::ios::beg);
	int c = 0;
	int b = 0;
	for (int a = getFiles[b]; b < getFiles.size(); ++b) {
		a = getFiles[b];
		memblock = new char[sizeVec[a]];
		in.seekg(startVec[a]);
		in.read(memblock, sizeVec[a]);
		texture.push_back(sTexture);
		SDL_RWops *rw = SDL_RWFromMem(memblock, sizeVec[a]);
		if (!rw)
			std::cout << "error writing to rw" << std::endl;
		SDL_Surface *temp = IMG_LoadPNG_RW(rw);
		if (!temp)
			std::cout << "error loading to temp" << std::endl;
		SDL_RWclose(rw);
		texture[c].texture = SDL_CreateTextureFromSurface(overhead.renderer, temp);
		if (texture[c].texture == NULL)
			std::cout << "error creating final texture" << std::endl;
		SDL_FreeSurface(temp);
		++c;
		delete[] memblock;
	}
	in.close();
	in.clear();
}

void archiveReader(std::vector<Audio> &audio, std::vector<int> &getFiles, Overhead &overhead, std::vector<bool> &isEffect) {
	char * memblock;
	std::string container;
	long long container2;
	std::vector<std::streampos> sizeVec;
	std::vector<std::streampos> startVec;
	std::ifstream in;
	startVec.push_back(0);
	in.open("archivedata.txt");
	int s = 0;
	bool totalCheck = true;
	while (std::getline(in, container)) {
		container2 = std::stol(container);
		if (!totalCheck) {
			sizeVec.push_back(container2);
			startVec.push_back(container2 + startVec[s]);
			++s;
		}
		else
			totalCheck = false;
	}
	in.close();
	in.clear();
	std::ofstream out;
	in.open("trash.violent", std::ios::in | std::ios::binary | std::ios::beg);
	int c = 0;
	int b = 0;
	for (int a = getFiles[b]; b < getFiles.size(); ++b) {
		a = getFiles[b];
		memblock = new char[sizeVec[a]];
		in.seekg(startVec[a]);
		in.read(memblock, sizeVec[a]);
		audio.emplace_back();
		if (isEffect[c]) {
			audio[c].buffer.loadFromMemory(memblock, sizeVec[a]);
			std::cout << "sound loaded!" << std::endl;
			audio[c].isEffect = true;
		}
		else if (!isEffect[c]) {
			audio[c].memblock = new char[sizeVec[a]];
			for (int myInt = 0; myInt < sizeVec[a]; ++myInt) {
				audio[c].memblock[myInt] = memblock[myInt];
			}
			audio[c].size = sizeVec[a];
			audio[c].isEffect = false;
			std::cout << "music loaded!" << std::endl;
		}
		++c;
		delete[] memblock;
	}
	in.close();
	in.clear();
}