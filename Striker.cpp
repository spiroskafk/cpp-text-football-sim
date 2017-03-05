#include "Striker.h"
#include "Player.h"
#include "Ball.h"
#include "Team.h"
#include "Game.h"
#include "Map.h"

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>

Striker::Striker(int x, int y, int pNum, int tCol, int mCol, string name, Game *game) 
	: Player(x, y, pNum, tCol, mCol, name, game)
{
}

void Striker::transfer()
{
	Game *game = getGameInstance();
	Ball *ball = game->getBall();
	Map *map = game->getMap();

	// elenxoume an exei ti mpala
	if (!hasBall()) return;

	// me pithanotita 70% tha steilei tin mpala stis 2 kentrikes stiles(2-3)
	int p = 1 + rand() % 100;

	if (p <= 70)
	{
		// epilegoume 50-50 tin 2 h tin 3ti stili
		int q = 1 + rand() % 100;
		if (q <= 50)
		{
			// 2i stili
			ball->changeBall(getTargetCol(), 2);
		}
		else
		{
			// 3ti stili
			ball->changeBall(getTargetCol(), 3);
		}

		// allaksoume tin katoxi tis mpalas
		//ball->setPreviousPlayer(this);
		//ball->setCurrentPlayer(NULL);
	}
	else
	{
		// epilegoume tixaia mia apo tis stiles 0,1,4,5
		int q = 1 + rand() % 100;
		
		if (q <= 25)
		{
			// epilegoume 0
			ball->changeBall(getTargetCol(), 0);

		}
		else if (q <= 50)
		{
			// epilegoume 1
			ball->changeBall(getTargetCol(), 1);

		}
		else if (q <= 75)
		{
			// epilegoume 4
			ball->changeBall(getTargetCol(), 4);

		}
		else
		{
			// epilegoume 5
			ball->changeBall(getTargetCol(), 5);
			
		}

		// allaksoume tin katoxi tis mpalas
		//ball->setPreviousPlayer(this);
		//ball->setCurrentPlayer(NULL);
	}
	
}

