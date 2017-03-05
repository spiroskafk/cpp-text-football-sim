#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>

class Player;
class Game;

using namespace std;

class Team
{
public:
	Team(int, int, int, int, string, Game *);

	void action();
	void initVectorTeam(string);

	// setters
	void setName(string);
	void setPasses(int);
	void setMistakes(int);
	void setGoals(int);
	void setSteals(int);

	void readFile(string);

	// getters
	int getPasses();
	int getMistakes();
	int getGoals();
	int getSteals();
	int chooseAction();      /* epilegoume tixaia mia apo tis 3s kiniseis */
	string getName();
	Game *getGameInstance(); /* Epistrefei deikti se antikeimeno game */
	vector<Player *> getPlayersVector();

	bool isInSameTeam(Player *p1, Player *p2);
	bool isInRedTeam(Player *p);
	bool isInBlueTeam(Player *p);

	vector<string> split(const string &s, char delim);
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

	void printTeamInfo();
private:
	string name;			 /* Onoma omadas */
	int passes;				 /* Passes */
	int mistakes;			 /* Lathoi */
	int goals;				 /* Goal */
	int steals;              /* Klepsimata */
	Game *game;              /* Antikeimeno game */
	vector<Player *> players;/* Vector me tous paiktes */
};
#endif