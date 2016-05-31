/*
 * pngUtil.cpp
 *
 *  Authors:
 *  	Ravit Siman - Tov, 311305130
 *  	Tomer Laniado, 311117097
 *  	Gal Navon, 204357305
 *
 */
#include "pngUtil.h"
#include "lodepng.h"
#include <iostream>

//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, std::vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}

void decodeOneStep(const char* filename) {
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
void MapHandler(const char* filename)
{
	//Constants for robot size and resolution
	const int ROBOT_WIDTH = 30;
	const  int ROBOT_HEIGHT = 30;
	const double RESOLUTION = 2.5;

	//Calculating the size of the robot in the map, by pixels:
	double robotPixelWidth = (ROBOT_WIDTH/2)/RESOLUTION;
	double robotPixelHeight = (ROBOT_HEIGHT/2)/RESOLUTION;

	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> navImage; //the raw pixels
	navImage.resize(width * height * 4);
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
				navImage[y * width * 4 + x * 4 + 0] = color;
				navImage[y * width * 4 + x * 4 + 1] = color;
				navImage[y * width * 4 + x * 4 + 2] = color;
				navImage[y * width * 4 + x * 4 + 3] = 255;
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
								navImage[(indexHeight * width * 4) + (indexWidth * 4) + 0] = color;
								navImage[(indexHeight * width * 4) + (indexWidth* 4) + 1] = color;
								navImage[(indexHeight * width * 4) + (indexWidth * 4) + 2] = color;
								navImage[(indexHeight * width * 4) + (indexWidth * 4) + 3] = 255;
							}
					}
				}
			}
		}
	}

	encodeOneStep("newMap.png", navImage, width, height);
}
