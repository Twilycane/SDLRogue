#include "Engine.h"

Engine::Base base;

int main(int argc, char *args[]) {
	base.init();
	base.printString("Hello Sylvia!", 0, 0);
	base.update();
	base.close();
	return 0;
}