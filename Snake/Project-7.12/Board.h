#ifndef __BOARD_H__
#define __BOARD_H__

#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include "Point.h"
#include "Snake.h"
#include "Bullet.h"

enum GROUP { ONE = 1, TWO, THREE,FOUR,FIVE,SIX,SEVEN};
enum ARRAY { MAX_X = 80, MAX_Y = 25 };

class Game;
class Mission;

class Board {
private:

	//array to sotre all numbers on board and its positions
	vector <Point> numbersOnBoard;

	char board[25][80] = {
	//		   10        20        30        40        50        60        70        80
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789012
	 "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",//1
	 "+Mission:                                                                     +",//2
	 "+Score/Bullets player 1: 0  / 5               Score/Bullets player 2: 0  / 5  +",//3
	 "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",//4
	 "+                                                                             +",//5
	 "+                                                                             +",//6
	 "+                                                                             +",//7
	 "+                                                                             +",//8
	 "+                                                                             +",//9
	 "+                                                                             +",//10
	 "+                                                                             +",//11
	 "+                                                                             +",//12
	 "+                                                                             +",//13
	 "+                                                                             +",//14
	 "+                                                                             +",//15
	 "+                                                                             +",//16
	 "+                                                                             +",//17
	 "+                                                                             +",//18
	 "+                                                                             +",//19
	 "+                                                                             +",//20
	 "+                                                                             +",//21
	 "+                                                                             +",//22
	 "+                                                                             +",//23
	 "+                                                                             +",//24
	 "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"//25
	};


public:

	const int SNAKE_DIDNT_EAT_NUM = -1;
	void cleanScreen() { system("CLS"); }
	void displayScreen();
	void mainMenu();
	int choice();
	void showNum();
	int getGroupNumber(GROUP g);
	int getNumOfDigits(int num);
	int randGroup(){ return (rand() % 3 + 1); }
	
	void UpdateBoard(int numDigits, int num, const Point& p);
	Point getNumberAndUpdateBoard(const Point & pos,int & res);
	void storeInNumArr(const Point& newPoint);
	void deleteHalfNumbers(int & numsInBoard);
	void eraseFronNumbersOnBoard(const Point & poinToDelete);
	Point deleteNumberFromBoard(Point p);
	void enterIntialSnakeToBoard();
	void setBoard( const Point& p, char c);
	char getCharFromBoard(const Point& p);
	bool isPointANumber(int x,int y);
	bool checkPositionInBoardArray(const Point& p, int numDigits);
	
	bool isPointASnake(int x, int y);
	bool isPointABullet(int x, int y);
	bool isPointAFlyer(const Point & p);
	int escMenu();
	void SetPointOfScore(Point & pointOfScore1, Point & pointOfScore2);
	void SetPointOfBullets(Point & pointOfScore1, Point & pointOfScore2);
	void cleanNumbersOnBoard();
	void emptyNumbersOnBoardVector();

	int getNumberFromBoard(Point p);
	void flashNumbers(int missioNumber);
	vector <Point> & getNumbersOnBoardVector() { return numbersOnBoard; }

	


};

#endif // !__BOARD_H__
