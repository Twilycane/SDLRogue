#include "Engine.h"
using namespace Engine;

bool Base::init(){
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << SDL_GetError() << endl;
		success = false;
	}
	else {
		mainWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
		if (mainWindow == nullptr) {
			cout << SDL_GetError() << endl;
			success = false;
		}
		else {
			mainSurface = SDL_GetWindowSurface(mainWindow);
			if (mainSurface == nullptr) {
				cout << SDL_GetError() << endl;
				success = false;
			}
			renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				cout << SDL_GetError() << endl;
				success = false;
			}
		}
		mainEvent = new SDL_Event();
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		cout << IMG_GetError() << endl;
		success = false;
	}
	else {
		tiles = SDL_CreateTextureFromSurface( renderer ,SDL_LoadBMP("ascii.bmp"));
		if (tiles == nullptr) {
			cout << SDL_GetError() << endl;
			success = false;
		}
	}
	return success;
}

void Base::printTile(int ascii, int x, int y) {
	SDL_Rect targetRect; 
	targetRect.h = 16;
	targetRect.w = 16;
	targetRect.x = (ascii % 16) * 16;
	targetRect.y = (ascii / 16) * 16;
	printf("%i %i", (ascii % 16), (ascii / 16) );
	SDL_Rect dst = { x ,y , 16, 16};
	SDL_RenderCopy(renderer, tiles, &targetRect, NULL);
	SDL_RenderPresent(renderer);
}

void Base::close() {
	SDL_DestroyTexture(tiles);
	delete mainEvent;
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(mainSurface);
	SDL_DestroyWindow(mainWindow);
	IMG_Quit();
	SDL_Quit();
}