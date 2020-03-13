#include <iostream>
#include <SDL.h>

#include "Engine.h"
#include "Grid2D.h"

Engine* engine = nullptr;

int main(int argc, char* argv[]) {
	
	//Grid2D grid = Grid2D(10, 10);

	//grid.DEBUG_printGrid();

	//return EXIT_SUCCESS;

	
	engine = new Engine(15, 15);

	engine->init("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (engine->running()) {
		engine->engineLoop();
	}

	engine->clean();

	return EXIT_SUCCESS;
	
}