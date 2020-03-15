#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <iostream>
#include <list>
#include <numeric>

#include "Grid2D.h"
#include "globals.h"

class Grid2DEngine {
public:
	Grid2DEngine();
	~Grid2DEngine();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	
	void engineLoop();

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

	std::string getCurrentMap() { return this->current_map; }
	void setCurrentMap(std::string s) { this->current_map = s; }

	void addGrid2D(std::string name, unsigned int w, unsigned int h, bool SET_AS_CURRENT_MAP=false);

private:
	Uint32 max_fps = 60;
	Uint32 time_step_ms = 1000 / max_fps;
	Uint32 next_game_step = SDL_GetTicks(); // initial value
	std::list<Uint32> frametime_tracker = std::list<Uint32>();

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	int width; 
	int height;

	std::map<std::string, Grid2D*> mGrids2D;
	std::string current_map;

	void drawGrid(std::string name);
};



#endif GAME_HPP

