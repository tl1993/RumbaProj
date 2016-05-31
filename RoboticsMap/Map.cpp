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


void Map::BufferMap(){
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
		unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
		if (error)
			std::cout << "decoder error " << error << ": "
			<< lodepng_error_text(error) << std::endl;

		 _bufMap.resize(width * height * 4);

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
		 				color = 255;
		 				_bufMap[y * width * 4 + x * 4 + 0] = color;
		 				_bufMap[y * width * 4 + x * 4 + 1] = color;
		 				_bufMap[y * width * 4 + x * 4 + 2] = color;
		 				_bufMap[y * width * 4 + x * 4 + 3] = 255;
		 			}
		 			//Obstacle is found:
		 			else
		 			{
		 				//The color is black:
		 				color = 0;

		 				// Scanning the square area around the obstacle and resize it in the new map
		 				for (unsigned int indexHeight = (y-robotPixelHeight); indexHeight < (y+robotPixelHeight); indexHeight++)
		 				{
		 					for (unsigned int indexWidth = (x-robotPixelWidth); indexWidth < (x+robotPixelWidth); indexWidth++)
		 					{
		 						if ((indexHeight <= height) && (indexWidth <=width) && (indexHeight >= 0) && (indexWidth >=0))
		 							{
		 								_bufMap[(indexHeight * width * 4) + (indexWidth * 4) + 0] = color;
		 								_bufMap[(indexHeight * width * 4) + (indexWidth* 4) + 1] = color;
		 								_bufMap[(indexHeight * width * 4) + (indexWidth * 4) + 2] = color;
		 								_bufMap[(indexHeight * width * 4) + (indexWidth * 4) + 3] = 255;
		 							}
		 					}
		 				}
		 			}
		 		}
		 	}
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}
