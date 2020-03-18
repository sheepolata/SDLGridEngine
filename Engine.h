#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <iostream>
#include <list>
#include <numeric>

#include "Grid2D.h"
#include "Entity.h"
#include "globals.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL2_framerate.h"

template<class cTile>
class Grid2DEngine {
public:
	Grid2DEngine() {
		this->isRunning = false;
		this->window = nullptr;
		this->renderer = nullptr;

		this->width = 0;
		this->height = 0;

		this->mGrids2D = std::map<std::string, Grid2D<cTile>*>();
		current_map = "None";

		this->e = new Entity();

		SDL_initFramerate(&this->sFPSManager);
		SDL_setFramerate(&this->sFPSManager, this->max_fps);
	}
	~Grid2DEngine() {
		this->mGrids2D.clear();
		delete this->e;
	}

	void init(const char* title, int x, int y, int width, int height, bool fullscreen) {
		this->width = width;
		this->height = height;
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
			std::cout << "SDL successfully initialised!" << std::endl;


			int flags = 0;
			if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

			this->window = SDL_CreateWindow(title, x, y, width, height, flags | SDL_WINDOW_RESIZABLE);
			if (this->window) {
				std::cout << "Window created!" << std::endl;
			}
			else {
				this->isRunning = false;
				std::cout << "Window could not be created!" << std::endl;
				return;
			}

			this->renderer = SDL_CreateRenderer(window, -1, 0);
			if (this->renderer) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				std::cout << "Renderer created!" << std::endl;
			}
			else {
				this->isRunning = false;
				std::cout << "Renderer could not be created!" << std::endl;
				return;
			}

			this->bInitialised = true;
			this->isRunning = true;
		}
		else {
			this->isRunning = false;
			std::cout << "SDL could not initialize! SDL error: " << SDL_GetError() << std::endl;
		}
	}

	void engineLoop() {
		if (!this->bInitialised) {
			std::cerr << "Engine not initialised!" << std::endl;
			return;
		}

		this->fElapsedTime = SDL_framerateDelay(&this->sFPSManager) / 1000.0f;

		SDL_SetWindowTitle(this->window, (this->current_map + ". " + std::to_string(SDL_getFramerate(&this->sFPSManager)) + "fps, fElapedTime=" + std::to_string(this->fElapsedTime)).c_str());

		this->handleEvents();

		this->update();

		this->render();
	}

	void handleEvents() {
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type) {
		case SDL_QUIT:
			this->isRunning = false;
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				this->width = event.window.data1;
				this->height = event.window.data2;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_r:
				break;
			case SDLK_ESCAPE:
				this->isRunning = false;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP: {
			int mp_x, mp_y;
			SDL_GetMouseState(&mp_x, &mp_y);
			int* grid_pos = mousePosToGridPos(mp_x, mp_y);

			if (this->selected != nullptr) {
				//std::cout << this->selected->getXPos() << this->selected->getYPos() << " ";
				//std::cout << grid_pos[0] << grid_pos[1] << std::endl;
				if (this->selected->getXPos() == grid_pos[0]
					&& this->selected->getYPos() == grid_pos[1]) {
					this->selected = nullptr;
				}
				else {
					this->selected = this->mGrids2D[this->current_map]->get(grid_pos[0], grid_pos[1]);
					std::cout << this->selected->toString() << std::endl;
				}
			}
			else {
				this->selected = this->mGrids2D[this->current_map]->get(grid_pos[0], grid_pos[1]);
				std::cout << this->selected->toString() << std::endl;
			}


			delete[] grid_pos;
			break;
		}
		default:
			break;
		}
	}
	void update() {

	}
	void render() {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_RenderClear(this->renderer);
		//This is where we would render stuff

		this->drawGrid(this->current_map);

		filledEllipseRGBA(renderer, (Sint16)e->getXPos(), (Sint16)e->getYPos(), 10, 10, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		//SDL_RenderDrawPointF(renderer, this->e->getXPos(), this->e->getYPos());

		SDL_RenderPresent(renderer);
	}
	void clean() {
		SDL_DestroyWindow(this->window);
		SDL_DestroyRenderer(this->renderer);
		SDL_Quit();

		std::cout << "Engine cleaned!" << std::endl;
	}

	bool running() {
		return this->isRunning;
	}

	std::string getCurrentMap() { return this->current_map; }
	void setCurrentMap(std::string s) { this->current_map = s; }

	void addGrid2D(std::string name, unsigned int w, unsigned int h, std::vector<std::string> vTileProperties, bool SET_AS_CURRENT_MAP = false) {
		this->mGrids2D[name] = new Grid2D<cTile>(w, h, vTileProperties);
		if (SET_AS_CURRENT_MAP)
			this->current_map = name;
	}

private:
	int max_fps = 60;
	FPSmanager sFPSManager;

	Uint32 fLastTime = 0;
	float fElapsedTime = 0.0f;

	bool isRunning;
	bool bInitialised = false;
	SDL_Window* window;
	SDL_Renderer* renderer;

	int width;
	int height;

	std::vector<std::string> vTilePropertyList;
	std::map<std::string, Grid2D<cTile>*> mGrids2D;
	std::string current_map;

	cTile* selected = nullptr;

	int* mousePosToGridPos(int mpx, int mpy) {
		int gx = -1; int gy = -1;
		int* res = new int[2];
		res[0] = gx;
		res[1] = gy;
		if (this->current_map == "None") return res;

		Grid2D<cTile>* grid = this->mGrids2D[this->current_map];
		float x_slice = (float)this->width / (float)grid->getColumns();
		float y_slice = (float)this->height / (float)grid->getRows();

		gx = mpx / (int)x_slice;
		gy = mpy / (int)y_slice;

		res[0] = gx;
		res[1] = gy;
		return res;
	}

	Entity* e;

	void drawGrid(std::string name) {

		auto it = this->mGrids2D.find(name);
		if (it != this->mGrids2D.end()) {
			//Grid2D* grid = &this->mGrids2D[name];
			Grid2D<cTile>* grid = it->second;

			float rect_size_width = (float)this->width / (float)grid->getColumns();
			float rect_size_height = (float)this->height / (float)grid->getRows();

			for (size_t y = 0; y < grid->getRows(); y++) {
				for (size_t x = 0; x < grid->getColumns(); x++) {
					int* colors = grid->get(x, y)->getColor();
					//int* colors = new int[4] { 128, 45, 95, 255 };
					SDL_SetRenderDrawColor(renderer, colors[0], colors[1], colors[2], colors[3]);
					SDL_FRect rect = { x * rect_size_width, y * rect_size_height, rect_size_width, rect_size_height };
					SDL_RenderFillRectF(this->renderer, &rect);

					if (this->selected != nullptr && this->selected == grid->get(x, y)) {
						SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
						SDL_RenderDrawRectF(renderer, &rect);
					}

					delete[] colors;
				}
			}
		}
		else {
			std::cerr << name << " is not stored in the Engine!" << std::endl;
		}
	}

};



#endif GAME_HPP

