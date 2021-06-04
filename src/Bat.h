#ifndef BAT_H_
#define BAT_H_

#include <string>
#include "Globals.h"
#include "Element.h"

class Bat : public Element
{
public:
	Bat(World *);
	virtual void execute();
	virtual ~Bat();
};

#endif /* BAT_H_ */
