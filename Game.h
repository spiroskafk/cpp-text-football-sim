#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

class Map;
class Team;
class Ball;
class Player;

using namespace std;

class Game
{
public:
	// Constructor
	Game();

	void init();        /* Arxikopoihsi */
	void start();       /* Arxizei tin prosomoiwsi */
	void runTurn();	    /* Trexei action() */
	void placeOnMap();  /* Topothetise se xarti */
	void printPlayers();
	bool scored();
	void sentra(string);

	// setters
	void setRounds(int);
	void setGoals(int);

	// getters
	int getRounds();
	int getGoals();
	Team *getTeam(string);
	Ball *getBall();
	Map *getMap();

private:
	int rounds;
	int goals;
	int ballRounds;
	Map *map;
	Team *redTeam;
	Team *blueTeam;
	Ball *ball;
	vector<Player *> redPlayers;
	vector<Player *> bluePlayers;
};

#endif