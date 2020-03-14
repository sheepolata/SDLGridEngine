#pragma once
#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <map>
#include <vector>
#include <string>

struct sTILE_INFO {
	int* type_color;
};

extern bool ENGINE_LIMIT_FPS;

extern std::map<std::string, sTILE_INFO> mTILE_INFO;


#endif GLOBALS_HPP