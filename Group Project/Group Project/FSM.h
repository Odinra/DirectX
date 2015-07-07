#ifndef FSM_H_
#define FSM_H_

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>
#include <cstdlib>

using namespace std;

class Racer;

class State
{
public:
	virtual void Execute(Racer*)=0;
}

class Racer
{
public:
	State* currentState;
	Racer();
	void Update(){
		currentState->Execute(this);
	}
	void UpdateState(State* newState)
	{
		delete currentState;
		currentState = newState;
	}
};

class RacerAccelerate:public State
{
public:
	RacerAccelerate(){};
	void Execute(Racer* racer);
};

class RacerTurn:public State
{
public:
	RacerTurn(){};
	void Execute(Racer* racer);
};

class RacerReverse:public State
{
public:
	RacerReverse(){};
	void Execute(Racer* racer);
};

class RacerAvoid:public State
{
public:
	RacerAvoid(){};
	void Execute(Racer* racer);
};

class RacerAttack:public State
{
public:
	RacerAttack(){};
	void Execute(Racer* racer);
};

class RacerDead:public State
{
public:
	RacerDead(){};
	void Execute(Racer* racer);
};

#endif