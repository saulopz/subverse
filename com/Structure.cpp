#include "Structure.h"

Structure::Structure()
{
}

Structure::Structure(string pack)
{
	vector<string> vars;

	char str[1024] = "";
	strcpy(str, pack.c_str());
	char *pch;
	pch = strtok(str, ";");
	while (pch != NULL)
	{
		vars.push_back(pch);
		pch = strtok(NULL, ";");
	}
	for (unsigned int i = 0; i < vars.size(); i++)
	{
		add(new Variable(vars[i]));
	}
}

void Structure::add(Variable *variable)
{
	variables.push_back(variable);
}

Variable *Structure::get(int pos)
{
	if ((u_int)pos >= variables.size())
	{
		return NULL;
	}
	return variables[pos];
}

Variable *Structure::get(string varName)
{
	Variable *variable = NULL;
	unsigned int i = 0;
	while (i < variables.size())
	{
		Variable *aux = variables[i];
		if (aux->getName().compare(varName) == 0)
		{
			variable = aux;
			i = variables.size();
		}
		i++;
	}
	return variable;
}

int Structure::size()
{
	return variables.size();
}

string Structure::toString()
{
	string pack = "";
	for (unsigned int i = 0; i < variables.size(); i++)
	{
		Variable *var = variables[i];
		pack += var->toString();
		if (i < (variables.size() - 1))
		{
			pack += ";";
		}
	}
	return pack;
}

Structure::~Structure()
{
}
