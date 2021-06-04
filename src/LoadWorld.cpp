#include "LoadWorld.h"

LoadWorld::LoadWorld(string f)
{
	width = 0;
	height = 0;
	elementIdx = 0;
	landIdx = 0;
	fileName = f;
	load();
}

void LoadWorld::load()
{
	FILE *fp;
	if ((fp = fopen(fileName.c_str(), "r")) == NULL)
	{
		cerr << "Error loanding file" << fileName << endl;
	}

	bool tag = false;
	bool iten = false;
	bool content = false;
	int type = NONE;
	string value = "";

	while (!feof(fp))
	{
		int c = fgetc(fp);
		if (!content)
		{
			if (!tag)
			{
				if (c == '<')
				{
					tag = true;
				}
				else if (c == '{')
				{
					content = true;
				}
			}
			else
			{
				if (c == '>')
				{
					tag = false;
					if (value.compare("element") == 0)
					{
						type = ELEMENT;
					}
					else if (value.compare("land") == 0)
					{
						type = LAND;
					}
					else if (value.compare("world") == 0)
					{
						type = WORLD;
					}
					value = "";
				}
				else
				{
					value += c;
				}
			}
		}
		else
		{
			if (c == '}')
			{
				content = false;
			}
			else if (!iten)
			{
				if (c == '[')
				{
					iten = true;
				}
			}
			else if (iten)
			{
				if (c == ']')
				{
					iten = false;
					if (type == ELEMENT)
					{
						elements.push_back(Tools::stringToInt(value));
					}
					else if (type == LAND)
					{
						lands.push_back(Tools::stringToInt(value));
					}
					else if (type == WORLD)
					{
						if (width == 0)
						{
							width = Tools::stringToInt(value);
						}
						else
						{
							height = Tools::stringToInt(value);
						}
					}
					value = "";
				}
				else
				{
					value += c;
				}
			}
		}
	}
	fclose(fp);
	uint size = width * height;
	if ((width == 0) || (height == 0) ||
		(size != lands.size()) || (size != elements.size()))
	{
		cerr << "Invalid world file: " << fileName << endl;
		exit(1);
	}
}

int LoadWorld::getNext(int type)
{
	int temp = 0;
	if (type == ELEMENT)
	{
		if (elementIdx < elements.size())
		{
			temp = elements[elementIdx];
			elementIdx++;
		}
	}
	else if (type == LAND)
	{
		if (landIdx < lands.size())
		{
			temp = lands[landIdx];
			landIdx++;
		}
	}
	return temp;
}

void LoadWorld::reset(int type)
{
	if (type == ELEMENT)
	{
		elementIdx = 0;
	}
	else if (type == LAND)
	{
		landIdx = 0;
	}
}

int LoadWorld::getWidth()
{
	return width;
}

int LoadWorld::getHeight()
{
	return height;
}

LoadWorld::~LoadWorld()
{
}
