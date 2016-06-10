#include "Engine.h"

Engine::Base base;

int main(int argc, char *args[]) {
	base.init();
	base.printTile(1, 5, 5);
	SDL_Delay(3000);
	base.close();
	return 0;
}