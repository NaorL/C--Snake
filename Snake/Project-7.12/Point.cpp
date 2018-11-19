#include "Point.h"

//this function changes the direction of a point
void Point::move(Direction dir)
{
	switch (dir)
	{
	case LEFT:
		m_dir_x = -1; m_dir_y = 0;
		break;
	case RIGHT:
		m_dir_x = 1; m_dir_y = 0;
		break;
	case UP:
		m_dir_x = 0; m_dir_y = -1;
		break;
	case DOWN:
		m_dir_x = 0; m_dir_y = 1;
		break;

	default:
		break;
	}
}

//this function changes direction of tail point to other side;
void Point::changeDirectionTailXY()
{
	m_dir_x = m_dir_x*(-1);
	m_dir_y = m_dir_y*(-1);
}

