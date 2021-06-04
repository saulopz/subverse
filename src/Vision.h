#ifndef VISION_H_
#define VISION_H_

#include <vector>
#include "Globals.h"
#include "Element.h"

class Element;

class Vision
{
	unsigned int indexElement;
	unsigned int indexLand;
	vector<Element *> element;
	vector<Element *> land;

public:
	Vision();
	Element *next(int);
	void reset(int);
	void add(Element *, int);
	virtual ~Vision();
};

#endif /* VISION_H_ */
