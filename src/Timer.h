#ifndef TIMER_H_
#define TIMER_H_

#include <string>
#include "Tools.h"

using namespace std;

class Timer
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	Timer();
	void inc();
	string toString();
	long valueOf();
	void reset();
	void setYear(int);
	void setMonth(int);
	void setDay(int);
	void setHour(int);
	void setMinute(int);
	void setSecond(int);
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	int getSecond();
	virtual ~Timer();
};

#endif /* TIMER_H_ */
