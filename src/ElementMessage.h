#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>
#include <string>
#include "Globals.h"

class Element;

class ElementMessage
{
private:
	Element *sender;
	string content;

public:
	ElementMessage(Element *, string);
	Element *getSender();
	string getContent();
	~ElementMessage();
};

#endif /* MESSAGE_H_ */
