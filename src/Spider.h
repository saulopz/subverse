#ifndef SPIDER_H_
#define SPIDER_H_

#include <string>
#include "Globals.h"
#include "Element.h"

class Spider : public Element
{
public:
	Spider(World *);
	virtual void execute();
	virtual ~Spider();
};

#endif /* SPIDER_H_ */
