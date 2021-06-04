#include "Timer.h"

Timer::Timer()
{
	reset();
}

void Timer::reset()
{
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	minute = 0;
	second = 0;
}

void Timer::inc()
{
	second++;
	if (second > 59)
	{
		second = 0;
		minute++;
		if (minute > 59)
		{
			minute = 0;
			hour++;
			if (hour > 24)
			{
				hour = 0;
				day++;
				if (day > 30)
				{
					day = 1;
					month++;
					if (month > 11)
					{
						month = 1;
						year++;
					}
				}
			}
		}
	}
}

string Timer::toString()
{
	string out = Tools::intToString(year);
	out += ".";
	out += Tools::intToString(month);
	out += ".";
	out += Tools::intToString(day);
	out += ".";
	out += Tools::intToString(hour);
	out += ".";
	out += Tools::intToString(minute);
	out += ".";
	out += Tools::intToString(second);
	return out;
}

long Timer::valueOf()
{
	long out = second;
	out += minute * 60;
	out += hour * 60 * 60;
	out += day * 60 * 60 * 24;
	out += month * 60 * 60 * 24 * 30;
	out += year * 60 * 60 * 24 * 30 * 12;
	return out;
}

void Timer::setYear(int y)
{
	if (y < 1)
	{
		year = 1;
	}
	else
	{
		year = y;
	}
}

void Timer::setMonth(int m)
{
	if (m < 1)
	{
		month = 1;
	}
	else if (m > 12)
	{
		month = 12;
	}
	else
	{
		month = m;
	}
}

void Timer::setDay(int d)
{
	if (d < 1)
	{
		day = 1;
	}
	else if (d > 30)
	{
		day = 30;
	}
	else
	{
		day = d;
	}
}

void Timer::setHour(int h)
{
	if (h < 0)
	{
		hour = 0;
	}
	else if (h > 24)
	{
		hour = 24;
	}
	else
	{
		hour = h;
	}
}

void Timer::setMinute(int m)
{
	if (m < 0)
	{
		minute = 0;
	}
	else if (m > 60)
	{
		minute = 60;
	}
	else
	{
		minute = m;
	}
}

void Timer::setSecond(int s)
{
	if (s < 0)
	{
		second = 0;
	}
	else if (s > 60)
	{
		second = 60;
	}
	else
	{
		second = s;
	}
}

int Timer::getYear()
{
	return year;
}

int Timer::getMonth()
{
	return month;
}

int Timer::getDay()
{
	return day;
}

int Timer::getHour()
{
	return hour;
}

int Timer::getMinute()
{
	return minute;
}

int Timer::getSecond()
{
	return second;
}

Timer::~Timer()
{
}
