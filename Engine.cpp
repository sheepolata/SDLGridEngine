#include "Engine.h"

Grid2DEngine::Grid2DEngine() {
	this->isRunning = false;
	this->window = nullptr;
	this->renderer = nullptr;

	this->width = 0;
	this->height = 0;

	this->mGrids2D = std::map<std::string, Grid2D*>();
	current_map = "None";
}

Grid2DEngine::~Grid2DEngine() {
	this->mGrids2D.clear();
}

void Grid2DEngine::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
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



void Grid2DEngine::engineLoop() {
	if (!this->bInitialised) {
		std::cerr << "Engine not initialised!" << std::endl;
		return;
	}

	Uint32 now = SDL_GetTicks();

	this->handleEvents();

	if (ENGINE_LIMIT_FPS) {
		if (next_game_step <= now) {

			int computer_is_too_slow_limit = 10; // max number of advances per render, adjust this according to your minimum playable fps

			// Loop until all steps are executed or computer_is_too_slow_limit is reached
			while ((next_game_step <= now) && (computer_is_too_slow_limit--)) {
				this->update();
				next_game_step += time_step_ms; // count 1 game tick done
			}

			this->render();
		}
		else {
			// we're too fast, wait a bit.
			if (next_game_step - now > 10) {
				SDL_Delay(next_game_step - now);
			}
		}
	}
	else {
		this->update();

		this->render();
	}

	frametime_tracker.push_back(SDL_GetTicks() - now);
	if (frametime_tracker.size() > 60) frametime_tracker.pop_front();
	if (!this->frametime_tracker.empty()) {
		float _avg = (float)std::accumulate(frametime_tracker.begin(), frametime_tracker.end(), 0.0) / (float)frametime_tracker.size();
		float _fps = 1000.0f / _avg;
		int _ifps = (int)(_fps/2.0f);
		SDL_SetWindowTitle(this->window, (this->current_map + ". " + std::to_string(_ifps) + "fps").c_str());
	}

}

void Grid2DEngine::handleEvents() {
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
		default:
			break;
	}
}

void Grid2DEngine::update() {
	
}

void Grid2DEngine::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderClear(this->renderer);
	//This is where we would render stuff

	this->drawGrid(this->current_map);
	//this->grid.DEBUG_printGrid();

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderDrawLine(renderer, 50, 50, 300, 300);
	//SDL_Rect rect = { 50, 50, 150, 150 };
	//SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);
}

void Grid2DEngine::clean() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();

	std::cout << "Engine cleaned!" << std::endl;
}

bool Grid2DEngine::running() {
	return this->isRunning;
}

void Grid2DEngine::addGrid2D(std::string name, unsigned int w, unsigned int h, std::vector<std::string> vTileProperties, bool SET_AS_CURRENT_MAP) {
	this->mGrids2D[name] = new Grid2D(w, h, vTileProperties);
	if (SET_AS_CURRENT_MAP)
		this->current_map = name;
}

void Grid2DEngine::drawGrid(std::string name) {

	auto it = this->mGrids2D.find(name);
	if (it != this->mGrids2D.end()) {
		//Grid2D* grid = &this->mGrids2D[name];
		Grid2D* grid = it->second;

		float rect_size_width = (float)this->width / (float)grid->getColumns();
		float rect_size_height = (float)this->height / (float)grid->getRows();

		for (size_t y = 0; y < grid->getRows(); y++) {
			for (size_t x = 0; x < grid->getColumns(); x++) {
				int* colors = grid->get(x, y)->getColor();
				//int* colors = new int[4] { 128, 45, 95, 255 };
				SDL_SetRenderDrawColor(renderer, colors[0], colors[1], colors[2], colors[3]);
				SDL_FRect rect = { x * rect_size_width, y * rect_size_height, rect_size_width, rect_size_height };
				SDL_RenderFillRectF(this->renderer, &rect);
				delete[] colors;
			}
		}
	}
	else {
		std::cerr << name << " is not stored in the Engine!" << std::endl;
	}
}