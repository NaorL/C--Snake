#ifndef __NUMEATER_H__
#define __NUMEATER_H__

#include "Father.h"
class Game;

class NumEater : public Father{

public:
	enum { X1= 1, X2 = 2, Y1 = 3, Y2 = 4};
	NumEater(Point _loc, char _ch, Direction _dir, Game *_game) : Father(_loc, _ch, _dir, _game){}
	//Snake * snakes, vector <Point> numbersOnBoard, int & numsOnBoard, Board & board, Father ** flyers, Mission & mission, int missionNumber
	void move();
	Point searchForCloseNumber(vector <Point> numbersOnBoard, Board & board, Mission & mission, int missionNumber, int & helpDirX, int & helpDirY);
	bool isPointIsCloser(int & numMinSteps, Point & digitOfNumber, int & helpDirX, int & helpDirY);
	void setDirection(Point & digitOfNumber, int & helpDirX, int & helpDirY);
	int changeHelpDir(const int & x1, const int & x2, const int & y1, const int & y2, const int & minSteps, int & helpDirX, int & helpDirY);

	void resetLocationAndDir();

};
#endif // !__NUMEATER_H__
