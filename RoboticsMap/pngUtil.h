/*
 * pngUtil.h
 *
 *  Authors:
 *  	Ravit Siman - Tov, 311305130
 *  	Tomer Laniado, 311117097
 *  	Gal Navon, 204357305
 *
 */

#ifndef PNGUTIL_H_
#define PNGUTIL_H_
#include <iostream>
#include <vector>
void encodeOneStep(const char* filename, std::vector<unsigned char> image, unsigned width, unsigned height);
void decodeOneStep(const char* filename);
void MapHandler(const char* filename);

#endif /* PNGUTIL_H_ */
