#include <cmath>
#include <iostream>
#include <string>

#include "Ball.h"
#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "Team.h"

using namespace std;

Ball::Ball(int x, int y, string id, Player *pPlayer, Player *cPlayer, Game *game)
{
	setX(x);
	setY(y);
	setID(id);
	this->game = game;
	setCurrentPlayer(cPlayer);
	setPreviousPlayer(pPlayer);
}

void Ball::assignBall(Player *p)
{
	Map *map = game->getMap();
	// Ean i mpala einai eleftheri kai vriskete se diplani thesi apo ton Player p tin anathetoume se afton

	if (currentPlayer == NULL)
	{
		// Elenxos an vrisketai se diplani thesi apo ton paixti
		if (getX() == p->getX() && (abs(getY() - p->getY()) == 1))
		{
			map->setPositions(getX(), getY(), "---");
			// Allazoume tis sintetagmenes tis mpalas
			//changeBall(p->getX(), p->getY());
			// Allazoume tis sintetagmenes tis mpalas
			setX(p->getX());
			setY(p->getY());

			// Vriskoume poios paixtis einai idi ekei
			string s = map->getMapContent(p->getX(), p->getY());

			// Theloume na allaksoume to id ekeinou tou paixti pou einai se ekeini tin thesi
			//Player *newPlayer = p->getPlayer(getX(), getY());
			p->setID(s.substr(0, 1) + s.substr(1, 1) + "*");

			// To apeikonizoume ston xarti
			map->setPositions(p->getX(), p->getY(), p->getID());
			setCurrentPlayer(p);
			//setPreviousPlayer(NULL);
			cout << p->getPlayerNum() << " -> Anatethike mpala" << endl;
		}

		// Elenxos an vriskontai stin idia omada
		/*
		Team *redTeam = game->getTeam("red");
		Team *blueTeam = game->getTeam("blue");

		if (redTeam->isInSameTeam(getPreviousPlayer(), p))
		{
			redTeam->setPasses(redTeam->getPasses() + 1);
		}
		else if (blueTeam->isInSameTeam(getPreviousPlayer(), p))
		{
			blueTeam->setPasses(blueTeam->getPasses() + 1);
		}
		else
		{
			// Auksanoume ta lathoi tou previousPlayer
			if (redTeam->isInRedTeam(getPreviousPlayer()))
				redTeam->setMistakes(redTeam->getMistakes() + 1);
			else if (blueTeam->isInBlueTeam(getPreviousPlayer()))
				blueTeam->setMistakes(blueTeam->getMistakes() + 1);
		}
		*/

		// Thetoume ton previousPlayer se null
		setPreviousPlayer(NULL);
	}
}

void Ball::assignBall()
{
	// Psaxnoume na vroume ton kontinotero paikti
	Team *redTeam = game->getTeam("red");
	vector<Player *> redPlayers = redTeam->getPlayersVector();
	Team *blueTeam = game->getTeam("blue");
	vector<Player *> bluePlayers = blueTeam->getPlayersVector();
	Map *map = game->getMap();

	int min = 10;
	int playerIndex = -1;

	cout << "assignball()!" << endl;
	// Lista me tous kontinous paixtes
	vector<Player *> nearestPlayers;

	for (int i = 0; i < redPlayers.size(); i++)
	{
		//cout << getX() << redPlayers[i]->getX() << endl;
		cout << redPlayers[i]->getPlayerNum() << endl;
		if (getX() == redPlayers[i]->getX()) {
			cout << "mpika yo" << endl;
			nearestPlayers.push_back(redPlayers[i]);
		}
	}

	for (int i = 0; i < bluePlayers.size(); i++)
	{
		cout << bluePlayers[i]->getPlayerNum() << endl;
		cout << "player x = " << bluePlayers[i]->getX() << endl;
		if (getX() == bluePlayers[i]->getX()) {
			cout << "MPIKA" << endl;
			nearestPlayers.push_back(bluePlayers[i]);
		}
	}

	cout << "SIZE = " << nearestPlayers.size() << endl;
	if (nearestPlayers.size() == 0) return;

	for (int i = 0; i < nearestPlayers.size(); i++)
	{
		cout << nearestPlayers[i]->getY() << endl;
		if (abs(getY() - nearestPlayers[i]->getY()) < min)
		{
			min = abs(getY() - nearestPlayers[i]->getY());
			playerIndex = i;
		}
	}
	cout << "index" << playerIndex << endl;

	string s = map->getMapContent(nearestPlayers[playerIndex]->getX(), nearestPlayers[playerIndex]->getY());

	cout << "s: " << s << endl;
	// Theloume na allaksoume to id ekeinou tou paixti pou einai se ekeini tin thesi
	nearestPlayers[playerIndex]->setID(s.substr(0, 1) + s.substr(1, 1) + "*");

	// To apeikonizoume ston xarti
	map->setPositions(getX(), getY(), "---");
	setX(nearestPlayers[playerIndex]->getX());
	setY(nearestPlayers[playerIndex]->getY());
	map->setPositions(nearestPlayers[playerIndex]->getX(), nearestPlayers[playerIndex]->getY(), nearestPlayers[playerIndex]->getID());

	//if (nearestPlayers.size() == 0) return;
	setCurrentPlayer(nearestPlayers[playerIndex]);
	cout << nearestPlayers[playerIndex]->getPlayerNum() << " -> Anatethike mpala!" << endl;

}

// setters functions
void Ball::setX(int x) { this->x = x; }
void Ball::setID(string id) { this->id = id; }
void Ball::setY(int y) { this->y = y; }
void Ball::setPreviousPlayer(Player *p) { previousPlayer = p; }

