#ifndef __POINT_H__
#define __POINT_H__

#include "Gotoxy.h"
#include "Direction.h"
#include <iostream>

using namespace std;

class Point {
private:
	int m_x, m_y;
	int m_dir_x , m_dir_y;
	
public:

	enum { min_x = 1, max_x = 77, min_y = 4, max_y = 23 };

	//ctor
	Point(int x = 0, int y = 0) { m_x = x;  m_y = y; }
	
	//getters
	int getX() const { return m_x; }
	int getY() const { return m_y; }

	int getDirX()const { return m_dir_x; }
	int getDirY()const { return m_dir_y; }
	
	//setters
	void setX(const int& x)  { m_x = x; }
	void setY(const int& y)  { m_y = y; }

	//setters
	void setDirX(const int& dirx) { m_dir_x = dirx; }
	void setDirY(const int& diry) { m_dir_y = diry; }

	//draw character for snake
	void draw(char c)
	{
		gotoxy(m_x, m_y);
		cout << c;
	}

	void draw(int num)
	{
		gotoxy(m_x, m_y);
		cout << num;
	}

	void setPoint(int x, int y, int dirx, int diry)
	{
		m_x = x;
		m_y = y;
		m_dir_x = dirx;
		m_dir_y = diry;
	}

	//update point directions (dir_x, dir_y) according to the key pressed by the player
	void move(Direction dir);

	//update point m_x, m_y values, also calculates new location when reaching edge of the board
	void changeXY()
	{
		if (m_x == min_x && m_dir_x == -1)
			m_x = max_x;
		else if (m_x == max_x && m_dir_x == 1)
			m_x = min_x;
		else if (m_y == min_y && m_dir_y == -1)
			m_y = max_y;
		else if (m_y == max_y && m_dir_y == 1)
			m_y = min_y;
		else
		{
			m_x = m_x + m_dir_x;
			m_y = m_y + m_dir_y;
		}
	}


	void changeDirectionTailXY();

	//opertor - compares two points
	bool operator== (const Point& other)
	{
		if (m_x == other.getX() && m_y == other.getY())
			return true;
		else
			return false;
	}
	
	//operator - perform assignment into a point
	Point& operator=(const Point& other)
	{
			m_x = other.getX();
			m_y = other.getY();
			m_dir_x = other.getDirX();
			m_dir_y = other.getDirY();
			return *this;
	}


};
#endif // !__POINT_H__
