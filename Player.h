#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Game;

using namespace std;

class Player
{
public:
	Player(int, int, int, int, int, string, Game *);

	// setters
	void setX(int);
	void setY(int);
	void setPlayerNum(int);
	void setTargetCol(int);
	void setMoveCol(int);
	void setName(string);
	void setID(string);

	// getters
	int getX();
	int getY();
	int getPlayerNum();
	int getTargetCol();
	int getMoveCol();
	string getName();
	string getID();
	Game* getGameInstance();
	Player *getPlayer(int, int);

	bool hasBall();

	void move();
	virtual void printPlayerInfo();
	virtual void transfer();
	virtual void specialMove() = 0;
private:
	int x;
	int y;
	int playerNum;   /* arithmos fanelas */
	int targetCol;   /* grammiStoxos*/
	int moveCol;     /* grammiKinisis*/
	string name;     /* onoma paikti*/
	string id;
	Game *game;
};

#endif