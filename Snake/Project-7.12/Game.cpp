#include "Game.h"
#include <windows.h>

using namespace std; 

void Game::showInstructions()
{
	string line;
	ifstream instructions("instructions.txt");
	
	if (instructions.is_open())
	{
		while (getline(instructions, line))
		{
			line = line + "\n";
			cout << line;
		}
	}
	else
	{
		cout << "error reading file!!" << endl;
	}
	instructions.close();
}

int Game::run(int doIRunWithMenu)
{
	bool flag = false;
	int choice;
	//Board board;
	if(doIRunWithMenu ==DONTRUNMENU)
		return runGame(board);
	else
	{
		while (flag == false)
		{
			board.mainMenu();
			choice = board.choice();
			switch (choice)
			{
			case 1:
				system("CLS");
				showInstructions();
				Sleep(15000);
				system("CLS");
				break;
			case 2:
				return runGame(board);
				break;
			case 3:
				flag = true;
				cout << "thanks for using the game! goodbye!\n" << endl;
				return 0;
				break;
			default:
				break;
			}
		}
	}
}


int Game::runGame(Board& board)
{
	int counter = 0, group,playerChoice= INITIALCHOOSE,prevPlayerChoice=INITIALCHOOSE;;
	//Mission mission;
	system("CLS");

	//prints board on the screen
	board.displayScreen();
	board.enterIntialSnakeToBoard();
	//Displays snakes on the screen
	for (int i = 0;i <= GAME::SnakesArrSize;++i)
	{
		snakes[0].getSnake().at(i).draw(snakes[0].getSnakeChar());
		snakes[1].getSnake().at(i).draw(snakes[1].getSnakeChar());
	}
	//reading missions
	loadMissionsToMissionVec();
	
	//run and execute all missions
	while(true)
	{
		missionNumber = rand() % 5;
		//show flyers
		showFlyersInStartMission();
		//clear all bullets from board. and set all bulleet snake to 5.
		resetBulletAndBulletOnBoard(board);
		//exetreme case,in this case we initial player choice to 0,and setting the previous mission
		if (playerChoice == FOUR)
			playerChoice = 0;

		//deleting half of the numbers from board and screen
		board.deleteHalfNumbers(numbersOnBoard);
		//prints new mission on the board
		mission.loadNewMission(board, missionNumber);

		//till one player eats a number, or the number of numbers on the board exceed 60
		while (true)
		{
			int player1Number = 0, player2Number = 0;
			bool isPlayer1Right = false, isPlayer2Right = false, isNumberEaten = false;
			
			//using empty ctor
			Point player1Head, player2Head;

			//handle the case when ESC pressed
			char keyPressed = 0;
			if (_kbhit())
			{
				keyPressed = _getch();
				while (true)
				{
					if (keyPressed == ESC|| prevPlayerChoice==SEVEN)
					{
						keyPressed = 0;
						if(prevPlayerChoice != SEVEN)
							playerChoice = board.escMenu();
						prevPlayerChoice = INITIALCHOOSE;
						switch (playerChoice)
						{
						case ONE:
							system("CLS");
							cout << "thanks for using the game! goodbye!" << endl;
							return ENDOFGAME;
						case TWO:
							system("CLS");
							return RUNWITHMENU;
						case THREE:
							system("CLS");
							board.displayScreen();
							break;
						case FOUR:
							board.emptyNumbersOnBoardVector();
							board.cleanNumbersOnBoard();
							for (int i = 0; i < SnakesArrSize; ++i)
								snakes[i].resetDataMembersOfSnake(board);
							board.displayScreen();
							break;
						case FIVE:
							break;
						case SIX:
							return DONTRUNMENU;
						case SEVEN:
							playerChoice = board.escMenu();
							prevPlayerChoice = SEVEN;
							system("CLS");
							break;
						default:
							break;
						}
					}
					else if (keyPressed == 'z' || keyPressed == 'n')
					{
						if (keyPressed == 'z')
							snakes[0].shoot(board);
						else
							snakes[1].shoot(board);
					}
					if (playerChoice != SEVEN&&prevPlayerChoice != SEVEN)
						break;
				}
			}
			Sleep(170);
			
			//in this case we have to break once again and show the screen
			if (playerChoice == FIVE)
			{
				board.displayScreen();
				playerChoice = 0;
				break;
			}
			//move flyers
			moveFlyers();

			//move the bulles of each snake
			moveBullets(board, snakes, numbersOnBoard, flyers);

			//make sure to move the snake according to key pressed and update its location on the screen
			//in case we got a number, we extract it from board array and then insert snake char to board array
			moveSnakes(player1Head, player2Head, keyPressed, board, player1Number, player2Number, isNumberEaten, mission, missionNumber);
			if (checkOfWinner(snakes[0].getScore(),snakes[1].getScore()) == true)
				return ENDOFGAME;
			//check if one of the snake (or both) catch a number, in case it did we update the board status (hence not const)
			// isNumberEaten = getEatenNumbers(player1Number, player2Number, player1Head, player2Head, board, mission, missionNumber);
			++counter;
			//ends the mission once one of the player got a number
			if (isNumberEaten == true)
			{
				//exetreme case in which we have to set counter to 0
				if (counter == NEED_TO_SHOW_NUMBER)
					counter = 0;
				--numbersOnBoard;
				break;
			}
			
			if (countOfShowNum(counter,numbersOnBoard,board)==true)
			{
				if (numbersOnBoard == MAX_NUMBERS_AT_BOARD)
				{
					numbersOnBoard = 0;
					board.flashNumbers(missionNumber);
					Sleep(1000);
					break;
				}
			}
		}
	}
}


