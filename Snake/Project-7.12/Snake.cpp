#include "Snake.h"
#include "Board.h"
#include <windows.h>

//ctor
Snake::Snake(Point&& head, char c1, Direction dir)
{
	Point p;
	//get char for snake
	m_c = c1;
	direction = dir;
	head.move(dir);
	//initialized the head of the snake
	body.push_back(head);
	//check if is the left snake or the right snake
	p = head;
	if (head.getX() == 70)
	{
		for (int i = 1; i < 3; ++i)
		{
			p.setDirX(head.getDirX());
			p.setX(p.getX() + 1);
			body.push_back(p);
		}
	}
	else
	{
		for (int i = 1; i < 3; ++i)
		{
			p.setDirX(head.getDirX());
			p.setX(p.getX() - 1);
			body.push_back(p);
		}
		
	}
}

//this function moves snake
Point Snake::move(char key, Snake& otherSnake, Board & board)
{

	//set p as copy of the head
	Point p = body.at(0);

	//make sure to update snake member data direction
	changeDirection(key);

	//update p data members m_dir_x , m_dir_y
	p.move(direction);

	//implement the changes on m_x & m_y the p's data members
	p.changeXY();
    
	//entering only when there is not a snake in the next move we want to make
	//when entering, we actually update the head of the snake
	//in case we cant move towards the direction, we just return the current head value
	if (thereIsSnakeThere(p, otherSnake) == false && disappearAfterHitByBullet == 0) //&& thereIsNumberThere() == false
	{
		//put space instead of the tail on the board
		body.at(body.size() - 1).draw(' ');

		//set the arrary and make room at the head for new point
		for (size_t i = body.size() - 1;i > 0;--i)
		{
			if (i == body.size() - 1)
				board.setBoard(body.at(i), ' ');
			else
				board.setBoard(body.at(i), m_c);
			body.at(i) = body.at(i - 1);
		}
		
		body.at(0).move(direction);

		//update x,y by the direction inserted
		body.at(0).changeXY();
		if (board.isPointABullet(body.at(0).getX(), body.at(0).getY()) == false && board.isPointAFlyer({ body.at(0).getX(), body.at(0).getY() } ) == false)
			body.at(0).draw(m_c);
	}
	return body.at(0);
}

//this function change the direction of snake
void Snake::changeDirection(char key)
{
	for (int i = 0;i < 4;i++)
	{
		if (key == keyArr[i])
			direction = (Direction)i;
	}
}

bool Snake::thereIsSnakeThere(const Point& p,Snake& otherSnake)
{
	for (int i = 0; i < body.size();++i)
		if ((p.getX() == body.at(i).getX() && p.getY() == body.at(i).getY()))
			return true;

	for (int i = 0; i < otherSnake.getSnake().size();++i)
		if (p.getX() == otherSnake.getSnake().at(i).getX() && p.getY() == otherSnake.getSnake().at(i).getY()&& otherSnake.getDisappearAfterHitByBullet()==0)
			return true;
	
	
	return false;
}

void Snake::setKeys(char left, char up, char right, char down)
{
	keyArr[0] = left;
	keyArr[1] = up;
	keyArr[2] = right;
	keyArr[3] = down;
}

void Snake::setNumOfBullets(Board & board)
{
	Point p1, p2;
    ++numOfBullets;
	board.SetPointOfBullets(p1, p2);
	if (m_c == '@')
	{
		p1.draw(numOfBullets);
		board.setBoard(p1, numOfBullets);
	}
	else
	{
		p2.draw(numOfBullets);
		board.setBoard(p2, numOfBullets);
	}
}

void Snake::manageAnswers(Board & board,const Point & pointOfScore)
{
	Point p;
	//updating score at board and at screen
	++score;
	board.UpdateBoard(board.getNumOfDigits(score), score, pointOfScore);

	//p is the tail of snake
	p.setX(body.at(body.size() - 1).getX());
	p.setY(body.at(body.size() - 1).getY());
	p.setDirX(body.at(body.size() - 1).getDirX());
	p.setDirY(body.at(body.size() - 1).getDirY());

	//make sure that we dont change the point if we got to the edge of board
	//it helps to manage the appearance of a new tail when it should jump the other side of the board
	if (p.getX() != (body.at(body.size() - 2).getX())&& p.getX() != Point::max_x&& p.getX() != Point::min_x)
	{
		if (p.getX() > (body.at(body.size() - 2).getX()))
			p.setX(p.getX() + 1);
		else
			p.setX(p.getX() - 1);
	}
	else if (p.getX() == Point::max_x || p.getX() == Point::min_x)
	{
		p.changeDirectionTailXY();
		p.changeXY();
		p.changeDirectionTailXY();
	}
	
	if (p.getY() != (body.at(body.size() - 2).getY())&& p.getY()!=Point::max_y&&p.getY() != Point::min_y)
	{
		if (p.getY() > (body.at(body.size() - 2).getY()))
			p.setY(p.getY() + 1);
		else
			p.setY(p.getY() - 1);
	}
	else if (p.getY() == Point::max_y||p.getY() == Point::min_y)
	{
		p.changeDirectionTailXY();
		p.changeXY();
		p.changeDirectionTailXY();
	}
	//if the snake didnt disappear
	if (disappearAfterHitByBullet == 0)
	{
		board.setBoard(p, m_c);
		p.draw(m_c);
	}
	
	body.push_back(p);
	
	
}

