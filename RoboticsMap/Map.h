/*
 * Map.h
 *
 *  Created on: May 24, 2016
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_

class Map {
private:
	double _mapResolution;
	double _gridResolution;
	char* _mapPath;
	std::vector<unsigned char> _bufMap;
public:
	Map(double mapResolution,double gridResolution,char * mapPath);
	virtual ~Map();
	void BufferMap();
};

#endif /* MAP_H_ */
