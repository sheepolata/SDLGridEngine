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

template<class cTile>
class Grid2D {
public:
	Grid2D(unsigned int cols, unsigned int rows, std::vector<std::string> vTilesProperties) {
		this->columns = cols;
		this->rows = rows;

		this->tileGrid = new Tile * [this->rows];
		for (size_t i = 0; i < this->rows; i++) {
			this->tileGrid[i] = new Tile[this->columns];
		}

		for (size_t y = 0; y < rows; y++) {
			for (size_t x = 0; x < cols; x++) {
				TILE_TYPE t = rand() % 3 == 0 ? TILE_TYPE::MOUNTAIN : TILE_TYPE::PLAIN;
				this->tileGrid[y][x] = cTile(x, y, vTilesProperties, t);
			}
		}
	}
	Grid2D() : Grid2D(10, 10, std::vector<std::string>()) {};
	~Grid2D() {
		for (size_t y = 0; y < this->rows; y++) {
			delete[] this->tileGrid[y];
		}

		delete[] this->tileGrid;
	}

	void DEBUG_printGrid() {
		for (size_t y = 0; y < this->rows; y++) {
			for (size_t x = 0; x < this->columns; x++) {
				std::cout << this->tileGrid[y][x].toString() << " ";
			}
			std::cout << std::endl;
		}
	}


	cTile* get(unsigned int x, unsigned int y) {
		return &this->tileGrid[y][x];
	}
	unsigned int getColumns() { return this->columns; }
	unsigned int getRows() { return this->rows; }

private:
	unsigned int columns;
	unsigned int rows;
	cTile** tileGrid;
};

#endif GRID2D_HPP

