#include "NumEater.h"
#include "Game.h"


void NumEater::move()
{
	for (int k = 0; k < FLYER_STEP; ++k)
	{
		if (getOnBoard() == true)
		{
			Game * game = getGame();
			int helpDirX, helpDirY;
			Point p = searchForCloseNumber(game->getBoard().getNumbersOnBoardVector(), game->getBoard(), game->getMission(), game->getMissionNumber(), helpDirX, helpDirY);
			if (p.getX() != NOT_INITIALIZED&&p.getY() != NOT_INITIALIZED)
			{
				setDirection(p, helpDirX, helpDirY);
				Point temp = getLocation();
				temp.move(getDirection());
				temp.changeXY();
				//in this case its a flyer or a bullet
				if (game->getBoard().getCharFromBoard(temp) == '$' || game->getBoard().getCharFromBoard(temp) == '!'
					|| game->getBoard().isPointABullet(temp.getX(), temp.getY()) == true)
				{
					getLocation().draw(' ');
					temp.draw(' ');
					game->getBoard().setBoard(getLocation(), ' ');
					game->getBoard().setBoard(temp, ' ');
					if (game->getBoard().getCharFromBoard(temp) == '$' || game->getBoard().getCharFromBoard(temp) == '!')
					{
						setDataMemberOnBoard(temp, game->getFlyers());
						setOnBoard(false);
					}
					else
					{
						//we use only on snake 0 but the 2 function work on both snakes
						game->getSnakesArr()[0].deleteFromShoots(temp, game->getSnakesArr()[1].getShoots());
						game->getSnakesArr()[0].setNumOfBullets(game->getBoard());
					}
				}
				//in this case its a snake or its nothing
				else if (game->getBoard().isPointASnake(temp.getX(), temp.getY()) == true || game->getBoard().getCharFromBoard(temp) == ' ')
				{
					if (game->getBoard().isPointASnake(temp.getX(), temp.getY()) == true)
					{
						if (game->getBoard().getCharFromBoard(temp) == '@')
							game->getSnakesArr()[0].deleteSnakeAfterHitBullet(game->getBoard(), getLocation(), temp, game->getSnakesArr()[0].getShoots(), false);
						else
							game->getSnakesArr()[1].deleteSnakeAfterHitBullet(game->getBoard(), getLocation(), temp, game->getSnakesArr()[1].getShoots(), false);
					}

					getLocation().draw(' ');
					game->getBoard().setBoard(getLocation(), ' ');
					temp.draw('%');
					game->getBoard().setBoard(temp, '%');
					getLocation().setPoint(temp.getX(), temp.getY(), temp.getDirX(), temp.getDirY());
				}
				//in this case its a number
				else if (game->getBoard().isPointANumber(temp.getX(), temp.getY()) == true)
				{
					game->setNumbersOnBoard(-1);
					while (game->getBoard().isPointANumber(temp.getX() - 1, temp.getY()) == true)
						temp.setX(temp.getX() - 1);
					game->getBoard().eraseFronNumbersOnBoard(temp);
					game->getBoard().deleteNumberFromBoard(temp);
					getLocation().draw(' ');
					game->getBoard().setBoard(getLocation(), ' ');
					temp.draw('%');
					game->getBoard().setBoard(temp, '%');
					getLocation().setPoint(temp.getX(), temp.getY(), temp.getDirX(), temp.getDirY());
				}
			}
		}
	}
}

Point NumEater::searchForCloseNumber(vector<Point> numbersOnBoard, Board & board, Mission & mission, int missionNumber, int & helpDirX, int & helpDirY)
{
	int num, numOfDigits, numMinSteps = Father::NOT_INITIALIZED;
	Point minSteps(Father::NOT_INITIALIZED, Father::NOT_INITIALIZED);
	for (int i = 0; i < numbersOnBoard.size(); ++i)
	{
		num = board.getNumberFromBoard(numbersOnBoard.at(i));
		if (mission.manageMission(missionNumber, num) == true)
		{
			Point temp = numbersOnBoard.at(i);
			if (getLocation().getX() > temp.getX())//in this case we wanna change temp to the closet digit to flyer
			{
				numOfDigits = board.getNumOfDigits(num);
				if (numOfDigits > 1)
				{
					if (getLocation().getX() == temp.getX() + 1 || numOfDigits == 2)
						temp.setX(temp.getX() + 1);
					else if (numOfDigits > 2)
						temp.setX(temp.getX() + 2);
				}
			}
			if (isPointIsCloser(numMinSteps, temp, helpDirX, helpDirY) == true)
				minSteps = temp;
		}
	}
	return minSteps;
}

bool NumEater::isPointIsCloser(int & numMinSteps, Point & digitOfNumber, int & helpDirX, int & helpDirY)
{
	int y1, y2, x1, x2;
	y1 = abs(getLocation().getY() - digitOfNumber.getY());
	y2 = abs(Point::max_y - y1);
	x1 = abs(getLocation().getX() - digitOfNumber.getX());
	x2 = abs(Point::max_x - x1);

	int lastCheck = changeHelpDir(x1, x2, y1, y2, numMinSteps, helpDirX, helpDirY);
	if (lastCheck < numMinSteps|| numMinSteps==Father::NOT_INITIALIZED)
	{
		numMinSteps = lastCheck;
		return true;
	}
	return false;
}

void NumEater::setDirection(Point & digitOfNumber, int & helpDirX, int & helpDirY)
{
	//only in this case we go up or down
	if (getLocation().getX() == digitOfNumber.getX())
	{
		if (getLocation().getY() > digitOfNumber.getY())//if the flyer is down to number
		{
			if(helpDirY==Y1)
				setDir(UP);
			else
				setDir(DOWN);
		}
		else//if the flyer is up to number
		{
			if (helpDirY == Y1)
				setDir(DOWN);
			else
				setDir(UP);
		}
	}
	else
	{
		if (getLocation().getX() > digitOfNumber.getX())//if the flyer is right to number
		{
			if (helpDirX == X1)
				setDir(LEFT);
			else
				setDir(RIGHT);
		}
		else//if the flyer is left to number
		{
			if (helpDirX == X1)
				setDir(RIGHT);
			else
				setDir(LEFT);
		}
	}
}

int NumEater::changeHelpDir(const int & x1, const int & x2, const int & y1, const int & y2,const int & minSteps, int & helpDirX, int & helpDirY)
{
	int min1 = x1 + y1, min2 = x1 + y2, min3 = x2 + y1, min4 = x2 + y2, res1, res2, finalMin;
	res1 = min(min1, min2);
	res2 = min(min3, min4);
	finalMin = min(res1, res2);
	if (finalMin==min1)
	{
		helpDirX = X1;
		helpDirY = Y1;
	}
	else if (finalMin == min2)
	{
		helpDirX = X1;
		helpDirY = Y2;
	}
	else if(finalMin == min3)
	{
		helpDirX = X2;
		helpDirY = Y1;
	}
	else
	{
		helpDirX = X2;
		helpDirY = Y2;
	}
	return finalMin;

}

void NumEater::resetLocationAndDir()
{
	if (getOnBoard() == false)
	{
		setLocation({ 10,19 });
	}
}
