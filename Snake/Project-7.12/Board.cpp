#include "Board.h"
#include "Game.h"
#include "Mission.h"

using namespace std;
////this function print from file the the main menu
void Board::mainMenu()
{
	int choice;
	string line;
	ifstream snakePic("snakePic.txt");

	if (snakePic.is_open())
	{
		while (getline(snakePic, line))
		{
			line = line + "\n";
			cout << line;
		}
	}
	else
	{
		cout << "error reading file!!" << endl;
	}
	snakePic.close();
}

//this function return the choice of player in main menu
int Board::choice()
{
	int choice;
	cin >> choice;
	return choice;
}

//this function rand number and print him in board and screen
void Board::showNum()
{
	bool isOkay = false;
	//point variable to store the random place we generated
	Point p;
	//rand group from 1-3
	int group = randGroup();
	//rand number from the selected group
	int num = getGroupNumber((GROUP)group);
	//calculates number of digits in num
	int numDigits = getNumOfDigits(num);

	while (isOkay == false)
	{
		//rand point on board
		p.setX(rand() % 79 + 1);
		p.setY(rand() % (24 - 3) + 4);

		isOkay = checkPositionInBoardArray(p, numDigits);
		if (isOkay == true)
		{
			UpdateBoard(numDigits, num, p);
			storeInNumArr(p);
		}
	}
}

//this function update res to SNAKE_DIDNT_EAT_NUM if didnt eat a number
//if eat a number update res to number and the function return the left point of res digits
Point Board::getNumberAndUpdateBoard(const Point& pos, int & res)
{
	Point copy,helper;
	int numDigits = 0, i = 0;
	//copy is the point of left point of res digits. we return him
	copy.setX(pos.getX());
	copy.setY(pos.getY());
	//if we are in a digit from number
	if (isPointANumber(pos.getX(), pos.getY()) == true)
	{
		//we bring copy until the right position of the number in board
		while (isPointANumber(copy.getX() + i, copy.getY()) == true)
			++i;
		//now we set copy to the right position in res
		copy.setX(pos.getX() + (i - 1));
		//we count how many digits in the number in board
		while (isPointANumber(copy.getX() - numDigits, copy.getY()) == true)
			++numDigits;
		//this is the last set of copy.we set him to left position. we return him in the end
		copy.setX((copy.getX() - (numDigits - 1)));
		//helper is a point that we use by value. we use him because we dont wanna change copy
		helper.setX(copy.getX());
		helper.setY(copy.getY());

		i = 0;
		//creating num from board into res
		while (numDigits != 0)
		{
			res = res * 10 + (board[helper.getY()][helper.getX()]);
			//exetreme case.if helper is in the head we dont wanna delete the drawing of head from screen.else do.
			if (helper.getX() != pos.getX() || helper.getY() != pos.getY())
				helper.draw(' ');

			board[helper.getY()][helper.getX()] = ' ';
			helper.setX(helper.getX() + 1);
			++i;
			--numDigits;
		}

	}
	else//in this case we didnt meet in a number
		res = SNAKE_DIDNT_EAT_NUM;
	return copy;

}

//this function increase the vector of point of numbers in board.
void Board::storeInNumArr(const Point& newPoint)
{
	numbersOnBoard.push_back(newPoint);
}

//this function delete half of the numbers from board. and update numsInBoard into the right amount after delete half.
void Board::deleteHalfNumbers(int & numsInBoard)
{
	int sizeHalf = numbersOnBoard.size() / 2;
	//updating numsInBoard
	numsInBoard = numbersOnBoard.size()-sizeHalf;
	//we wanna delete sizeHalf numbers
	for (int i = 0;i < sizeHalf;++i)
	{ 
		//here we rand a index. from 0 to number of numbers
		int indexToDel = rand() % numbersOnBoard.size();
		//in this while we delete the number in board char after char
		//so we continue as long we didnt reach the end of number
		while (isPointANumber(numbersOnBoard.at(indexToDel).getX(), numbersOnBoard.at(indexToDel).getY())==true)
		{
			//updating board
			board[numbersOnBoard.at(indexToDel).getY()][numbersOnBoard.at(indexToDel).getX()] = ' ';
			//print to screen  ' '
			numbersOnBoard.at(indexToDel).draw(' ');
			//in the start every point set to the left position in number
			//here we move him right every time by 1;
			numbersOnBoard.at(indexToDel).setX(numbersOnBoard.at(indexToDel).getX()+1);
		}
		//here we delete the number from the vector of numbers
		numbersOnBoard.erase(numbersOnBoard.begin() + indexToDel);
	}
}

