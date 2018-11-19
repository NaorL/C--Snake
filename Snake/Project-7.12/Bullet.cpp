#include "Bullet.h"
#include "Snake.h"
#include "Board.h"

//this function set direction to bullet
void Bullet::changeDirection(int dir_x, int dir_y)
{
	if (dir_x == 1 && dir_y == 0)
		direction = RIGHT;
	else if (dir_x == 0 && dir_y == 1)
		direction = DOWN;
	else if (dir_x == 0 && dir_y == -1)
		direction = UP;
	else
		direction = LEFT;
}
