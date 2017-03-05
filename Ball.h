#ifndef BALL_H
#define BALL_H

#include <string>
using namespace std;

class Player;
class Game;

class Ball
{
public:
	// constructor
	Ball(int, int, string, Player*, Player*, Game*);

	void assignBall(Player *);
	void assignBall();
	void changeBall(int, int);

	// setters
	void setX(int);
	void setY(int);
	void setID(string);
	void setCurrentPlayer(Player*);
	void setPreviousPlayer(Player*);

	// getters
	int getX() const;
	int getY() const;
	string getID();
	Player *getCurrentPlayer() const;						/* Epistrefei ton paixti pou exei tin mpapla */
	Player *getPreviousPlayer() const;                      /* Epistrefei ton paixti pou eixe tin mpala */

private:
	int x;													/* Sintetagmeni x tis mpalas */          
	int y;													/* Sintetagmeni y tis mpalas*/
	string id;							
	Player *currentPlayer;									/* Deixnei ston paixti pou exei tin mpala */
	Player *previousPlayer;									/* Deixnei ston prohgoumeno paixti pou eixe tin mpala */
	Game *game;												/* Deiktis se antikeimeno game */
};

#endif