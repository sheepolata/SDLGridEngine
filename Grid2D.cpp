#include "Grid2D.h"


Tile::Tile() {
	this->xpos = 0;
	this->ypos = 0;
	this->type = TILE_TYPE::DEFAULT;
}

Tile::Tile(unsigned int x, unsigned int y, std::vector<std::string> vPropertyList, TILE_TYPE t) {
	this->xpos = x;
	this->ypos = y;
	this->type = t;

	for (std::string prop : vPropertyList) {
		this->mProperties[prop] = false;
	}
}

Tile::~Tile() {
}

int* Tile::getColor() {
	int* col = new int[4];

	switch (this->type) {
	case TILE_TYPE::MOUNTAIN:
		col[0] = 139;
		col[1] = 69;
		col[2] = 19;
		break;
	case TILE_TYPE::PLAIN:
		col[0] = 85;
		col[1] = 107;
		col[2] = 47;
		break;
	case TILE_TYPE::DEFAULT:
	default:
		col[0] = 255;
		col[1] = 255;
		col[2] = 255;
		break;
	}

	col[3] = 255;

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


Grid2D::Grid2D(unsigned int cols, unsigned int rows, std::vector<std::string> vTileProperties) {
	this->columns = cols;
	this->rows = rows;

	this->tileGrid = new Tile*[this->rows];
	for (size_t i = 0; i < this->rows; i++) {
		this->tileGrid[i] = new Tile[this->columns];
	}

	for (size_t y = 0; y < rows; y++) {
		for (size_t x = 0; x < cols; x++) {
			TILE_TYPE t = rand()%3 == 0? TILE_TYPE::MOUNTAIN : TILE_TYPE::PLAIN;
			this->tileGrid[y][x] = Tile(x, y, vTileProperties, t);
		}
	}
}

Grid2D::~Grid2D() {
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
