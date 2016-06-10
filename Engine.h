#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;



namespace Engine {
	class Base {
	public: 
		SDL_Window *mainWindow = nullptr;
		SDL_Surface *mainSurface = nullptr;
		SDL_Texture *tiles = nullptr;
		SDL_Renderer *renderer = nullptr;
		SDL_Event mainEvent;
		bool init();
		void loadTiles();
		void printTile(int ascii, int x, int y);
		void printTile(int ascii, int x, int y, int size);
		void printString(std::string txt, int x, int y);
		void update();
		void close();
	protected:
		int tileSize = 16;
	};
}