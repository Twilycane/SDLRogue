#include "Engine.h"

Engine::Base base;

int main(int argc, char *args[]) {
	base.init();
	base.printString("Hello jnsjhfjsdf", 5, 2, 32);
	base.update();
	base.close();
	return 0;
}