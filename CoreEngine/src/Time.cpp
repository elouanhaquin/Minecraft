#include "stdafx.h"
#include "Time.h"

using namespace TimeNS;

double Time::time = 0.0f;
double Time::deltaTime = 0.0f;
double Time::dayTime = 0.0f;
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
	float ti = (glfwGetTime())*0.1f + 360.0f; // 360 is to start in the day, 0.1f is the time speed
	Time::dayTime = std::sin(ti) + 0.8f;
}

Time::~Time()
{

}