#ifndef __LINEEATER_H__
#define __LINEEATER_H__

#include "Father.h"

enum { NOT_INITIALIZED = -1 };
enum { NUM_OF_FLYERS = 5 };

class LineEater : public Father{
	
public:
	LineEater(Point _loc, char _ch, Direction _dir, Game *_game) : Father(_loc, _ch, _dir, _game) {}
	//Snake * snakes, vector <Point> numbersOnBoard, int & numsOnBoard, Board & board, Father ** flyers, Mission & mission, int missionNumber
	void move();
	void resetLocationAndDir();
};
#endif // !__LINEEATER_H__
