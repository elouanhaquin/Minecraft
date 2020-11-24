#include "stdafx.h"
#include "Time.h"

using namespace TimeNS;

double Time::time = 0.0f;
double Time::deltaTime = 0.0f;
double Time::fixedDeltaTime = 1.0f / 60.0f;

Time::Time()
{
	//time		=	0.0f;
	//deltaTime	=	0.0f;
}

void Time::UpdateTime()
{
	const double previousTime = time;
	Time::time = glfwGetTime();
	Time::deltaTime = time - previousTime;
}

Time::~Time()
{

}