//this function use in sub-menu option 4.
//its changes the direction to start direction.
//its change the body to start point and keeps his size and score
void Snake::resetDataMembersOfSnake(Board & board)
{
	if (m_c == '@')
		direction = RIGHT;
	else
		direction = LEFT;
	resetBodyForOption4(board);
}

//this function change the body of snake in sub-menu option 4
void Snake::resetBodyForOption4(Board & board)
{
	int index = score + 3,helper,flag=1;
	if (m_c == '@')
		helper = 10;
	else
	{
		helper = 70;
		flag = -1;
	}
	//exetreme case if the score is more than 5 there is a problem in pointing snake from starting point.
	if (index > 8)
	{
		body.at(0).setY(9);
		body.at(0).setX(helper + (index - 8)*flag);
	}
	else
	{
		body.at(0).setY(9);
		body.at(0).setX(helper);
	}
	body.at(0).draw(m_c);
	board.setBoard({ body.at(0).getX(),9 }, m_c);
	body.at(0).move(direction);

	//change all the body
	for(int i=1;i<body.size();++i)
	{
		body.at(i).setY(9);
		body.at(i).setX(body.at(i-1).getX()-1*flag);
		body.at(i).move(direction);
		body.at(i).draw(m_c);
		board.setBoard({ body.at(i).getX() , 9}, m_c);
	}

}

void Snake::shoot(Board & board)
{

	Bullet b;
	Point p1, p2;
	//snake can shoot only if he appear on board
	if (disappearAfterHitByBullet == 0)
	{
		b.setPosition(body.at(0).getX(), body.at(0).getY(), body.at(0).getDirX(), body.at(0).getDirY());
		board.SetPointOfBullets(p1, p2);
		if (numOfBullets > 0)
		{
			--numOfBullets;
			shoots.push_back(b);
		}
		//here we check in which snake we are
		if (numOfBullets >= 0)
		{
			if (m_c == '@')
				board.UpdateBoard(1, numOfBullets, p1);
			else
				board.UpdateBoard(1, numOfBullets, p2);
		}
	}
}

void Snake::deleteSnakeAfterHitBullet(Board & board, Point & previous, const Point & curr, vector<Bullet> &other_bullets,bool flag)
{
	//first we delete snake from board and screen.
	for (int k = 0; k < getSnake().size(); ++k)
	{
		//delete snake from board
		board.setBoard(getSnake().at(k), ' ');
		body.at(k).draw(' ');
	}
	//delete bullet from board
	setDisappearAfterHitByBullet(STARTING_BULLETS);
	//we use whis function in 2 diffrent places, only if flag is true we use this code
	if (flag == true)
	{
		if (board.getCharFromBoard(previous) == '*')
		{
			board.setBoard(previous, ' ');
			previous.draw(' ');
		}
		deleteFromShoots(curr, other_bullets);
	}
}

void Snake::deleteFromShoots(const Point & p, vector<Bullet>& other)
{
	for (int i = 0; i < shoots.size(); ++i)
	{
		if (p.getX() == shoots.at(i).getPosition().getX() && p.getY() == shoots.at(i).getPosition().getY())
		{
			shoots.erase(shoots.begin() + i);
			--i;
		}
	}
	for (int i = 0; i < other.size(); ++i)
	{
		if (p.getX() == other.at(i).getPosition().getX() && p.getY() == other.at(i).getPosition().getY())
		{
			other.erase(other.begin() + i);
			--i;
		}
	}
}

bool Snake::isTheBulletMine(const Point & p)
{
	for (int i = 0; i < shoots.size(); ++i)
	{
		if (p.getX() == shoots.at(i).getPosition().getX() && p.getY() == shoots.at(i).getPosition().getY())
			return true;
	}
	return false;
}

void Snake::showSnakeOnBoardAfter5Numbers(Board & board, int& numbersOnBoard)
{
	bool randomIsGood = false,placeIsClear=true;
	int len = body.size(),i=0;
	while (randomIsGood == false)
	{
		int x = rand() % 77 + 1;
		int y = rand() % (24 - 4) + 4;
		if ((x + body.size()-1)<=Point::max_x)
		{
			while (placeIsClear == true && i < body.size())
			{
				if (board.isPointABullet(x + i, y) == true || board.isPointASnake(x+i,y) == true)
					placeIsClear = false;
				i++;
			}
		
			if (placeIsClear == true)
			{
				Point p;
				p.setPoint(x, y, -1, 0);
				showSnake(p, board, numbersOnBoard);
				randomIsGood = true;
			}
		}
	}
}

void Snake::showSnake(Point newHead, Board & board, int & numbersOnBoard)
{
	Point p;
	p.setY(newHead.getY());
	for (int i = 0; i < body.size(); ++i)
	{
		p.setX(newHead.getX() + i);

		//μϊχο
		if (board.isPointANumber(p.getX(), p.getY()) == true)
		{
			--numbersOnBoard;
			board.eraseFronNumbersOnBoard(newHead);
		}
		body.at(i).setPoint(p.getX(), p.getY(), -1, 0);

		board.setBoard(body.at(i), m_c);
		body.at(i).draw(m_c);
	}
	setDirection();
}


