#ifndef MAP_H
#define MAP_H

#define ROW 10
#define COL 6

#include <string>
using namespace std;

class Map
{
public:
	Map();

	void printMap();					   /* Ektipwnei xarti */
	bool isEmpty(int, int);				   /* ELenxei an i sigkekrimeni thesi einai adeia */
	void setPositions(int, int, string);   /* Orizei tin thesi sto xarti */
	string getMapContent(int, int);
private:
	string map[ROW][COL];
};

#endif