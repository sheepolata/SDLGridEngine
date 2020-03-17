#include <iostream>
#include <SDL.h>

#include "Engine.h"
#include "Grid2D.h"
#include "globals.h"

Grid2DEngine* engine = nullptr;

//extern bool ENGINE_LIMIT_FPS;
bool ENGINE_LIMIT_FPS;

int main(int argc, char* argv[]) {
	
	//Grid2D grid = Grid2D(10, 10);

	//grid.DEBUG_printGrid();

	//return EXIT_SUCCESS;

	
	engine = new Grid2DEngine();

	std::vector<std::string> vTileProperties = {"isEnemyRoad", "isEnemySpawn", "isTowerBuildable", "isEnemyGoal"};

	engine->addGrid2D("map1", 10, 10, vTileProperties, true);

	engine->init("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	ENGINE_LIMIT_FPS = true;

	while (engine->running()) {
		engine->engineLoop();
	}

	engine->clean();

	return EXIT_SUCCESS;
	
}