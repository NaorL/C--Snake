#ifndef __SNAKE_H__
#define __SNAKE_H__


#include "Point.h"
#include "Direction.h"
#include "Bullet.h"
#include <vector>

class Board;

using namespace std;

class Snake {

private:
	vector<Point> body;
	Direction direction;
	char m_c;
	int score=0;
	char keyArr[4]; // the keys for the four possible directions
	vector<Bullet> shoots;
	int numOfBullets = 5;
	int disappearAfterHitByBullet = 0;

public:
	enum SNAKE { initSize = 3 };
	enum { STARTING_BULLETS = 5 };
	Snake(Point&& head, char c1, Direction dir = Direction::DOWN);
	void setDirection() { direction = LEFT; }
	void setKeys(char left, char right, char down, char up);
	void setNumOfBullets(Board & board);
	void resetNumOfBullet() { numOfBullets = STARTING_BULLETS; }
	Point move(char key,Snake& otherSnake, Board & board);
	void changeDirection(char key);
	vector<Point> getSnake() { return body; }
	char getSnakeChar() { return m_c; }
	bool thereIsSnakeThere(const Point& p,Snake& otherSnake);
	int getScore() { return score; }
	void manageAnswers(Board & board,const Point & pointOfScore);
	void resetDataMembersOfSnake(Board & board);
	void resetBodyForOption4(Board & board);
	void shoot(Board & board);
	vector<Bullet>& getShoots() { return shoots; }
	void setDisappearAfterHitByBullet(int num) { disappearAfterHitByBullet = num; }
	int getDisappearAfterHitByBullet() { return disappearAfterHitByBullet; }
	void deleteSnakeAfterHitBullet(Board & board, Point & previous, const Point & curr, vector<Bullet> &other_bullets, bool flag);
	void deleteFromShoots(const Point & p, vector<Bullet> & other);
	bool isTheBulletMine(const Point & p);
	void showSnakeOnBoardAfter5Numbers(Board & board, int& numbersOnBoard);
	void showSnake(Point newHead, Board & board, int& numbersOnBoard);
	
};

#endif //__SNAKE_H__