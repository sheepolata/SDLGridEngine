#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <iostream>
#include "Grid2D.h"
#include <list>
#include <numeric>


class Engine {
public:
	Engine();
	Engine(unsigned int grid_cols, unsigned int grid_rows);
	~Engine();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	
	void engineLoop();

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

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

	Grid2D grid;

	void drawGrid();
};



#endif GAME_HPP
