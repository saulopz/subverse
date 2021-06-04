#ifndef VARIABLE_H
#define VARIABLE_H

#include "Config.h"

class Variable
{
private:
	int type;
	string name;
	string value;

public:
	Variable(string);
	Variable(string, string);
	Variable(string, int);
	Variable(string, double);
	Variable(string, char);
	string getName();
	int getType();
	string getString();
	int getInt();
	double getDouble();
	char getChar();
	string toString();
	virtual ~Variable();
};

#endif /* VARIABLE_H */
