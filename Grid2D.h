#pragma once
#ifndef GRID2D_HPP
#define GRID2D_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>

enum class TILE_TYPE {
	DEFAULT = -1,
	PLAIN = 0,
	MOUNTAIN = 1
};

class Tile {
public:
	Tile();
	Tile(unsigned int x, unsigned int y, std::vector<std::string> vPropertyList, TILE_TYPE t);
	~Tile();

	TILE_TYPE getType() { return this->type; }
	bool wasModified() { return this->modified; }
	void setModified(bool b) { this->modified = b; }
	int* getColor();

	bool getProperty(std::string prop) {
		if (this->mProperties.find(prop) != this->mProperties.end())
			return this->mProperties[prop];
		std::cerr << prop << " is not a tile property!" << std::endl;
		return false;
	}
	//Return true if add was successful, false otherwise
	bool setProperty(std::string prop, bool value, bool ADD_IF_NOT_IN_MAP = false) {
		if (!ADD_IF_NOT_IN_MAP && this->mProperties.find(prop) == this->mProperties.end()) {
			std::cerr << prop << " is not a tile property! SetProperty canceled" << std::endl;
			return false;
		}
		this->mProperties[prop] = value;
		return true;
	}

	std::string toString();

private:
	unsigned int xpos;
	unsigned int ypos;

	TILE_TYPE type;

	bool modified = true;

	std::map<std::string, bool> mProperties = std::map<std::string, bool>();
};

/////////////////////////////////////////////////////////////////////

class Grid2D {
public:
	Grid2D(unsigned int cols, unsigned int rows, std::vector<std::string> vTilesProperties);
	Grid2D() : Grid2D(10, 10, std::vector<std::string>()) {};
	~Grid2D();

	void DEBUG_printGrid();

	Tile* get(unsigned int x, unsigned int y) {
		return &this->tileGrid[y][x];
	}
	unsigned int getColumns() { return this->columns; }
	unsigned int getRows() { return this->rows; }

private:
	unsigned int columns;
	unsigned int rows;
	Tile** tileGrid;
};

#endif GRID2D_HPP

