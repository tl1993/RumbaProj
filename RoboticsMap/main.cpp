/*
 * main.cpp
 *
 *  Authors:
 *  	Ravit Siman - Tov, 311305130
 *  	Tomer Laniado, 311117097
 *  	Gal Navon, 204357305
 *
 */

#include "pngUtil.h"
#include "Map.h"
#include "Matrix.h"
#include "Utils.h"
#include "Map.h"
#include <iostream>

using namespace std;

int main()
{
      char * mapPath = "./roboticLabMap.png";
	   Map mymap(2.5,10,mapPath);
//	MapHandler("./roboticLabMap.png");
	mymap.BlowMap();
    Matrix<Utils::CELL_STATUS> grid = mymap.MapToGrid();

	grid.print();

	return (0);
}
