#include "ElementMessage.h"

ElementMessage::ElementMessage(Element *msg_sender, string msg_content)
{
	sender = msg_sender;
	content = msg_content;
}

Element *ElementMessage::getSender()
{
	return sender;
}

string ElementMessage::getContent()
{
	return content;
}

ElementMessage::~ElementMessage()
{
}
