#include "Vision.h"

Vision::Vision()
{
	indexElement = 0;
	indexLand = 0;
}

Element *Vision::next(int type)
{
	Element *e = NULL;
	if (type == ELEMENT)
	{
		if (indexElement < element.size())
		{
			e = element[indexElement];
			indexElement++;
		}
	}
	else if (type == LAND)
	{
		if (indexLand < land.size())
		{
			e = land[indexLand];
			indexLand++;
		}
	}
	return e;
}

void Vision::reset(int type)
{
	if (type == ELEMENT)
	{
		indexElement = 0;
	}
	else if (type == LAND)
	{
		indexLand = 0;
	}
}

void Vision::add(Element *e, int type)
{
	if (e != NULL)
	{
		if (type == ELEMENT)
		{
			element.push_back(e);
		}
		else if (type == LAND)
		{
			land.push_back(e);
		}
	}
}

Vision::~Vision()
{
}
