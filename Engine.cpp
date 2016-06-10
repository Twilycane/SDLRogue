#include "Engine.h"
using namespace Engine;

bool Base::init(){
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << SDL_GetError() << endl;
		success = false;
	}
	else {
		mainWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_SHOWN);
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

void Base::printTile(int ascii, int x, int y) {
	printTile(ascii, x, y, tileSize);
}

void Base::printTile(int ascii, int x, int y, int size) {
	SDL_Rect targetRect; 
	targetRect.h = 16;
	targetRect.w = 16;
	targetRect.x = (ascii % 16) * 16;
	targetRect.y = (ascii / 16) * 16;
	printf("%i %i %i\n", (ascii % 16), (ascii / 16), tileSize );
	SDL_Rect dst = { x * 16 ,y * 16, size, size};
	SDL_RenderCopy(renderer, tiles, &targetRect, &dst);
	SDL_RenderPresent(renderer);
}

void Base::printString(std::string txt, int x, int y) {
	for (int i = 0; i < txt.length(); i++)
	{
		printTile(txt.c_str()[i], x++, y);
		printf("%i\n", i);
	}
}

void Base::update() {
	bool quit = false;
	while (!quit) {

		while (SDL_PollEvent(&mainEvent) != 0)
		{
			if (mainEvent.window.type == SDL_QUIT) {
				quit == true;
			}
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