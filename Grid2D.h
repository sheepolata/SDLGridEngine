#pragma once
#ifndef GRID2D_HPP
#define GRID2D_HPP

#include <string>
#include <iostream>

enum class TILE_TYPE {
	DEFAULT = -1
};

class Tile {
public:
	Tile();
	Tile(unsigned int x, unsigned int y, TILE_TYPE t);
	~Tile();

	TILE_TYPE getType() {
		return this->type;
	}

	int* getColor();

	std::string toString();

private:
	unsigned int xpos;
	unsigned int ypos;

	TILE_TYPE type;
};

/////////////////////////////////////////////////////////////////////

class Grid2D {
public:
	Grid2D(unsigned int cols, unsigned int rows);
	~Grid2D();

	void DEBUG_printGrid();

	Tile get(unsigned int x, unsigned int y) {
		return this->tileGrid[y][x];
	}
	unsigned int getColumns() { return this->columns; }
	unsigned int getRows() { return this->rows; }

private:
	unsigned int columns;
	unsigned int rows;
	Tile** tileGrid;
};

#endif GRID2D_HPP

