#include "LineEater.h"
#include "Game.h"

void LineEater::move()
{
	for (int k = 0; k < FLYER_STEP; ++k)
	{
		if (getOnBoard() == true)
		{
			Game *game = getGame();
			if ((Point::min_x == getLocation().getX()) && (getDirection() == LEFT) && (getLocation().getY() == 15))
				setDir(RIGHT);
			else if (Point::max_x == getLocation().getX() && (getDirection() == RIGHT) && (getLocation().getY() == 15))
				setDir(LEFT);
			Point temp = getLocation();
			temp.move(getDirection());
			temp.changeXY();
			//in this case its a flyer
			if (game->getBoard().getCharFromBoard(temp) == '$' || game->getBoard().getCharFromBoard(temp) == '%')
			{
				getLocation().draw(' ');
				temp.draw(' ');
				game->getBoard().setBoard(getLocation(), ' ');
				game->getBoard().setBoard(temp, ' ');
				setDataMemberOnBoard(temp, game->getFlyers());
				setOnBoard(false);
			}
			//in this case its a snake or its nothing or its a bullet
			else if (game->getBoard().isPointASnake(temp.getX(), temp.getY()) == true || game->getBoard().getCharFromBoard(temp) == ' ' || game->getBoard().isPointABullet(temp.getX(), temp.getY()) == true)
			{
				if (game->getBoard().isPointASnake(temp.getX(), temp.getY()) == true)
				{
					if (game->getBoard().getCharFromBoard(temp) == '@')
						game->getSnakesArr()[0].deleteSnakeAfterHitBullet(game->getBoard(), getLocation(), temp, game->getSnakesArr()[0].getShoots(), false);
					else
						game->getSnakesArr()[1].deleteSnakeAfterHitBullet(game->getBoard(), getLocation(), temp, game->getSnakesArr()[1].getShoots(), false);
				}
				else if (game->getBoard().isPointABullet(temp.getX(), temp.getY()) == true)//
					game->getSnakesArr()[0].deleteFromShoots(temp, game->getSnakesArr()[1].getShoots());

				getLocation().draw(' ');
				game->getBoard().setBoard(getLocation(), ' ');
				temp.draw('!');
				game->getBoard().setBoard(temp, '!');
				getLocation().setPoint(temp.getX(), temp.getY(), temp.getDirX(), temp.getDirY());
			}
			else if (game->getBoard().isPointANumber(temp.getX(), temp.getY()) == true)
			{
				game->setNumbersOnBoard(-1);
				while (game->getBoard().isPointANumber(temp.getX() - 1, temp.getY()) == true)
					temp.setX(temp.getX() - 1);
				game->getBoard().eraseFronNumbersOnBoard(temp);
				game->getBoard().deleteNumberFromBoard(temp);
			}
		}
	}
}

void LineEater::resetLocationAndDir()
{
	if (getOnBoard() == false)
	{
		if (getLocation().getY() == 23)
		{
			setDir(RIGHT);
			setLocation({ 30,23 });
		}
		else
		{
			setDir(LEFT);
			setLocation({ 50,15 });
		}
	}
}



