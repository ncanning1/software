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
#include <iostream>
#include <fstream>
#include <Windows.h>

void setupCheck(int w, int h, int windowType) {
	char check;
	std::ifstream in;
	in.open("setup.txt", std::ios::in | std::ios::beg);
	in >> check;
	in.close();
	in.clear();
	std::ofstream out;
	if (check == '1') {
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		LPCTSTR path = "Decompressor.exe";
		LPSTR arg = "Decompressor.exe";
		CreateProcess(path, arg, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		out.open("setup.txt", std::ios::out | std::ios::beg);
		out << "0 " << w << " " << h << " " << windowType;
		std::cout << "Decompressor totally ran";
		out.close();
		out.clear();
	}
}

int main(int argc, char* args[]) {
	Overhead overhead;
	int w = 0; int h = 0; int windowType = 0;
	std::ifstream in("setup.txt", std::ios::beg);
	in >> w;
	if (w == 0)
		in >> w >> h >> windowType;
	else
		w = 0;
	in.close();
	in.clear();
	std::cout << "w: " << w << "   h: " << h << std::endl;
	overhead.create(w, h, windowType);
	std::cout << "THIS IS THE RESOLUTION AFTER THE RELEVANT CODE: " << w << " x " << h << std::endl;
	setupCheck(w, h, windowType);
	intro(overhead, w, h);
	overhead.closeOverhead();
	return 0;
}