#include "Defender.h"
#include "Player.h"
#include "Team.h"
#include "Game.h"
#include "Ball.h"
#include "Map.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Defender::Defender(int x, int y, int pNum, int tCol, int mCol, string name, bool yCard, Game * game)
	: Player(x, y, pNum, tCol, mCol, name, game)
{
	setYellowCard(yCard);
}

void Defender::specialMove()
{
	// Elenxos gia to an uparxei antipalos paixtis me tin mpala se diplano tetragono
	Game *game = getGameInstance();
	Team *redTeam = game->getTeam("red");
	Team *blueTeam = game->getTeam("blue");
	Ball *ball = game->getBall();
	Map *map = game->getMap();

	bool blueFlag = false;
	bool redFlag = false;

	// Elenxw an exw idi tin mpala
	if (hasBall()) return;

	// Elenxos an uparxei antipalos konta me tin mpala
	// elenxw pou anikei aftos o paiktis
	if (redTeam->isInRedTeam(this))
	{
		// anoikei stin kokkini
		// ara psaxnoume stous mple paiktes
		// psaxnoume na vroume an uparxei dipla tou mple paiktis me tin mpala
		vector<Player *> bluePlayers = blueTeam->getPlayersVector();
		for (int i = 0; i < bluePlayers.size(); i++)
		{
			// elenxoume an uparxei paiktis aristera
			if (getY() - bluePlayers[i]->getY() == 1 && getX() == bluePlayers[i]->getX() && bluePlayers[i] == ball->getCurrentPlayer())
			{
				blueFlag = true;
			}
			else if (bluePlayers[i]->getY() - getY() == 1 && getX() == bluePlayers[i]->getX() && bluePlayers[i] == ball->getCurrentPlayer())
			{
				blueFlag = true;
			}
			else if (getX() - bluePlayers[i]->getX() == 1 && getX() == bluePlayers[i]->getX() && bluePlayers[i] == ball->getCurrentPlayer())
			{
				blueFlag = true;
			}
			else if (bluePlayers[i]->getX() - getX() == 1 && getX() == bluePlayers[i]->getX() && bluePlayers[i] == ball->getCurrentPlayer())
			{
				blueFlag = true;
			}

			// vrikame telika antipalo paikti me tin mpala
			if (blueFlag)
			{
				
				int p = 1 + rand() % 100;

				if (p <= 70)
				{
					// klepse tin mpala
					cout << "O paixtis " << getPlayerNum() << " eklepse tin mpala" << endl;
					ball->setPreviousPlayer(bluePlayers[i]);
					ball->setCurrentPlayer(this);

					// auksise ta klepsimata kata ena
					redTeam->setSteals(redTeam->getSteals() + 1);
				}
				else
				{
					int kitrini = 1 + rand() % 100;
					
					if (kitrini <= 20)
					{
						// trwei kitrini
						// elenxoume an exei idi kitrini
						if (hasYellowCard())
						{
							// ton dixnoume apo tin prosomoiwsi
							cout << "O paixtis " << getPlayerNum() << " pire kokkini karta" << endl;

							// ton svinoume apo ton xarti
							map->setPositions(getX(), getY(), "---");

							vector<Player *> redPlayers = redTeam->getPlayersVector();

							// ton svinoume apo tin lista
							for (int i = 0; i < redPlayers.size(); i++)
							{
								if (getX() == redPlayers[i]->getX() && getY() == redPlayers[i]->getY())
								{
									redPlayers.erase(redPlayers.begin() + i);
								}
							}

						}
						else
						{
							cout << "O paixtis " << getPlayerNum() << " pire kitrini karta" << endl;
							setYellowCard(true);
						}
					}
				}
			}
		}

	}
	else
	{
		// anoikei stin mple
		// ara psaxnoume stous kokinous paiktes
		// psaxnoume na vroume an uparxei dipla tou kokinos paiktis me tin mpala
		vector<Player *> redPlayers = redTeam->getPlayersVector();
		for (int i = 0; i < redPlayers.size(); i++)
		{
			// elenxoume an uparxei paiktis aristera
			if (getY() - redPlayers[i]->getY() == 1 && getX() == redPlayers[i]->getX() && redPlayers[i] == ball->getCurrentPlayer())
			{
				redFlag = true;
			}
			else if (redPlayers[i]->getY() - getY() == 1 && getX() == redPlayers[i]->getX() && redPlayers[i] == ball->getCurrentPlayer())
			{
				redFlag = true;
			}
			else if (getX() - redPlayers[i]->getX() == 1 && getX() == redPlayers[i]->getX() && redPlayers[i] == ball->getCurrentPlayer())
			{
				redFlag = true;
			}
			else if (redPlayers[i]->getX() - getX() == 1 && getX() == redPlayers[i]->getX() && redPlayers[i] == ball->getCurrentPlayer())
			{
				redFlag = true;
			}

			// vrikame telika antipalo paikti me tin mpala
			if (redFlag)
			{
				int p = 1 + rand() % 100;

				if (p <= 70)
				{
					// klepse tin mpala
					ball->changeBall(getX(), getY());
					//ball->setPreviousPlayer(redPlayers[i]);
					//ball->setCurrentPlayer(this);

					// auksise ta klepsimata kata ena
					blueTeam->setSteals(blueTeam->getSteals() + 1);
					redFlag = true;
				}
				else
				{
					int kitrini = 1 + rand() % 100;

					if (kitrini <= 20)
					{
						// trwei kitrini
						// elenxoume an exei idi kitrini
						if (hasYellowCard())
						{
							// ton dixnoume apo tin prosomoiwsi
							cout << "O paixtis " << getPlayerNum() << " pire kokkini karta" << endl;

							// ton svinoume apo ton xarti
							map->setPositions(getX(), getY(), "---");

							vector<Player *> bluePlayers = blueTeam->getPlayersVector();

							// ton svinoume apo tin lista
							for (int i = 0; i < bluePlayers.size(); i++)
							{
								if (getX() == bluePlayers[i]->getX() && getY() == bluePlayers[i]->getY())
								{
									bluePlayers.erase(bluePlayers.begin() + i);
								}
							}
							redFlag = false;
						}
						else
						{
							cout << "O paixtis " << getPlayerNum() << " pire kitrini karta" << endl;
							setYellowCard(true);
							redFlag = false;
						}
					}
				}
			}
		}
	}
}


void Defender::setYellowCard(bool yCard) { this->yellowCard = yCard; }
bool Defender::hasYellowCard() { return yellowCard; }


