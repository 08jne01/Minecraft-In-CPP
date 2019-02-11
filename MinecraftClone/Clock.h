#pragma once
#include <ctime>

class Clock

{
public:

	class Time

	{
	public:
		Time(double cur_time);
		double inMicroSeconds();
		double inMilliSeconds();
		double inSeconds();
	private:
		double time;
	};

	Clock();
	void restart();
	Time elapsed();

	

private:
	double prev_time;
};