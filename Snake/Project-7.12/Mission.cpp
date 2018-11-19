#include "Mission.h"

//this function print the current mission in a point we choosen
void Mission::loadNewMission(Board & board, int missionNumber)
{
	int i;
	gotoxy(10, 1);
	for (i = 0; i < MAX_SIZE_MISSION_NAME; ++i)
		cout << ' ';
	gotoxy(10, 1);

	string s = getMission(missionNumber);

	for (i = 0; i < s.size(); ++i)
		board.setBoard({ 10 + i,1 }, s[i]);
	cout << s;

	gotoxy(10, 1);
}

//this function return true if we collect the number that answer the current mission else return false
bool Mission::manageMission(int missionNumber, int num)
{
	switch (missionNumber)
	{
	case 0:
		return M1_modX(num);
		break;
	case 1:
		return M2_gtXstY(num);
		break;
	case 2:
		return M3_checkPrimary(num);
		break;
	case 3:
		return M4_divXModY(num);
		break;
	case 4:
		return M5_solve(num);
		break;
	default:
		break;
	}
}

//this function return true if a number is primary
bool Mission::M3_checkPrimary(int num)
{
	int primeNumbers[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167 };
	for (int i = 0;i < 39;++i)
	{
		if (num == primeNumbers[i] && num < x_member)
			return true;
	}
	return false;
}

//this function return true if a number mod 4 is 0
bool Mission::M1_modX(int num)
{
	if (num % x_member == 0)
		return true;
	return false;
}

bool Mission::M2_gtXstY(int num)
{
	if (num >= x_member && num <= y_member)
		return true;
	return false;
}


//this function return true if a number mod7=3
bool Mission::M4_divXModY(int num)
{
	if (num % x_member == y_member)
		return true;
	return false;
}

//this function return true we the right answer
bool Mission::M5_solve(int num)
{
	if (num == checkNumber)
		return true;
	return false;
}

//this function create exercise and return the string we need to print
string Mission::buildExercise7()
{
	int  op1, op2, temp2;
	double num1, num2, num3, num4, temp1;
	bool exIsGood = false;
	//we keep in the while as long we didnt rand a good exercise
	while (exIsGood == false)
	{
		num1 = rand() % 170;
		num2 = rand() % 170;
		num3 = rand() % 170;
		op1 = rand() % 4;
		op2 = rand() % 4;
		//its a priority if the first operator is plus or minus we start with the second operator
		if (op1 == Plus || op1 == Minus)
		{
			//we first sum num2 operator num 3 and temp1 is the result
			switch (op2)
			{
			case Plus:
				temp1 = num2 + num3;
				break;
			case Minus:
				temp1 = num2 - num3;
				break;
			case Mul:
				temp1 = num2*num3;
				break;
			case Div:
				temp1 = num2 / num3;
				break;
			}

			//now we sum num1 operator temp1
			if (op1 == Plus)
				num4 = num1 + temp1;
			else if (op1 == Minus)
				num4 = num1 - temp1;
			else if (op1 == 2)
				num4 = num1* temp1;
			else
				num4 = (double)(num1 / temp1);
		}
		else
		{
			//otherwise we make the first operator first
			//in this case we sum num1 operator num2. temp1 is the result
			switch (op1)
			{
			case Plus:
				temp1 = num1 + num2;
				break;
			case Minus:
				temp1 = num1 - num2;
				break;
			case Mul:
				temp1 = num1*num2;
				break;
			case Div:
				temp1 = num1 / num2;
				break;
			}
			//now we sum temp1 operator num3
			if (op2 == Plus)
				num4 = temp1 + num3;
			else if (op2 == Minus)
				num4 = temp1 - num3;
			else if (op2 == Mul)
				num4 = temp1 * num3;
			else
				num4 = (double)(temp1 / num3);
		}
		//here we make a tric. we submit the integer number of num4 to temp 2
		temp2 = num4;
		//if num4 is not equal to num4 we rand again new numbers and operators
		if (num4 == temp2   && num4 >= 0 && num4 <= 169)
			exIsGood = true;
	}
     return createStringFromExercise(num1, op1, num2, op2, num3, num4);
}

//this function build the string of the exercise and return him
string Mission::createStringFromExercise(int num1, int op1, int num2, int op2, int num3, int num4)
{
	string res;
	char operator1, operator2;
	operator1 = getOperator(op1);
	operator2 = getOperator(op2);

	int numToHide = rand() % 4 +1;

	switch (numToHide)
	{
	case 1:
		res = "Solve _ " + (operator1 + to_string(num2)) + operator2 + to_string(num3) + '=' + to_string(num4);
		checkNumber = num1;
		break;
	case 2:
		res ="Solve " + to_string(num1) + operator1 + "_ " + operator2 + to_string(num3) + "=" + to_string(num4);
		checkNumber = num2;
		break;
	case 3:
		res ="Solve " + to_string(num1) + operator1 + to_string(num2) + operator2 + "_" + "=" + to_string(num4);
		checkNumber = num3;
		break;
	case 4:
		res ="Solve " + to_string(num1) + operator1 + to_string(num2) + operator2 + to_string(num3) + "=" + "_";
		checkNumber = num4;
		break;
	}
	return res;
}

string Mission::getMission(int missionNumber)
{
	string res;
	switch (missionNumber)
	{
	case 0:
		x_member = rand() % 6 + 2;
		res = "Get a number that divide by " + to_string(x_member);
		break;
	case 1:
		x_member= rand() % 20 + 1;
		y_member = rand() % 21 + 20;
		res = "Collect a number that bigger than " + to_string(x_member) + " but smaller than " + to_string(y_member);
		break;
	case 2:
		x_member= rand() % 167 + 3;
		res = "Get primary number smaller than " + to_string(x_member);
		break;
	case 3:
		x_member = rand() % 10 + 1;
		y_member = rand() % 4 + 1;
		res = "Get a number that its modulu with " + to_string(x_member) + " is " + to_string(y_member);
		break;
	case 4:
		res = buildExercise7();
		break;
	default:
		break;
	}
	return res;
}

//this function return the char of each operator
char Mission::getOperator(int op)
{
	if (op == Plus)
		return '+';
	else if (op == Minus)
		return '-';
	else if (op == Mul)
		return '*';
	else
		return '/';
}


