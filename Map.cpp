#include <iostream>
#include <string>
#include "Map.h"

using namespace std;


Map::Map()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j] = "---";
		}
	}
}

void Map::printMap()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool Map::isEmpty(int x, int y)
{

	if (map[x][y].compare(0, 3, "---") == 0)
	{
		return true;
	}


	return false;
}

void Map::setPositions(int x, int y, string id)
{
	map[x][y] = id;
}

string Map::getMapContent(int x, int y)
{
	return map[x][y];
}