#include "Clock.h"

Clock::Clock()

{
	prev_time = clock();
}

Clock::Time::Time(double cur_time): time(cur_time)

{

}

double Clock::Time::inMicroSeconds()

{
	return time * 1000;
}

double Clock::Time::inMilliSeconds()

{
	return time;
}

double Clock::Time::inSeconds()

{
	return time / 1000.0;
}

void Clock::restart()

{
	prev_time = clock();
}

Clock::Time Clock::elapsed()

{
	return Time((double)(clock() - prev_time));
}