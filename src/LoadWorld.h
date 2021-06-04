#ifndef LOADWORLD_H_
#define LOADWORLD_H_

#include "Globals.h"
#include "Tools.h"

using namespace std;

class LoadWorld
{
	string fileName;
	vector<int> elements;
	vector<int> lands;
	unsigned int width;
	unsigned int height;
	unsigned int elementIdx;
	unsigned int landIdx;
	void load();

public:
	LoadWorld(string);
	int getWidth();
	int getHeight();
	int getNext(int);
	void reset(int);
	virtual ~LoadWorld();
};

#endif /* LOADWORLD_H_ */
