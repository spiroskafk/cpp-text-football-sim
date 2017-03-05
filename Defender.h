#ifndef DEFENDER_H
#define DEFENDER_H

#include <string>

#include "Player.h"

using namespace std;

class Defender : public Player
{
public:
	Defender(int, int, int, int, int, string, bool, Game *);

	void setYellowCard(bool);
	bool hasYellowCard();
	
	virtual void specialMove();
private:
	bool yellowCard;
	string id;
};


#endif