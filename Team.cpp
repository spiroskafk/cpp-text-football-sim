#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include <sstream>
#include <algorithm>
#include <iterator>

#include "Team.h"
#include "Player.h"
#include "Defender.h"
#include "Striker.h"
#include "Game.h"
#include "Ball.h"
#include "Map.h"

using namespace std;

Team::Team(int passes, int mistakes, int goals, int steals, string name, Game *game)
{
	setPasses(passes);
	setMistakes(mistakes);
	setGoals(goals);
	setName(name);
	setSteals(steals);
	this->game = game;

	//initVectorTeam(name);
	readFile(name);
}

void Team::action()
{
	Ball *ball = game->getBall();
	Map *map = game->getMap();

	for (int i = 0; i < players.size(); i++)
	{
		// Ekteloume tis energeies tou kathe paixti
		int move = chooseAction();

		switch (move) {

		case 1:
			cout << players[i]->getPlayerNum() << " -> " << "move()" << endl;

			// Kinisi - move()
			players[i]->move();

			// Kaloume assignBall gia na doume an mporei o paixtis na parei tin mpala
			ball->assignBall(players[i]);

			//cout << "Ball coord : " << ball->getX() << ball->getY() << endl;

			// Ektipwnoume ton xarti
			//map->printMap();

			break;
		case 2:
			cout << players[i]->getPlayerNum() << " -> " << "transfer()" << endl;

			// Metavivasi - transfer()
			players[i]->transfer();

			// Kaloume assignBall
			ball->assignBall(players[i]);

			//cout << "Ball coord : " << ball->getX() << ball->getY() << endl;

			// Ektipwnoume ton xarti
			//map->printMap();
			break;

		case 3:
			cout << players[i]->getPlayerNum() << " -> " << "specialMove()" << endl;

			// Eidiki kinisis - specialMove()
			players[i]->specialMove();

			// Kaloume assignBall
			ball->assignBall(players[i]);

			//cout << "Ball coord : " << ball->getX() << ball->getY() << endl;

			//map->printMap();

			break;
		}
	}
}

void Team::initVectorTeam(string name)
{
	if (name.compare("red") == 0)
	{
		string i = "R";
		Defender *def1 = new Defender(6, 0, 3, 1, 6, "pipis1", game, false);
		def1->setID(i + "3-");
		Defender *def2 = new Defender(7, 3, 4, 2, 7, "talak2", game, false);
		def2->setID(i + "4-");

		Defender *def3 = new Defender(8, 2, 5, 6, 8, "talak12", game, false);
		def3->setID(i + "5-");

		Striker *str1 = new Striker(1, 2, 1, 0, 1,  "pipen3", game);
		str1->setID(i + "1-");
		Striker *str2 = new Striker(2, 3, 2, 0, 2, "talaken4", game);
		str2->setID(i + "2-");

		players.push_back(def1);
		players.push_back(def2);
		players.push_back(def3);
		players.push_back(str1);
		players.push_back(str2);
		

	}
	else if (name.compare("blue") == 0)
	{
		string i = "B";
		Defender *def1 = new Defender(1, 3, 1, 3, 1, "pipis6", game, false);
		def1->setID(i + "1-");
		Defender *def2 = new Defender(2, 2, 2, 7, 2, "talak6", game, false);
		def2->setID(i + "2-");

		Defender *def3 = new Defender(3, 0, 3, 8, 3, "talak31", game, false);
		def3->setID(i + "3-");

		Striker *str1 = new Striker(7, 2, 4, 9, 7, "pipen7", game);
		str1->setID(i + "4-");
		Striker *str2 = new Striker(8, 3, 5, 9, 8, "taen8", game);
		str2->setID(i + "5-");

		players.push_back(def1);
		players.push_back(def2);
		players.push_back(def3);
		players.push_back(str1);
		players.push_back(str2);

	}

}

int Team::chooseAction()
{
	int randomMove = 1 + rand() % 100;

	if (randomMove <= 35)
	{
		// move()
		return 1;
	}
	else if (randomMove <= 70)
	{
		// transfer()
		return 2;
	}
	else
	{
		// specialMove()
		return 3;
	}
}

