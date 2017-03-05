#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "Ball.h"
#include "Team.h"

using namespace std;

Player::Player(int x, int y, int pNum, int tCol, int mCol, string name, Game *game)
{
	setX(x);
	setY(y);
	setPlayerNum(pNum);
	setTargetCol(tCol);
	setMoveCol(mCol);
	setName(name);
	this->game = game;
}

/* Sinartisi kinisis */
void Player::move()
{
	Map *map = game->getMap();
	Ball *ball = game->getBall();
	bool flag = false;


	// 1 - kinisi aristera, 2 - kinisi deksia
	int randomMove = 1 + (rand() % 2);

	if (randomMove == 1)
	{
		// Elenxos an einai adeia i thesi aristera mas h an tha vgoume ektos orion
		if (getY() == 0) return;
		if (map->isEmpty(getX(), getY() - 1) && getY() != 0)
		{
			if (hasBall())
			{
				flag = true;
			}
			// Svinoume tin palia thesi tou paixti ston xarti
			map->setPositions(getX(), getY(), "---");
			setY(getY() - 1);

			// Thetoume tin nea thesi tou paixti ston xarti
			map->setPositions(getX(), getY(), getID());

			if (flag)
			{
				ball->setX(getX());
				ball->setY(getY());
			}
		}
	}
	else if (randomMove == 2)
	{
		// Elenxos an einai adeia i thesi deksia mas h an tha vgoume ektos orion
		if (getY() == 5) return;
		if (map->isEmpty(getX(), getY() + 1) && getY() != 5)
		{
			if (hasBall())
			{
				flag = true;
			}
			// Svinoume tin palia thesi tou paixti ston xarti
			map->setPositions(getX(), getY(), "---");
			setY(getY() + 1);

			// Thetoume tin nea thesi tou paixti ston xarti
			map->setPositions(getX(), getY(), getID());

			if (flag)
			{
				ball->setX(getX());
				ball->setY(getY());
			}
		}
	}
}


void Player::transfer()
{
	Ball *ball = game->getBall();


	if (hasBall())
	{
		// Epilegoume tixaia mia stili tis grammisStoxou 
		int randomCol = rand() % 6;
		ball->changeBall(getTargetCol(), randomCol);
		cout << "Edwse pasa stis : " << ball->getX() << "," << ball->getY() << endl;

		/*// Katexei tin mpala
		

		// Allazoume to id tou paixti wste na min katexei tin mpala pleon
		string s = map->getMapContent(p->getX(), p->getY());
		setID(s.substr(0, 1) + s.substr(1, 1) + "-");

		// to vazoume sto map
		map->setPositions(getX(), getY(), getID());

		// Stelnoume tin mpala ekei
		ball->setX(getTargetCol());
		ball->setY(randomCol);

		// Elexnoume an i thesi pou tha paei i mpala einai eleftheri
		if (map->isEmpty(ball->getX(), ball->getY()))
		{
			cout << "Eleftheri thesi" << endl;

			// Vazoume tin mpala stin nea tis thesi sto xarti
			map->setPositions(ball->getX(), ball->getY(), "***");

			// Thetoume tin mpala eleftheri
			ball->setPreviousPlayer(this);
			ball->setCurrentPlayer(NULL);
		}
		else
		{
			// Vriskoume poios paixtis einai idi ekei
			string s = map->getMapContent(ball->getX(), ball->getY());
			//setID(s.substr(0, 1) + s.substr(1, 1) + "-");

			// Theloume na allaksoume to id ekeinou tou paixti pou einai se ekeini tin thesi
			Player *p = getPlayer(ball->getX(), ball->getY());
			p->setID(s.substr(0, 1) + s.substr(1, 1) + "*");

			// To apeikonizoume ston xarti
			map->setPositions(p->getX(), p->getY(), p->getID());
		}

		cout << "Edwse pasa stis : " << ball->getX() << "," << ball->getY() << endl;
		*/
	}

	/*
	// elenxoume to onoma an einai aftos pou exei tin mpala
	if (p->getName().compare(getName()) == 0)
	{
		cout << "Exei tin mpala o:"<< p->getName() << endl;
		// tote exei aftos tin mpala
		// tin stelnoume se mia tuxaia stili tis grammisStoxou
		// dialekse tixaia enan arithmo 0 - 5
		int randomCol = rand() % 6;
		// allazw ta stats tis mpalas
		// tin vazw stin grammiStoxo
		ball->setX(getTargetCol());

		// kai epeita stin tixai stili
		ball->setY(randomCol);

		string str1 = map->getMapContent(p->getX(), p->getY());
		p->setID(str1.substr(0, 1) + str1.substr(1, 1) + "-");
		map->setPositions(p->getX(), p->getY(), p->getID());

		// elenxoume an einai adeios o xartis
		if (map->isEmpty(ball->getX(), ball->getY()))
		{
			map->setPositions(ball->getX(), ball->getY(), "***");
			ball->setCurrentPlayer(NULL);
		}

		// sxolia
		else
		{
			string str1 = map->getMapContent(ball->getX(), ball->getY());
			string s = str1.substr(0, 1) + str1.substr(1, 1) + "*";
			map->setPositions(ball->getX(), ball->getY(), s);
		}

		cout << "Edwse pasa stis : " << ball->getX() << "," << ball->getY() << endl;
	}
	*/
	
}

void Player::printPlayerInfo()
{
	cout << getName() << "\t" << getPlayerNum() << "\t" << getTargetCol()
		 << "\t" << getMoveCol() << "\t" << getID() << endl;
}

Player *Player::getPlayer(int x, int y)
{
	Team *redTeam = game->getTeam("red");
	Team *blueTeam = game->getTeam("blue");
	vector<Player *> redPlayers = redTeam->getPlayersVector();
	vector<Player *> bluePlayers = blueTeam->getPlayersVector();

	for (int i = 0; i < redPlayers.size(); i++)
	{
		if (redPlayers[i]->getX() == x && redPlayers[i]->getY() == y)
		{
			return redPlayers[i];
		}
		else if (bluePlayers[i]->getX() == x && bluePlayers[i]->getY() == y)
		{
			return bluePlayers[i];
		}
	}
	
	return NULL;
}

bool Player::hasBall()
{
	// Elenxoume an o paixtis exei tin mpala
	Ball *ball = game->getBall();

	if (getX() == ball->getX() && getY() == ball->getY())
		return true;

	return false;
}

// setters
void Player::setX(int x) { this->x = x; }
void Player::setY(int y) { this->y = y; }
void Player::setPlayerNum(int pNum) { this->playerNum = pNum; }
void Player::setTargetCol(int tCol) { this->targetCol = tCol; }
void Player::setMoveCol(int mCol) { this->moveCol = mCol; }
void Player::setName(string name) { this->name = name; }
void Player::setID(string id) { this->id = id; }


// getters
int Player::getX() { return x; }
int Player::getY() { return y; }
int Player::getPlayerNum() { return playerNum; }
int Player::getTargetCol() { return targetCol; }
int Player::getMoveCol() { return moveCol; }
string Player::getName() { return name; }
string Player::getID() { return id; }
Game *Player::getGameInstance() { return game; }
