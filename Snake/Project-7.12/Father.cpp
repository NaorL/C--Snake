#include "Father.h"
#include "Game.h"

void Father::setDataMemberOnBoard(const Point & temp, Father ** flyers)
{
	for (int i = 0; i < NUM_OF_FLYERS; ++i)
	{
		if (temp.getX() == flyers[i]->getLocation().getX() && temp.getY() == flyers[i]->getLocation().getY())
			flyers[i]->setOnBoard(false);
	}
}

void Father::showFlyer()
{
	location.draw(ch);
	game->getBoard().setBoard(location, ch);
}