void Game::moveSnakes(Point& player1Head, Point& player2Head, char keyPressed, Board & board, int& player1Number, int& player2Number, bool& isNumberEaten, Mission& mission, const int& missionNumber)
{
	bool isOkToUpdateBoardWithSnakeChar = false;
	Point playerHead,playerPrevHead;
	//moving both snakes, make sure to sent the other snake to prevent clashes
	//after we got the next position for the head, we also prints it on the screen
	Point player1PrevHead = snakes[0].getSnake().at(0);
	Point player2PrevHead = snakes[1].getSnake().at(0);
	player1Head = snakes[0].move(keyPressed, snakes[1], board);
	player2Head = snakes[1].move(keyPressed, snakes[0], board);
	

	for (int i = 0;i < GAME::SnakesArrSize;++i)
	{
		//we move the snake only in he appears on board
		if (snakes[i].getDisappearAfterHitByBullet() == 0)
		{
			if (i == 0)
			{
				playerHead = player1Head;
				playerPrevHead = player1PrevHead;
			}
			else
			{
				playerHead = player2Head;
				playerPrevHead = player2PrevHead;
			}

			//after snakes move, we need to check with the board if there is not a number in the new head position
			//if there isn't we update the snake character on board array
			if (board.getCharFromBoard(playerHead) == ' ')
				board.setBoard(playerHead, snakes[i].getSnakeChar());

			//in case we have a number we need to take it before we insert the snake char to board array
			else if (board.isPointANumber(playerHead.getX(), playerHead.getY()) == true && board.isPointASnake(playerHead.getX(), playerHead.getY()) == false)
			{
				getEatenNumbers(player1Number, player2Number, player1Head, player2Head, board, mission, missionNumber);
				isNumberEaten = true;
			}
			else if(board.getCharFromBoard(playerHead)=='*')//its a bullet
			{
				if (snakes[i].isTheBulletMine(playerHead) == true)
					snakes[i].setNumOfBullets(board);
				else
					snakes[(i + 1) % 2].setNumOfBullets(board);
				snakes[i].deleteSnakeAfterHitBullet(board, playerPrevHead, playerHead, snakes[(i + 1) % 2].getShoots(),true);
			}
			else if (board.isPointAFlyer(playerHead) == true)
			{
				if (board.getCharFromBoard(playerPrevHead) == '@')
					snakes[0].deleteSnakeAfterHitBullet(board, player1PrevHead, playerHead, snakes[0].getShoots(), false);
				else
					snakes[1].deleteSnakeAfterHitBullet(board, player2PrevHead, playerHead, snakes[1].getShoots(), false);
				
				for (int k = 0; k < Father::NUM_OF_FLYERS; ++k)
				{
					if (playerHead.getX() == flyers[k]->getLocation().getX() && playerHead.getY() == flyers[k]->getLocation().getY())
					{
						flyers[k]->getLocation().draw(flyers[k]->getChar());
						board.setBoard(flyers[k]->getLocation(), flyers[k]->getChar());
					}
				}
			}
		}
	}
}


