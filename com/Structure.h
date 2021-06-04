#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Config.h"
#include "Variable.h"

class Structure
{
private:
	vector<Variable *> variables;

public:
	Structure();
	Structure(string);
	void add(Variable *);
	Variable *get(int);
	Variable *get(string);
	int size();
	string toString();
	virtual ~Structure();
};

#endif /* STRUCTURE_H */
