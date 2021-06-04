#include "Variable.h"

Variable::Variable(string pack)
{
	name = "";
	value = "";

	char str[255] = "";
	strcpy(str, pack.c_str());
	char *pch;
	int i = 0;

	pch = strtok(str, ":");
	while (pch != NULL)
	{
		switch (i)
		{
		case 0:
			sscanf(pch, "%d", &type);
			break;
		case 1:
			name = pch;
			break;
		case 2:
			value = pch;
			break;
		}
		pch = strtok(NULL, ":");
		i++;
	}
}

Variable::Variable(string mname, char mvalue)
{
	name = mname;
	char str[255];
	sprintf(str, "%c", mvalue);
	value = str;
	type = MSG_TYPE_CHAR;
}

Variable::Variable(string mname, string mvalue)
{
	name = mname;
	value = mvalue;
	type = MSG_TYPE_STRING;
}

Variable::Variable(string mname, int mvalue)
{
	name = mname;
	char str[255];
	sprintf(str, "%d", mvalue);
	value = str;
	type = MSG_TYPE_INT;
}

Variable::Variable(string mname, double mvalue)
{
	name = mname;
	char str[255];
	sprintf(str, "%lf", mvalue);
	value = str;
	type = MSG_TYPE_DOUBLE;
}

string Variable::getName()
{
	return name;
}

int Variable::getType()
{
	return type;
}

char Variable::getChar()
{
	char aux;
	sscanf(value.c_str(), "%c", &aux);
	return aux;
}

string Variable::getString()
{
	return value;
}

int Variable::getInt()
{
	int aux;
	sscanf(value.c_str(), "%d", &aux);
	return aux;
}

double Variable::getDouble()
{
	double aux;
	sscanf(value.c_str(), "%lf", &aux);
	return aux;
}

string Variable::toString()
{
	char *charType = (char *)malloc(255);
	sprintf(charType, "%d", type);
	string sType = charType;
	string aux = sType + ":" + name + ":" + value;
	return aux;
}

Variable::~Variable()
{
}
