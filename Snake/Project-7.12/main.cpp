#include <iostream>
#include "Game.h"
#include "Board.h"

using namespace std;

int main()
{
	//if doIRunWithMenu= RUNWITHMENU we run the main menu 
	//if doIRunWithMenu= DONTRUNMENU we dont run the main menu
	int doIRunWithMenu = RUNWITHMENU;

	while (doIRunWithMenu == RUNWITHMENU || doIRunWithMenu == DONTRUNMENU)
	{
		Game g;

		doIRunWithMenu = g.run(doIRunWithMenu);
	}

	return 0;
}