void Striker::specialMove()
{
	Game *game = getGameInstance();
	Ball *ball = game->getBall();
	Team *redTeam = game->getTeam("red");
	Team *blueTeam = game->getTeam("blue");
	vector<Player*> redPlayers = redTeam->getPlayersVector();
	vector<Player*> bluePlayers = blueTeam->getPlayersVector();
	vector<Player *> nearest1, nearest2, nearest3;
	Map *map = game->getMap();


	bool redFlag = false, blueFlag = false;

	// Elenxw an exw idi tin mpala
	if (hasBall()) return;

	// elenxoume an exei tin mpala simpaiktis mas

	// elenxoume an anikoume se red h blue
	if (redTeam->isInRedTeam(this))
	{
		// anoikoume se kokkini
		for (int i = 0; i < redPlayers.size(); i++)
		{
			if (redPlayers[i]->getX() == ball->getX() && redPlayers[i]->getY() == ball->getY())
			{
				// metakinithoume 2 theseis makria apo ton kontinotero antipalo mas
				// vriskoume ton kontinotero antipalo(ble omada)
				for (int j = 0; j < bluePlayers.size(); j++)
				{
					// psaxnoume antipalo stin idia grammi
					if (bluePlayers[j]->getX() == getX())
					{
						if (abs(bluePlayers[j]->getY() - getY()) == 1)
						{
							nearest1.push_back(bluePlayers[j]);
							redFlag = true;
						}
						else if (abs(bluePlayers[j]->getY() - getY()) == 2)
						{
							nearest2.push_back(bluePlayers[j]);
							redFlag = true;
						}
						else if (abs(bluePlayers[j]->getY() - getY()) == 3)
						{
							nearest3.push_back(bluePlayers[j]);
							redFlag = true;
						}
					}
				}
			}

			if (redFlag)
			{
				// exoume vrei tous antipalous pou einai stin idia grammi me mas
				// kai exoun apostasi 1,2,3

				// 1. an uparxei 1 me apostasi 1,2,3

				// Apostasi 1
				if (nearest1.size() == 1)
				{
					if ( (getY() > nearest1.at(0)->getY()) && (getY() + 2 <= 5) )
					{
						// metakinise ton paixti 2 theseis deksia
						// svinoume palia thesi
						map->setPositions(getX(), getY(), "---");
						setY(getY() + 2);
						map->setPositions(getX(), getY(), getID());
						
					}
					else if ((getY() < nearest1.at(0)->getY()) && (getY() - 2 >= 0))
					{
						// metakinise ton paixti 2 theseis aristera
						map->setPositions(getX(), getY(), "---");
						setY(getY() - 2);
						map->setPositions(getX(), getY(), getID());
					}
				}
				else if (nearest2.size() == 1)
				{
					if ((getY() > nearest2.at(0)->getY()) && (getY() + 2 <= 5))
					{
						// metakinise ton paixti 2 theseis deksia
						map->setPositions(getX(), getY(), "---");
						setY(getY() + 2);
						map->setPositions(getX(), getY(), getID());
					}
					else if ((getY() < nearest2.at(0)->getY()) && (getY() - 2 >= 0))
					{
						// metakinise ton paixti 2 theseis aristera
						map->setPositions(getX(), getY(), "---");
						setY(getY() - 2);
						map->setPositions(getX(), getY(), getID());
					}
				}
				else if (nearest3.size() == 1)
				{
					if ((getY() > nearest3.at(0)->getY()) && (getY() + 2 <= 5))
					{
						// metakinise ton paixti 2 theseis deksia
						map->setPositions(getX(), getY(), "---");
						setY(getY() + 2);
						map->setPositions(getX(), getY(), getID());
					}
					else if ((getY() < nearest3.at(0)->getY()) && (getY() - 2 >= 0))
					{
						// metakinise ton paixti 2 theseis aristera
						map->setPositions(getX(), getY(), "---");
						setY(getY() - 2);
						map->setPositions(getX(), getY(), getID());
					}
				}
			}
		}
	}
	else if (blueTeam->isInBlueTeam(this))
	{
		// anoikoume se blue
		// anoikoume se kokkini
		for (int i = 0; i < bluePlayers.size(); i++)
		{
			if (bluePlayers[i]->getX() == ball->getX() && bluePlayers[i]->getY() == ball->getY())
			{
				// metakinithoume 2 theseis makria apo ton kontinotero antipalo mas
				// vriskoume ton kontinotero antipalo(ble omada)
				for (int j = 0; j < redPlayers.size(); j++)
				{
					// psaxnoume antipalo stin idia grammi
					if (redPlayers[j]->getX() == getX())
					{
						if (abs(redPlayers[j]->getY() - getY()) == 1)
						{
							nearest1.push_back(redPlayers[j]);
							blueFlag = true;
						}
						else if (abs(redPlayers[j]->getY() - getY()) == 2)
						{
							nearest2.push_back(redPlayers[j]);
							blueFlag = true;
						}
						else if (abs(redPlayers[j]->getY() - getY()) == 3)
						{
							nearest3.push_back(redPlayers[j]);
							blueFlag = true;
						}
					}
				}

			}
		}

		if (blueFlag)
		{
			// exoume vrei tous antipalous pou einai stin idia grammi me mas
			// kai exoun apostasi 1,2,3

			// 1. an uparxei 1 me apostasi 1,2,3

			// Apostasi 1
			if (nearest1.size() == 1)
			{
				if ((getY() > nearest1.at(0)->getY()) && (getY() + 2 <= 5))
				{
					// metakinise ton paixti 2 theseis deksia
					map->setPositions(getX(), getY(), "---");
					setY(getY() + 2);
					map->setPositions(getX(), getY(), getID());
				}
				else if ((getY() < nearest1.at(0)->getY()) && (getY() - 2 >= 0))
				{
					// metakinise ton paixti 2 theseis aristera
					map->setPositions(getX(), getY(), "---");
					setY(getY() - 2);
					map->setPositions(getX(), getY(), getID());
				}
			}
			else if (nearest2.size() == 1)
			{
				if ((getY() > nearest2.at(0)->getY()) && (getY() + 2 <= 5))
				{
					// metakinise ton paixti 2 theseis deksia
					map->setPositions(getX(), getY(), "---");
					setY(getY() + 2);
					map->setPositions(getX(), getY(), getID());
				}

				else if ((getY() < nearest2.at(0)->getY()) && (getY() - 2 >= 0))
				{
					// metakinise ton paixti 2 theseis aristera
					map->setPositions(getX(), getY(), "---");
					setY(getY() - 2);
					map->setPositions(getX(), getY(), getID());
				}
			}
			else if (nearest3.size() == 1)
			{
				if ((getY() > nearest3.at(0)->getY()) && (getY() + 2 <= 5))
				{
					// metakinise ton paixti 2 theseis deksia
					map->setPositions(getX(), getY(), "---");
					setY(getY() + 2);
					map->setPositions(getX(), getY(), getID());
				}
				else if ((getY() < nearest3.at(0)->getY()) && (getY() - 2 >= 0))
				{
					// metakinise ton paixti 2 theseis aristera
					map->setPositions(getX(), getY(), "---");
					setY(getY() - 2);
					map->setPositions(getX(), getY(), getID());
				}
			}
		}
	}
	
}