#ifndef __FATHER_H__
#define __FATHER_H__

#include "Point.h"
#include "Direction.h"
#include "Board.h"
#include "Snake.h"
#include "Mission.h"

//class Game;

class Father {
private:
	Point location;
	char ch;
	Direction dir;
	bool onBoard = true;
	Game * game;

public:
	Father(Point _loc, char _ch, Direction _dir,Game * _game)
	{
		location = _loc;
		ch = _ch;
		dir = _dir;
		game = _game;
	}

	
	virtual void resetLocationAndDir() = 0;
	virtual void move() = 0;
	enum { NOT_INITIALIZED = -1 };
	enum { NUM_OF_FLYERS = 5 };
	enum {FLYER_STEP = 2 };

	//getters
	Point & getLocation() { return location;}
	char getChar() { return ch;}
	Direction & getDirection() { return dir; }
	bool & getOnBoard() { return onBoard; }
	Game * getGame() { return game; }

	//setters
	void setLocation(const Point &p) { location = p;}
	void setChar(char c) { ch = c; }
	void setDir(Direction _dir) { dir = _dir; }
	void setOnBoard(bool status) { onBoard = status; }

	void setDataMemberOnBoard(const Point & temp, Father ** flyers);
	void showFlyer();
};
#endif // !__FATHER_H__
