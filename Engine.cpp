#include "Engine.h"
using namespace Engine;

bool Base::init(){
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << SDL_GetError() << endl;
		success = false;
	}
	else {
		mainWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 700, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		cout << IMG_GetError() << endl;
		success = false;
	}
	loadTiles();
	return success;
}

void Base::loadTiles() {
	SDL_Surface *loadedIMG = SDL_LoadBMP("ascii.bmp"), *temp = SDL_LoadBMP("ascii.bmp");
	Uint32 colorkey = SDL_MapRGB(loadedIMG->format, 255, 0, 255);
	SDL_SetColorKey(loadedIMG, 1, colorkey);
	SDL_BlitSurface(loadedIMG, NULL, temp, NULL);
	tiles = SDL_CreateTextureFromSurface(renderer, loadedIMG);
	SDL_FreeSurface(loadedIMG);
	SDL_FreeSurface(temp);
}

void Base::clearScreen() {
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Base::printTile(int ascii, int x, int y) {
	printTile(ascii, x, y, tileSize);
}

void Base::printTile(int ascii, int x, int y, int size) {
	SDL_Rect targetRect; 
	targetRect.h = 16;
	targetRect.w = 16;
	targetRect.x = (ascii % 16) * 16;
	targetRect.y = (ascii / 16) * 16;
	printf("%i %i %i %i\n", (ascii % 16), (ascii / 16), tileSize, ascii );
	SDL_Rect dst = { x * size, y * size, size, size };
	SDL_RenderCopy(renderer, tiles, &targetRect, &dst);
	SDL_RenderPresent(renderer);
}

void Base::printString(std::string txt, int x, int y) {
	for (int i = 0; i < txt.length(); i++)
	{
		printTile(txt.c_str()[i], x++, y);
	}
}

void Base::printString(std::string txt, int x, int y, int size) {
	for (int i = 0; i < txt.length(); i++)
	{
		printTile(txt.c_str()[i], x++, y, size);
	}
}

void Base::update() {
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&mainEvent);
		if (mainEvent.type == SDL_QUIT) {
			quit == true;
			break;
		}
		if (mainEvent.key.keysym.sym == (Uint16)' ') {
			clearScreen();
		}
		if (mainEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			mainSurface = SDL_GetWindowSurface(mainWindow);
			SDL_RenderPresent(renderer);
		}
		if (mainEvent.window.event == SDL_WINDOWEVENT_EXPOSED) {
			SDL_RenderPresent(renderer);
		}
	}
}

void Base::close() {
	SDL_DestroyTexture(tiles);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(mainSurface);
	SDL_DestroyWindow(mainWindow);
	IMG_Quit();
	SDL_Quit();
}