//this function gets 2 scores and check if there is winner
//if there is winner its return true and print to screen a messege, else return false.
bool Game::checkOfWinner(int score1, int score2)
{
	//nobody won
	if (score1 != 12 && score2 != 12)
		return false;
	//we decided to print in this point
	system("CLS");
	gotoxy(27, 15);

	if (score1 == 12 && score2 == 12)
		cout << "WellDone To Both Of You-You Both Are The Winners!"<<endl;
	else if (score1 == 12)
		cout << "WellDone Player 1 -You Are The Winner!"<<endl;
	else
		cout << "WellDone Player 2 -You Are The Winner!"<<endl;
	return true;
}

//this function print Number to screen and update in board
//and increases numbersonboard by one
bool Game::countOfShowNum(int & count, int & numbersOnBoard, Board & board)
{
	if (count == NEED_TO_SHOW_NUMBER)
	{
		count = 0;
		board.showNum();
		showSnakesAfter5Numbers(board, numbersOnBoard);
		++numbersOnBoard;
		return true;
	}
	else
		return false;
}

//this function manage eating number. and manage the check of whether the number answers the mission
//its update the board and both snakes by the answers
void Game::getEatenNumbers(int& player1Number, int& player2Number, const Point& player1Head, const Point& player2Head, Board& board, Mission& mission, const int& missionNumber)
{
	bool isPlayer1Right = false, isPlayer2Right = false;
	Point poinToDelete1, poinToDelete2, pointOfScore1, pointOfScore2;
	board.SetPointOfScore(pointOfScore1, pointOfScore2);

	//check if the head met a number, if it did we take it and update the board
	poinToDelete1 = board.getNumberAndUpdateBoard(player1Head, player1Number);
	poinToDelete2 = board.getNumberAndUpdateBoard(player2Head, player2Number);


	//here we take care of the snakes and the missions in case we got a number
	if (player1Number != SNAKE_DIDNT_EAT_NUM || player2Number != SNAKE_DIDNT_EAT_NUM)
	{
		//both of them is right
		if (player1Number != SNAKE_DIDNT_EAT_NUM && player2Number != SNAKE_DIDNT_EAT_NUM)
		{
			//check answers correction
			isPlayer1Right = mission.manageMission(missionNumber, player1Number);
			isPlayer2Right = mission.manageMission(missionNumber, player2Number);
			//if they both got it right
			if (isPlayer1Right == true && isPlayer2Right == true)
			{
				snakes[0].manageAnswers(board, pointOfScore1);
				snakes[1].manageAnswers(board, pointOfScore2);
			}
		}
		else if (player1Number != SNAKE_DIDNT_EAT_NUM)//player 1 is right
		{//if only player 1 is right
			board.eraseFronNumbersOnBoard(poinToDelete1);
			isPlayer1Right = mission.manageMission(missionNumber, player1Number);
			if (isPlayer1Right == true)
				snakes[0].manageAnswers(board, pointOfScore1);
			else
				snakes[1].manageAnswers(board, pointOfScore2);
		}
		else//player 2 is right
		{
			board.eraseFronNumbersOnBoard(poinToDelete2);
			isPlayer2Right = mission.manageMission(missionNumber, player2Number);
			if (isPlayer2Right == true)
				snakes[1].manageAnswers(board, pointOfScore2);
			else
				snakes[0].manageAnswers(board, pointOfScore1);
		}
	}
}

