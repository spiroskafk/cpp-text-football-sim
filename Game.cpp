#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "Map.h"
#include "Ball.h"
#include "Team.h"
#include "Player.h"




using namespace std;

Game::Game()
{
	// random number generator
	srand((unsigned)time(0));

	// sinartisi arxikopoihshs 
	init();
}

void Game::init()
{
	// init map
	map = new Map();

	// init readTeam
	redTeam = new Team(0, 0, 0, 0, "red", this);
	redPlayers = redTeam->getPlayersVector();

	// init blueTeam
	blueTeam = new Team(0, 0, 0, 0, "blue", this);
	bluePlayers = blueTeam->getPlayersVector();

	// init ball
	ball = new Ball(1, 1, "***", NULL, NULL, this);
	
	// init statistics
	setRounds(15);
	setGoals(7);

	// placeOnMap
	placeOnMap();

	// printMap
	map->printMap();

	cout << "Onoma\tPases\tLathoi\tGoal\tKlepsimata" << endl;
	blueTeam->printTeamInfo();
	cout << endl;
	
	cout << "Onoma\tFanela\tStoxos\tKinisis\tID" << endl;
	for (int i = 0; i < bluePlayers.size(); i++)
	{
		bluePlayers[i]->printPlayerInfo();
	}

	// arxizei i prosomoiwsi
	start();
}

void Game::start()
{
	int roundsPassed = 0;
	int choice = 1;
	int x = ball->getX();
	int y = ball->getY();
	// game loop
	while (roundsPassed < getRounds() && choice == 1)
	{

		do
		{
			// 1. runTurn();
			runTurn();

			// 2. Elenxoume an kapoia omada eftase ta 7 goal
			if (blueTeam->getGoals() == 7)
			{
				cout << "Blue Team Wins!" << endl;
				exit(1);
			}
			else if (redTeam->getGoals() == 7)
			{
				cout << "Red Team Wins!" << endl;
				exit(1);
			}

			// auksanoume tous gurous
			roundsPassed++;

			map->printMap();
			//cout << "Ball coord : " << ball->getX() << ball->getY() << endl;

			cout << "Onoma\tPases\tLathoi\tGoal\tKlepsimata" << endl;
			blueTeam->printTeamInfo();
			redTeam->printTeamInfo();

			if (x == ball->getX() && y == ball->getY())
			{
				if (ball->getCurrentPlayer() == NULL)
				{
					ballRounds++;
				}
			

			}
			else
			{
				 x = ball->getX();
				 y = ball->getY();
				 ballRounds = 0;

			}

			cout << ballRounds << endl;
			cout << "Thes na sunexiseis(Pata 1) : ";
			cin >> choice;
		} while (choice == 1);
	}
}


void Game::runTurn()
{
	// Epelekse tuxaia poia omada tha paiksei prwta
	int randomTeam = 1 + (rand() % 2);

	// 1 - RedTeam
	// 2 - BlueTeam
	if (randomTeam == 1)
	{
		cout << "RedTeam action()" << endl;
		redTeam->action();
		cout << "BlueTeam action()" << endl;
		blueTeam->action();
	}
	else
	{
		cout << "BlueTeam action()" << endl;
		blueTeam->action();
		cout << "RedTeam action()" << endl;
		redTeam->action();
	}

	// Elenxoume an kapoia omada evale goal, alliws kaloume assignBall()
	// prepei na elenksoume an i mpala vriskete dippla se ena apo ta termata
	if ( (ball->getX() == 0 || ball->getX() == 9) && (ball->getY() == 2 || ball->getY() == 3) )
	{
		if (!scored())
			ball->assignBall();
	}


	// Ektipwnoume ton xarti
}

