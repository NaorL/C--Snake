#include "ColEater.h"
#include "Game.h"

void ColEater::move()
{
	if (getOnBoard() == true)
	{
		Game *game = getGame();
		if ((Point::min_y == getLocation().getY()) && (getDirection() == UP) && (getLocation().getX() == 45))
			setDir(DOWN);
		else if (Point::max_y == getLocation().getY() && (getDirection() == DOWN) && (getLocation().getX() == 45))
			setDir(UP);
		Point temp = getLocation();
		temp.move(getDirection());
		temp.changeXY();
		//in this case its a flyer or a bullet
		if (game->getBoard().getCharFromBoard(temp) == '!' || game->getBoard().getCharFromBoard(temp) == '%'
			|| game->getBoard().isPointABullet(temp.getX(), temp.getY()) == true)
		{
			getLocation().draw(' ');
			temp.draw(' ');
			game->getBoard().setBoard(getLocation(), ' ');
			game->getBoard().setBoard(temp, ' ');
			if (game->getBoard().getCharFromBoard(temp) == '!' || game->getBoard().getCharFromBoard(temp) == '%')
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
			temp.draw('$');
			game->getBoard().setBoard(temp, '$');
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

void ColEater::resetLocationAndDir()
{
	if (getOnBoard() == false)
	{
		if (getLocation().getX() == 45)
		{
			setDir(UP);
			setLocation({ 45,23 });
		}
		else
		{
			setDir(DOWN);
			setLocation({ 55,15 });
		}
	}
}