bool Team::isInSameTeam(Player *p1, Player *p2)
{
	int counter = 0;

	if (p1 == NULL || p2 == NULL)
		return false;

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->getName().compare(p1->getName()) == 0) counter++;
		if (players[i]->getName().compare(p2->getName()) == 0) counter++;
	}

	// Elenxoume an vrikame kai tous 2 stin idia omada
	if (counter == 2) 
		return true;
	else 
		return false;

}

bool Team::isInRedTeam(Player *p)
{
	if (p == NULL) return false;
	for (int i = 0; i < players.size(); i++)
		if (players[i]->getName() == p->getName())
			return true;
	return false;
}

bool Team::isInBlueTeam(Player *p)
{
	if (p == NULL) return false;
	for (int i = 0; i < players.size(); i++)
		if (players[i]->getName() == p->getName())
			return true;
	return false;
}

Game *Team::getGameInstance()
{
	return game;
}

void Team::printTeamInfo()
{
	cout << getName() << "\t" << getPasses() << "\t" << getMistakes() << "\t"
		<< getGoals() << "\t" << getSteals() << endl;
}


vector<Player *> Team::getPlayersVector() { return players; }

void Team::setName(string name) { this->name = name; }
void Team::setPasses(int passes) { this->passes = passes; }
void Team::setMistakes(int mistakes) { this->mistakes = mistakes; }
void Team::setGoals(int goals) { this->goals = goals; }
void Team::setSteals(int steals) { this->steals = steals; }

string Team::getName() { return name; }
int Team::getPasses() { return passes; }
int Team::getMistakes() { return mistakes; }
int Team::getGoals() { return goals;  }
int Team::getSteals() { return steals; }


void Team::readFile(string teamName)
{
	string line;
	ifstream myfile("file.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			// diavazoume tin grammi
			// apothikeuoume se vector
			vector<string> v = split(line, ',');
			if (teamName.compare("red") == 0)
			{
				if (v.at(0).compare("red") == 0)
				{
					if (v.at(1).compare("defender") == 0)
					{
						bool b = (v.at(8).compare("false") == 0) ? false : true;
						Defender *def = new Defender(
							atoi(v.at(2).c_str()), 
							atoi(v.at(3).c_str()),
							atoi(v.at(4).c_str()),
							atoi(v.at(5).c_str()),
							atoi(v.at(6).c_str()),
							v.at(7),
							b,
							game);
						def->setID("R" + v.at(4) + "-");
						players.push_back(def);
					}
					else if	(v.at(1).compare("striker") == 0)
					{
						Striker *str = new Striker(
							atoi(v.at(2).c_str()),
							atoi(v.at(3).c_str()),
							atoi(v.at(4).c_str()),
							atoi(v.at(5).c_str()),
							atoi(v.at(6).c_str()),
							v.at(7),
							game);
						str->setID("R" + v.at(4) + "-");
						players.push_back(str);
					}
				}
			}
			else if (teamName.compare("blue") == 0)
			{
				if (v.at(0).compare("blue") == 0)
				{
					if (v.at(1).compare("defender") == 0)
					{
						bool b = (v.at(8).compare("false") == 0) ? false : true;
						Defender *def = new Defender(
							atoi(v.at(2).c_str()),
							atoi(v.at(3).c_str()),
							atoi(v.at(4).c_str()),
							atoi(v.at(5).c_str()),
							atoi(v.at(6).c_str()),
							v.at(7),
							b,
							game);
						def->setID("B" + v.at(4) + "-");
						players.push_back(def);
					}
					else if (v.at(1).compare("striker") == 0)
					{
						Striker *str = new Striker(
							atoi(v.at(2).c_str()),
							atoi(v.at(3).c_str()),
							atoi(v.at(4).c_str()),
							atoi(v.at(5).c_str()),
							atoi(v.at(6).c_str()),
							v.at(7),
							game);
						str->setID("B" + v.at(4) + "-");
						players.push_back(str);
					}
				}
			}

		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

vector<string> Team::split(const string &s, char delim) 
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

vector<string> &Team::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}