//this function delete point from vector of numbers. the point represent place of num in board.
void Board::eraseFronNumbersOnBoard(const Point & poinToDelete)
{
	int i = 0, checkX,checkY;

	checkX= poinToDelete.getX();
	checkY = poinToDelete.getY();
	
	for ( i = 0;i < numbersOnBoard.size();++i)
	{
		//we check if this is the point we wanna delete
		if (checkX == numbersOnBoard.at(i).getX() && checkY == numbersOnBoard.at(i).getY())
		{
			numbersOnBoard.erase(numbersOnBoard.begin() + i);
			//in this case we dont wanna continue in function any more.
			break;
		}
	}

}

Point Board::deleteNumberFromBoard(Point p)
{
	Point leftPoint;
	//here we bring p to the left digit of the number
	while (isPointANumber(p.getX(), p.getY()) == true)
		p.setX(p.getX() - 1);
	//in the end we have to bring p by one
	p.setX(p.getX() + 1);
	//we gonna return left point
	leftPoint.setPoint(p.getX(), p.getY(), p.getDirX(), p.getDirY());
	while (isPointANumber(p.getX(), p.getY()) == true)
	{
		setBoard(p, ' ');
		p.draw(' ');
		p.setX(p.getX() +1);
	}
	return leftPoint;


}

//this function initial board in snake position
void Board::enterIntialSnakeToBoard()
{
	board[9][72] = board[9][71] = board[9][70] = '#';
	board[9][8] = board[9][9] = board[9][10] = '@';
}

//this function changes the value of point in board
void Board::setBoard(const Point & p, char c)
{
	board[p.getY()][p.getX()] = c;
}

//this function return value of point in board
char Board::getCharFromBoard(const Point & p)
{
	return board[p.getY()][p.getX()];
}

//this function return true if a point in board is a digit:its mean we set on a number.
bool Board::isPointANumber(int x,int y)
{
	if (board[y][x] != ' '&&board[y][x] != '+'&&board[y][x] != '#'&&board[y][x] != '@' && board[y][x]!='*'
		&&board[y][x] != '!'&&board[y][x] != '$' && board[y][x] != '%')
		return true;
	return false;
}

//this function return true if a point in board is a snake:its mean we set on a snake.
bool Board::isPointASnake(int x, int y)
{
	if (board[y][x] == '#' || board[y][x] == '@')
		return true;
	return false;
}

bool Board::isPointABullet(int x, int y)
{
	if (board[y][x] == '*')
		return true;
	return false;
}

bool Board::isPointAFlyer(const Point & p)
{
	if(getCharFromBoard(p) == '%' || getCharFromBoard(p) == '$' || getCharFromBoard(p) == '!')
		return true;
	return false;
}

//this function shows the sub menu to screen and return the choice of player
int Board::escMenu()
{
	system("CLS");
	gotoxy(27, 6);
	cout << "Hi there, please select your choich:";
	gotoxy(27, 7);
	cout << "1. Get Out of The Game";
	gotoxy(27, 8);
	cout << "2. Get Back To Main Menu";
	gotoxy(27, 9);
	cout << "3. Continue Play From Last Point";
	gotoxy(27, 10);
	cout << "4. Start This Mission from The Start";
	gotoxy(27, 11);
	cout << "5. Start New  Mission";
	gotoxy(27, 12);
	cout << "6. Start New Game";
	gotoxy(27, 13);
	cout << "7. Replay Last Mission";
    gotoxy(27, 15);
	return choice();
	
}

//this function set a point that represent the place in board we write the score,to his place.
void Board::SetPointOfScore(Point & pointOfScore1, Point & pointOfScore2)
{
	//point score of player 1
	pointOfScore1.setX(25);
	pointOfScore1.setY(2);

	//point score of player 2
	pointOfScore2.setX(70);
	pointOfScore2.setY(2);
}

void Board::SetPointOfBullets(Point & pointOfScore1, Point & pointOfScore2)
{
	//point bullets of player 1
	pointOfScore1.setX(30);
	pointOfScore1.setY(2);

	//point bullets of player 2
	pointOfScore2.setX(75);
	pointOfScore2.setY(2);
}

