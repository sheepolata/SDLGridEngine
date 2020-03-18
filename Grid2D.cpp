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
	str.append(" / ");

	for (auto it = this->mProperties.begin(); it != this->mProperties.end(); it++) {
		//std::cout << it->first  // string (key)
			//<< ':'
			//<< it->second   // string's value 
			//<< std::endl;
		str.append(it->first);
		str.append(":");
		str.append(std::to_string(it->second));
		str.append(" ");
	}

	
	return str;
}


/////////////////////////////////////////////////////////////////////


