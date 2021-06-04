#ifndef AVATAR_H_
#define AVATAR_H_

#include <string>
#include "Globals.h"
#include "Element.h"

class Avatar : public Element
{
private:
	Enjin *g;
	bool key(int t);

public:
	Avatar(World *);
	virtual void execute();
	virtual ~Avatar();
};

#endif /* AVATAR_H_ */