//this function delete from board all the numbers
void Board::cleanNumbersOnBoard()
{
	for(int i=4;i<24;++i)
	{
		for (int j = 1; j < 78; ++j)
		{
			setBoard({ j,i }, ' ');
		}
	}
}

//this function empty the vector of points of numbers
void Board::emptyNumbersOnBoardVector()
{
	numbersOnBoard.clear();
}

//this function flashes the numbers when we reach 60 in board
void Board::flashNumbers(int missioNumber)
{
	bool thereIsolution = false;
	Point p;
	Mission mission;
	//we goes throw all the numbers in board
	for (int i = 0; i < numbersOnBoard.size(); ++i)
	{
		//here we get the point from board
		int num = getNumberFromBoard(numbersOnBoard.at(i));
		//if this number is a answer to this mission
		if (mission.manageMission(missioNumber, num) == true)
		{
			//there is soloution
			thereIsolution = true;
			//we flashing the number 2 times
			for (int k = 0; k < 2; ++k)
			{
				Sleep(600);
				p = numbersOnBoard.at(i);
				//we first clear in screen the number
				for (int j = 0; j < getNumOfDigits(num); ++j)
				{
					p.draw(' ');
					p.setX(p.getX() + 1);
				}
				Sleep(600);
				//and later we print the number
				numbersOnBoard.at(i).draw(num);
				Sleep(600);
			}
		}
	}
	if (thereIsolution == false)
	{
		//printing there is no soloution
		gotoxy(60, 1);
		cout << "no Soloutions";
		Sleep(1000);
		//deleting the statement of no solution
		gotoxy(60, 1);
		cout << "              ";
	}
}

//this function gets number and his num digits ,and a point that represent the place we wanna start
//put the point in board
void Board::UpdateBoard(int numDigits, int num, const Point& p)
{
	int copyOfNum = num;
	//we run the numdigits, we start from the right.
	for (int i = numDigits-1;i >=0;--i)
	{
		char ch = (char)((num % 10) + '0');
		board[p.getY()][p.getX() + i] = ch;
		num = num / 10;
	}
	//here wwe print thee number into screen in the right point
	gotoxy(p.getX(), p.getY());
	cout << copyOfNum;
}

//this function gets numdigits of a number.and point that represent his start.
//return false if we can put the point in this place with all the ristrictions.
bool Board::checkPositionInBoardArray(const Point & p, int numDigits)
{
	for (int i = 0;i < numDigits; ++i)
	{
		if (isPointANumber(p.getX() + i, p.getY()) == true || isPointANumber(p.getX() + i, p.getY() + 1) == true || isPointANumber(p.getX() + i, p.getY() - 1) == true)
			return false;
		
		if (isPointASnake(p.getX() + i, p.getY()) == true || isPointASnake(p.getX() + i, p.getY() + 1) == true || isPointASnake(p.getX() + i, p.getY() - 1) == true)
			return false;
	}

	if (p.getX() + numDigits > Point::max_x + 1 || isPointANumber(p.getX() - 1, p.getY()) == true || isPointANumber(p.getX() + numDigits, p.getY()) == true)
		return false;
	if (isPointASnake(p.getX() -1, p.getY()) == true || isPointASnake(p.getX() + numDigits, p.getY()) == true)
		return false;
	if (getCharFromBoard(p) == '%' || getCharFromBoard(p) == '$' || getCharFromBoard(p) == '!'|| getCharFromBoard(p) == '*')
		return false;

	return true;
}

//this function gets point that represent start of number.
//return the number
int Board::getNumberFromBoard(Point p)
{
	int res = 0;

	while (isPointANumber(p.getX(), p.getY()) == true)
	{
		res = res * 10 + (getCharFromBoard(p) - '0');
		p.setX(p.getX() + 1);
	}
	return res;
}

//this function print board to screen
void Board::displayScreen()
{
	string line;
	gotoxy(0, 0);
	for (int i = 0;i < MAX_Y;++i)
	{
		cout << board[i] << endl;
	}
}

//this function gets number and return the num of his digits
int Board::getNumOfDigits(int num)
{
	if (num == 0)
		return 1;
	int res = 0;
	while (num)
	{
		++res;
		num = num / 10;
	}
	return res;
}

//this function gets number of group and return random number from group.
int Board::getGroupNumber(GROUP g)
{
	switch (g)
	{
	case ONE:
		return (rand() % 26);
	case TWO:
		return (rand() % (81 - 25) + 26);
	case THREE:
		return (rand() % (169 - 81) + 82);
	default:
		break;
	}
}