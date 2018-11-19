#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Gotoxy.h"
#include "Board.h"
#include "Snake.h"
#include "Mission.h"
#include "Bullet.h"
#include "Father.h"
#include "ColEater.h"
#include "LineEater.h"
#include "NumEater.h"

using namespace std;


enum GAME { ESC = 27, SnakesArrSize = 2, SNAKE_DIDNT_EAT_NUM = -1 };
enum {ENDOFGAME=0,RUNWITHMENU=1,DONTRUNMENU=2};
enum{INITIALCHOOSE=-1};
enum { MAX_NUMBERS_AT_BOARD = 60 };
enum { NEED_TO_SHOW_NUMBER = 5 };


class Game {
private:

	vector<string> missions;

	Snake snakes[GAME::SnakesArrSize] = {
		{ { 10, 9 }, '@',RIGHT }
		,{ { 70, 9 }, '#',LEFT } 
	};

	vector <char**> replay;

	Board board;
	Mission mission;
	int numbersOnBoard = 0;
	int missionNumber=0;

	Father * flyers[Father::NUM_OF_FLYERS] = { new NumEater{{10,19},'%',RIGHT,this},
		new LineEater{ { 30,23 },'!',RIGHT,this },
		new LineEater{ { 50,15 },'!',LEFT,this },
		new ColEater{ { 45,23 },'$',UP,this },
		new ColEater{ { 55,15 },'$',DOWN,this }
	};


public:
	enum { BULLET_STEP = 2 };

	Game()
	{
		snakes[0].setKeys('a', 'w', 'd', 'x');
		snakes[1].setKeys('j', 'i', 'l', 'm');
	}

	void showInstructions();
	int run(int doIRunWithMenu);
	int runGame(Board& board);
	void getEatenNumbers(int& player1Number, int& player2Number, const Point&player1Head, const Point&player2Head, Board& board, Mission& mission, const int& missionNumber);
	void moveSnakes(Point& player1Head, Point& player2Head, char keyPressed, Board & board, int& player1Number, int& player2Number, bool& isNumberEaten, Mission& mission, const int& missionNumber);
	bool checkOfWinner(int score1, int score2);
	bool countOfShowNum(int & count, int & numbersOnBoard, Board & board);
	void moveBullets(Board &board, Snake * snakeArr, int & numbersOnBoard, Father ** flyers);
	void implMoveBullet(Board &board, Snake & snake, Snake& other, int & numbersOnBoard, Father ** flyers);
	void resetBulletAndBulletOnBoard(Board & board);
	void deleteBulletsFromBoard(vector<Bullet> & shoots, Board & board);
	void showSnakesAfter5Numbers(Board & board, int & numbersOnBoard);
	void showFlyersInStartMission();
	void moveFlyers();
	void loadMissionsToMissionVec();


	//getters
	int & getMissionNumber() { return missionNumber; }
	int & getNumbersOnBoard() { return numbersOnBoard; }
	Mission & getMission() { return mission;}
	Board & getBoard() { return board; }
	Snake * getSnakesArr() { return snakes; }
	Father ** getFlyers() { return flyers; }

	//setters
	void setNumbersOnBoard(int num) { numbersOnBoard = numbersOnBoard + num; }

};


#endif // !__GAME_H__