//this function run all the bullets on the screen and make it by 2 step bullet one step snake as demanded.
void Game::moveBullets(Board &board, Snake * snakeArr, int & numbersOnBoard, Father ** flyers)
{
	for (int i = 0; i < SnakesArrSize; ++i)
		for (int j = 0; j < BULLET_STEP; ++j)
			implMoveBullet(board, snakeArr[i], snakeArr[(i + 1) % 2], numbersOnBoard, flyers);
}

//this function move the bullet and handle each different case in which the bullet appear.
void Game::implMoveBullet(Board &board, Snake & snake, Snake& other, int & numbersOnBoard, Father ** flyers)
{
	//here we pass al the bullets of specific snake.
	for (int i = 0; i < snake.getShoots().size(); ++i)
	{
		//previous is the point of bullet before his moving
		Point previous = snake.getShoots().at(i).getPosition();
		snake.getShoots().at(i).changeDirection(snake.getShoots().at(i).getPosition().getDirX(), snake.getShoots().at(i).getPosition().getDirY());
		//we make the move of bullet on p.and make submit to the  bullet.
		Point p = snake.getShoots().at(i).getPosition();
		p.changeXY();
		snake.getShoots().at(i).setPosition(p.getX(),p.getY(),p.getDirX(),p.getDirY());
		//in this case the bullet see a number.he erase the number.and thats it.
		if (board.isPointANumber(snake.getShoots().at(i).getPosition().getX(), snake.getShoots().at(i).getPosition().getY()) == true)
		{
			Point leftPoint = board.deleteNumberFromBoard(snake.getShoots().at(i).getPosition());
			board.eraseFronNumbersOnBoard(leftPoint);
			previous.draw(' ');
			board.setBoard(previous, ' ');
			snake.getShoots().at(i).getPosition().draw('*');
			board.setBoard(snake.getShoots().at(i).getPosition(), '*');
			--numbersOnBoard;
		}
		//in this case the bullet see a snake a delete him for 5 show numbers.
		else if (board.isPointASnake(snake.getShoots().at(i).getPosition().getX(), snake.getShoots().at(i).getPosition().getY()) == true)
		{
			//if bullet hit a snake, its grows the snake shooter bullets by 1.
			if (snake.isTheBulletMine(snake.getShoots().at(i).getPosition()) == true)
				snake.setNumOfBullets(board);
			else
				other.setNumOfBullets(board);
			//in this case we check which snake we should delete.
			if (board.getCharFromBoard(snake.getShoots().at(i).getPosition()) == snake.getSnakeChar())
			{
				snake.deleteSnakeAfterHitBullet(board, previous, snake.getShoots().at(i).getPosition(), other.getShoots(),true);
				//we lower i because we have minus one bullet.
				--i;
			}
			else//here we dont minus i beacuse its the other bullets snake.we dont take care in him right now.
				other.deleteSnakeAfterHitBullet(board, previous, snake.getShoots().at(i).getPosition(), snake.getShoots(), true);
		}
		//in this case we handle when  bullet sees a bullet.both of them disappear.
		else if (board.isPointABullet(snake.getShoots().at(i).getPosition().getX(), snake.getShoots().at(i).getPosition().getY()) == true)
		{
			//we grow our num of bullets for sure
			snake.setNumOfBullets(board);
			//here we check if the second bullet is of the other player
			if (other.isTheBulletMine(other.getShoots().at(i).getPosition()) == true)
				other.setNumOfBullets(board);
			previous.draw(' ');
			board.setBoard(previous, ' ');
			snake.getShoots().at(i).getPosition().draw(' ');
			board.setBoard(snake.getShoots().at(i).getPosition(), ' ');
			int temp = snake.getShoots().size();
			snake.deleteFromShoots(snake.getShoots().at(i).getPosition(), other.getShoots());
			i=i-(temp- snake.getShoots().size());
		}
		else if (board.isPointAFlyer(snake.getShoots().at(i).getPosition()) == true)
		{
			if (board.getCharFromBoard(snake.getShoots().at(i).getPosition()) != '!')//if bullet sees !,then ! dont disappear
			{
				snake.getShoots().at(i).getPosition().draw(' ');
				board.setBoard(snake.getShoots().at(i).getPosition(), ' ');
				snake.setNumOfBullets(board);
			}
			for (int k = 0; k < Father::NUM_OF_FLYERS; ++k)
			{
				if (snake.getShoots().at(i).getPosition().getX() == flyers[k]->getLocation().getX()
					&& snake.getShoots().at(i).getPosition().getY() == flyers[k]->getLocation().getY()
					&& flyers[k]->getChar() != '!')
					flyers[k]->setOnBoard(false);
			}
			
			previous.draw(' ');
			board.setBoard(previous, ' ');
			snake.deleteFromShoots(snake.getShoots().at(i).getPosition(), other.getShoots());
		}
		else//in this case the bullet dont encounter nothing.so we move him by his direction.
		{
			//we check here if the previous point was a bullet.for exetreme case.
			if (board.isPointABullet(previous.getX(),previous.getY()) == true)
			{
				previous.draw(' ');
				board.setBoard(previous, ' ');
			}
			snake.getShoots().at(i).getPosition().draw('*');
			board.setBoard(snake.getShoots().at(i).getPosition(), '*');
		}
	}
}

