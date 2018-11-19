#ifndef __COLEATER_H__
#define __COLEATER_H__

#include "Father.h"

class ColEater : public Father {
public:

	ColEater(Point _loc, char _ch, Direction _dir, Game *_game) : Father(_loc, _ch, _dir,_game) {}
	//Snake * snakes, vector <Point> numbersOnBoard, int & numsOnBoard, Board & board, Father ** flyers, Mission & mission, int missionNumber
	void move();
	void resetLocationAndDir();
};
#endif // !__COLEATER_H__
