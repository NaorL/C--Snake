#ifndef __BULLET_H__
#define __BULLET_H__

#include "Point.h"
#include <vector>

class Board;
class Snake;
class Bullet {

private:
	Point position;
	//char keyArr='0';
	Direction direction = LEFT;

public:
	void setPosition(int x,int y,int dirx,int diry)
	{
		position.setPoint(x, y, dirx, diry);
	}
	Point getPosition() { return position; }
	void changeDirection(int dir_x, int dir_y);

};
#endif // !__BULLET_H__