//this function update snake bullet and delete all bullets in eveery start of mission
void Game::resetBulletAndBulletOnBoard(Board & board)
{
	Point p1, p2;
	for (int i = 0; i < SnakesArrSize; ++i)
	{
		snakes[i].resetNumOfBullet();
		deleteBulletsFromBoard(snakes[i].getShoots(),board);
	}
	board.SetPointOfBullets(p1, p2);
	p1.draw(Snake::STARTING_BULLETS);
	p2.draw(Snake::STARTING_BULLETS);
	board.setBoard(p1, '5');
	board.setBoard(p2, '5');
}

//this function elete all bullets from screen .
void Game::deleteBulletsFromBoard(vector<Bullet> & shoots, Board & board)
{
	for (int i = 0; i < shoots.size(); ++i)
	{
		board.setBoard(shoots.at(i).getPosition(), ' ');
		shoots.at(i).getPosition().draw(' ');
		shoots.erase(shoots.begin() + i);
		--i;
	}
}

//this function rand the place to show snake after hit by bullet.
void Game::showSnakesAfter5Numbers(Board & board,int & numbersOnBoard)
{
	//it passes every snake
	for (int i = 0; i < SnakesArrSize; ++i)
	{
		//we ask here if the snake not appear in screeen
		if (snakes[i].getDisappearAfterHitByBullet() != 0)
		{
			snakes[i].setDisappearAfterHitByBullet(snakes[i].getDisappearAfterHitByBullet() - 1);
			//we ask here if the snake appear in screeen
			if (snakes[i].getDisappearAfterHitByBullet() == 0)
				snakes[i].showSnakeOnBoardAfter5Numbers(board, numbersOnBoard);

		}
	}
}

void Game::showFlyersInStartMission()
{

	for (int i = 0; i < Father::NUM_OF_FLYERS; ++i)
	{
		flyers[i]->resetLocationAndDir();
		flyers[i]->setOnBoard(true);
		flyers[i]->showFlyer();
	}
}

void Game::moveFlyers()
{
	for (int i = 0; i < Father::NUM_OF_FLYERS; ++i)
	{
		flyers[i]->move();
		Sleep(29);
	}
}

void Game::loadMissionsToMissionVec()
{
	string line;
	ifstream f("missions.txt");

	if (f.is_open())
	{
		while (getline(f, line))
			missions.push_back(line);
	}
	else
	{
		cout << "error reading file!!" << endl;
	}
	f.close();
}



