#ifndef IMAGES_H_
#define IMAGES_H_

#include "Enjin.h"
#include "Globals.h"
#include "Tools.h"

using namespace std;

class Images
{
	Enjin *g;
	map<string, Image *> bitmaps;

public:
	Images();
	void add(string);
	Image *get(string);
	virtual ~Images();
};

#endif /* IMAGES_H_ */
