#include "Grid2D.h"


Tile::Tile() {
	this->xpos = 0;
	this->ypos = 0;
	this->type = TILE_TYPE::DEFAULT;
}

Tile::Tile(unsigned int x, unsigned int y, TILE_TYPE t) {
	this->xpos = x;
	this->ypos = y;
	this->type = t;
}

Tile::~Tile() {
}

int* Tile::getColor() {
	int* col = new int[4];

	col[0] = rand() % 255;
	col[1] = rand() % 255;
	col[2] = rand() % 255;
	col[3] = rand() % 255;

	return col;
}

std::string Tile::toString() {
	std::string str = "";

	str.append(std::to_string(this->xpos));
	str.append(", ");
	str.append(std::to_string(this->ypos));
	str.append(" / ");
	str.append(std::to_string((int)this->type));
	
	return str;
}


/////////////////////////////////////////////////////////////////////


Grid2D::Grid2D(unsigned int cols, unsigned int rows) {
	this->columns = cols;
	this->rows = rows;

	this->tileGrid = new Tile*[this->rows];
	for (size_t i = 0; i < this->rows; i++) {
		this->tileGrid[i] = new Tile[this->columns];
	}

	//this->tileGrid = new (Tile**)[rows];
	//for (size_t y = 0; y < rows; y++) {
	//	this->tileGrid[y] = new (Tile*)[cols];
	//}
	for (size_t y = 0; y < rows; y++) {
		for (size_t x = 0; x < cols; x++) {
			this->tileGrid[y][x] = Tile(x, y, TILE_TYPE::DEFAULT);
		}
	}
}

Grid2D::~Grid2D() {
	/*for (size_t y = 0; y < this->rows; y++) {
		for (size_t x = 0; x < this->columns; x++) {
			delete this->tileGrid[y][x];
		}
	}*/
	for (size_t y = 0; y < this->rows; y++) {
		delete[] this->tileGrid[y];
	}

	delete[] this->tileGrid;
}

void Grid2D::DEBUG_printGrid() {
	for (size_t y = 0; y < this->rows; y++) {
		for (size_t x = 0; x < this->columns; x++) {
			std::cout << this->tileGrid[y][x].toString() << " ";
		}
		std::cout << std::endl;
	}
}
