#ifndef STRIKER_H
#define STRIKER_H

#include <string> 

#include "Player.h"

using namespace std;

class Striker : public Player
{
public:
	Striker(int, int, int, int, int, string, Game *);


	virtual void transfer();
	virtual void specialMove();
private:
	//string id;
};

#endif