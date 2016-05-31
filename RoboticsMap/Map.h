/*
 * Map.h
 *
 *  Created on: May 24, 2016
 *      Author: user
 */

#include <iostream>
#include <vector>
#include "pngUtil.h"
#include "Matrix.h"
#include "Utils.h"

#ifndef MAP_H_
#define MAP_H_

class Map {
private:
	double _mapResolution;
	double _gridResolution;
	char* _mapPath;
	int _mapHeight;
	int _mapWidth;
	void encodeOneStep(const char* filename, std::vector<unsigned char> image,
			unsigned width, unsigned height);
	void decodeOneStep(const char* filename);
	std::vector<unsigned char> _blowMap;
public:
	Map(double mapResolution,double gridResolution,char * mapPath);
	virtual ~Map();
	void BlowMap();
	void PrintBMap();
	std::vector<unsigned char> GetBlowMap() { return _blowMap; };
	Utils::CELL_STATUS CheckPixle(int start_index);
	Utils::CELL_STATUS CheckCell(int i,int j,int cell_size);
	Matrix<Utils::CELL_STATUS> MapToGrid();
};

#endif /* MAP_H_ */
