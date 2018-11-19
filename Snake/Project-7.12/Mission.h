#ifndef __MISSION_H__
#define __MISSION_H__

#include <math.h>
#include "Gotoxy.h"
#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

enum { MAX_SIZE_MISSION_NAME = 60 };

class Mission {
	int checkNumber = Mission7DidntAppear;
	int x_member = NOT_INITIALIZED;
	int y_member = NOT_INITIALIZED;

public:
	enum MISSION { MAX_MISSIONS = 5 };
	enum { Mission7DidntAppear = -1 };
	enum Operators { Plus, Minus, Mul, Div };
	enum {NOT_INITIALIZED = -1};

	void loadNewMission(Board & board, int missionNumber);
	int getCheckNumber(){return checkNumber;}
	bool manageMission(int missionNumber, int num);
	bool M1_modX(int num);
	bool M2_gtXstY(int num);
	bool M3_checkPrimary(int num);
	bool M4_divXModY(int num);
	bool M5_solve(int num);
	string buildExercise7();
	string createStringFromExercise(int num1, int op1, int num2, int op2, int num3, int num4);
	string getMission(int missionNumber);
	char getOperator(int op);


	

};
#endif // !__MISSION_H__