bool Game::scored()
{
	// Elenxoume an evale goal i redTeam
	if ((ball->getX() == 0) && (ball->getY() == 2 || ball->getY() == 3))
	{
		int goalPropability = 1 + (rand() % 100);

		if (goalPropability <= 10)
		{
			redTeam->setGoals(redTeam->getGoals() + 1);
			cout << "Scorare h redTeam" << endl;
			sentra("blue");
			return true;
		}
	}
	else if ((ball->getX() == 9) && (ball->getY() == 2 || ball->getY() == 3))
	{
		int goalPropability = 1 + (rand() % 100);

		if (goalPropability <= 10)
		{
			blueTeam->setGoals(blueTeam->getGoals() + 1);
			cout << "Scorare h blueTeam" << endl;

			// dinoume tuxaia tin mpala se enan paixti tis mple omadas
			sentra("red");


			return true;
		}
	}

	return false;
}

void Game::sentra(string team)
{
	if (team.compare("red") == 0)
	{
		// scorare red
		int rndPlayer = rand() % redPlayers.size();
		int x = redPlayers[rndPlayer]->getX();
		int y = redPlayers[rndPlayer]->getY();

		// svinw tin mpala
		map->setPositions(ball->getX(), ball->getY(), "---");

		ball->setX(x);
		ball->setY(y);

		// Vriskoume poios paixtis einai idi ekei
		string s = map->getMapContent(x, y);

		// Theloume na allaksoume to id ekeinou tou paixti pou einai se ekeini tin thesi
		Player *newPlayer = redPlayers[rndPlayer]->getPlayer(x, y);
		newPlayer->setID(s.substr(0, 1) + s.substr(1, 1) + "*");

		// To apeikonizoume ston xarti
		map->setPositions(newPlayer->getX(), newPlayer->getY(), newPlayer->getID());

		// Orizoume ton neo paixti
		ball->setPreviousPlayer(NULL);
		ball->setCurrentPlayer(newPlayer);
	}
	else
	{
		// scorare blue
		// scorare red
		int rndPlayer = rand() % bluePlayers.size();
		int x = bluePlayers[rndPlayer]->getX();
		int y = bluePlayers[rndPlayer]->getY();

		// svinw tin mpala
		map->setPositions(ball->getX(), ball->getY(), "---");

		ball->setX(x);
		ball->setY(y);

		// Vriskoume poios paixtis einai idi ekei
		string s = map->getMapContent(x, y);

		// Theloume na allaksoume to id ekeinou tou paixti pou einai se ekeini tin thesi
		Player *newPlayer = bluePlayers[rndPlayer]->getPlayer(x, y);
		newPlayer->setID(s.substr(0, 1) + s.substr(1, 1) + "*");

		// To apeikonizoume ston xarti
		map->setPositions(newPlayer->getX(), newPlayer->getY(), newPlayer->getID());

		// Orizoume ton neo paixti
		ball->setPreviousPlayer(NULL);
		ball->setCurrentPlayer(newPlayer);
	}
}


void Game::placeOnMap()
{
	// place redTeam on map
	for (int i = 0; i < redPlayers.size(); i++)
	{
		map->setPositions(redPlayers[i]->getX(), redPlayers[i]->getY(), redPlayers[i]->getID());
	}

	// place blueTeam on map
	for (int i = 0; i < bluePlayers.size(); i++)
	{
		map->setPositions(bluePlayers[i]->getX(), bluePlayers[i]->getY(), bluePlayers[i]->getID());
	}

	// place ball on map
	map->setPositions(ball->getX(), ball->getY(), ball->getID());
}

// setters-getters
void Game::setRounds(int rounds) { this->rounds = rounds; }
void Game::setGoals(int goals) { this->goals = goals; }
int Game::getRounds() { return rounds; }
int Game::getGoals() { return goals; }
Map *Game::getMap() { return map; }
Ball *Game::getBall() { return ball; }

Team *Game::getTeam(string name) 
{
	if (name.compare(redTeam->getName()) == 0)
	{
		// epestrepse tin redTeam
		return redTeam;
	}
	else if (name.compare(blueTeam->getName()) == 0)
	{
		// epestrepse tin blueTeam
		return blueTeam;	
	}
}

void Game::printPlayers()
{
	for (int i = 0; i < redPlayers.size(); i++)
	{
		cout << redPlayers[i]->getName() << endl;
	}

	for (int i = 0; i < bluePlayers.size(); i++)
	{
		cout << bluePlayers[i]->getName() << endl;
	}
}