void Ball::changeBall(int targetX, int targetY)
{
	Map *map = game->getMap();
	Player *p = getCurrentPlayer();

	
	/*if (p == NULL)
	{
		// Allazoume tis sintetagmenes tis mpalas
		setX(targetX);
		setY(targetY);
		// Vriskoume poios paixtis einai idi ekei
		string s = map->getMapContent(getX(), getY());
		//setID(s.substr(0, 1) + s.substr(1, 1) + "-");

		// Theloume na allaksoume to id ekeinou tou paixti pou einai se ekeini tin thesi
		Player *newPlayer = p->getPlayer(getX(), getY());
		newPlayer->setID(s.substr(0, 1) + s.substr(1, 1) + "*");

		// To apeikonizoume ston xarti
		map->setPositions(newPlayer->getX(), newPlayer->getY(), newPlayer->getID());

		return;
	}*/
	

	// Allazoume to id tou paixti wste na min katexei tin mpala pleon
	string s = map->getMapContent(p->getX(), p->getY());
	p->setID(s.substr(0, 1) + s.substr(1, 1) + "-");

	// to vazoume sto map
	map->setPositions(getX(), getY(), p->getID());

	// Stelnoume tin mpala ekei
	setX(targetX);
	setY(targetY);

	// Elexnoume an i thesi pou tha paei i mpala einai eleftheri
	if (map->isEmpty(getX(), getY()))
	{
		// Vazoume tin mpala stin nea tis thesi sto xarti
		map->setPositions(getX(), getY(), "***");

		// Thetoume tin mpala eleftheri
		setPreviousPlayer(p);
		setCurrentPlayer(NULL);

		// auksise ta lathoi
		Team *redTeam = game->getTeam("red");
		Team *blueTeam = game->getTeam("blue");


		if (!((getX() == 0 || getX() == 9) && (getY() == 2 || getY() == 3)))
		{
			// Auksanoume ta lathoi tou previousPlayer
			if (redTeam->isInRedTeam(getPreviousPlayer()))
				redTeam->setMistakes(redTeam->getMistakes() + 1);
			else if (blueTeam->isInBlueTeam(getPreviousPlayer()))
				blueTeam->setMistakes(blueTeam->getMistakes() + 1);
		}


	}
	else
	{
		// Vriskoume poios paixtis einai idi ekei
		string s = map->getMapContent(getX(), getY());
		//setID(s.substr(0, 1) + s.substr(1, 1) + "-");

		// Theloume na allaksoume to id ekeinou tou paixti pou einai se ekeini tin thesi
		Player *newPlayer = p->getPlayer(getX(), getY());
		newPlayer->setID(s.substr(0, 1) + s.substr(1, 1) + "*");

		// To apeikonizoume ston xarti
		map->setPositions(newPlayer->getX(), newPlayer->getY(), newPlayer->getID());

		// Orizoume ton neo paixti
		setPreviousPlayer(p);
		setCurrentPlayer(newPlayer);

		if (!((getX() == 0 || getX() == 9) && (getY() == 2 || getY() == 3)))
		{
			Team *redTeam = game->getTeam("red");
			Team *blueTeam = game->getTeam("blue");

			if (redTeam->isInSameTeam(getPreviousPlayer(), getCurrentPlayer()))
			{
				redTeam->setPasses(redTeam->getPasses() + 1);
			}
			else if (blueTeam->isInSameTeam(getPreviousPlayer(), getCurrentPlayer()))
			{
				blueTeam->setPasses(blueTeam->getPasses() + 1);
			}
			else
			{
				// Auksanoume ta lathoi tou previousPlayer
				if (redTeam->isInRedTeam(getPreviousPlayer()))
					redTeam->setMistakes(redTeam->getMistakes() + 1);
				else if (blueTeam->isInBlueTeam(getPreviousPlayer()))
					blueTeam->setMistakes(blueTeam->getMistakes() + 1);
			}
		}
	}

}


void Ball::setCurrentPlayer(Player *p)
{ 
	if (p == NULL)
		currentPlayer = NULL;
	else
		currentPlayer = p;
	/*else
	{
		// Svinoume tin palia thesi tis mpalas apo ton xarti (Itan sigoura eleftheri prin?)
		map->setPositions(getX(), getY(), "---");

		// Thetoume tin katoxi tis mpalas se allon paixti
		currentPlayer = p;
		setX(p->getX());
		setY(p->getY());

		// To apeikonizoume ston xarti
		string s = map->getMapContent(p->getX(), p->getY());
		p->setID(s.substr(0, 1) + s.substr(1, 1) + "*");
		map->setPositions(p->getX(), p->getY(), p->getID());

		cout << "H mpala pige ston paixti : " << p->getName() << endl;

		/*cout << "i mpala allakse paikti: " << p->getName() << endl;
		map->setPositions(getX(), getY(), "---");
		currentPlayer = p;
		setX(p->getX());
		setY(p->getY());

		// elenxoume red/blue
		string str1 = map->getMapContent(p->getX(), p->getY());
		p->setID(str1.substr(0, 1) + str1.substr(1, 1) + "*");
		map->setPositions(getX(), getY(), p->getID());
		*/

}

// getters functions
int Ball::getX() const { return x; }
int Ball::getY() const { return y; }
string Ball::getID() { return id; }
Player * Ball::getCurrentPlayer() const { return currentPlayer; }
Player * Ball::getPreviousPlayer() const { return previousPlayer; }