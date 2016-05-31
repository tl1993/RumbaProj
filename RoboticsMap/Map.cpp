/*
 * Map.cpp
 *
 *  Created on: May 24, 2016
 *      Author: user
 */

#include "Map.h"
#include "pngUtil.h"
#include "lodepng.h"
#include <iostream>

Map::Map(double mapResolution,double gridResolution,char* mapPath){
	_mapResolution = mapResolution;
	_gridResolution = gridResolution;
	_mapPath = mapPath;
}

//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void Map::encodeOneStep(const char* filename, std::vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}

void Map::decodeOneStep(const char* filename) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void Map::BlowMap(){
	//should come from conf manager
	//Constants for robot size and resolution
		const int ROBOT_WIDTH = 30;
		const  int ROBOT_HEIGHT = 30;

	//Calculating the size of the robot in the map, by pixels:
		double robotPixelWidth = (ROBOT_WIDTH/2)/_mapResolution;
		double robotPixelHeight = (ROBOT_HEIGHT/2)/_mapResolution;

		std::vector<unsigned char> image; //the raw pixels
		unsigned width, height;
		unsigned x, y;
	//decode
		unsigned error = lodepng::decode(image, width, height, _mapPath);

	//if there's an error, display it
		if (error)
			std::cout << "decoder error " << error << ": "
			<< lodepng_error_text(error) << std::endl;

		  _mapHeight = height;
		  _mapWidth = width;
		 _blowMap.resize(width * height * 4);

		 unsigned char color;

		 	//Scanning the raw pixels in the image
		 	for (y = 0; y < height; y++)
		 	{
		 		for (x = 0; x < width; x++)
		 		{
		 			//If it's not an obstacle:
		 			if (image[y * width * 4 + x * 4 + 0]
		 					|| image[y * width * 4 + x * 4 + 1]
		 					|| image[y * width * 4 + x * 4 + 2])
		 			{
		 				color = Utils::WHITE;
		 				_blowMap[y * width * 4 + x * 4 + 0] = color;
		 				_blowMap[y * width * 4 + x * 4 + 1] = color;
		 				_blowMap[y * width * 4 + x * 4 + 2] = color;
		 				_blowMap[y * width * 4 + x * 4 + 3] = 255;
		 			}
		 			//Obstacle is found:
		 			else
		 			{
		 				//The color is black:
		 				color = Utils::BLACK;

		 				// Scanning the square area around the obstacle and resize it in the new map
		 				for (unsigned int indexHeight = (y-robotPixelHeight); indexHeight < (y+robotPixelHeight); indexHeight++)
		 				{
		 					for (unsigned int indexWidth = (x-robotPixelWidth); indexWidth < (x+robotPixelWidth); indexWidth++)
		 					{
		 						if ((indexHeight <= height) && (indexWidth <=width) && (indexHeight >= 0) && (indexWidth >=0))
		 							{
		 								_blowMap[(indexHeight * width * 4) + (indexWidth * 4) + 0] = color;
		 								_blowMap[(indexHeight * width * 4) + (indexWidth* 4) + 1] = color;
		 								_blowMap[(indexHeight * width * 4) + (indexWidth * 4) + 2] = color;
		 								_blowMap[(indexHeight * width * 4) + (indexWidth * 4) + 3] = 255;
		 							}
		 					}
		 				}
		 			}
		 		}
		 	}
}
void Map::PrintBMap()
{
	encodeOneStep("newMap.png",_blowMap, _mapWidth, _mapHeight);
}
Map::~Map() {
	// TODO Auto-generated destructor stub
	 _blowMap.~vector();
}

Utils::CELL_STATUS Map::CheckPixle(int start_index)
{

	if(_blowMap[start_index + 0] == Utils::BLACK ||
	   _blowMap[start_index + 1] == Utils::BLACK ||
	   _blowMap[start_index + 2] == Utils::BLACK)
	{
		return Utils::OBSTACLE;
	}
	else
	{
		return Utils::FREE;
	}
}

Utils::CELL_STATUS Map::CheckCell(int height, int width, int block_size)
{
	//cout << (height * 4 * _mapWidth)  + (width * 4);
	for(int i = 0; i < block_size;i++)
	{
		for(int j = 0; j < block_size;j++)
		{

			if(CheckPixle((height * 4 * _mapWidth * block_size) + (i * _mapWidth * 4) + (width * 4) + (j * 4)) == Utils::OBSTACLE)
			{
				return Utils::OBSTACLE;
			}
		}
	}
	return Utils::FREE;
}

Matrix<Utils::CELL_STATUS> Map::MapToGrid()
{
// Block size is calculated by map resolution
	int block_size = _gridResolution / _mapResolution;

// Calculate grid height and width by using the map sizes and the grid resolution
	int grid_height = _mapHeight / block_size;
	int grid_width  = _mapWidth / block_size;

	Matrix<Utils::CELL_STATUS> grid(grid_height,grid_width);

	for (int row = 0;  row < grid_height; row++)
	{
		for (int col = 0;  col < grid_width; col++)
		{
			grid.set(row,col,CheckCell(row,col,block_size));
		}
	}

	return grid;
}
