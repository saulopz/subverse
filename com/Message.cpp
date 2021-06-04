#include "Message.h"

Message::Message(int i)
{
	id = i;
	type = MSG_NULL;
	content = "";
}

Message::Message(int i, string c)
{
	id = i;
	type = MSG_NULL;
	content = c;
}

Message::Message(int i, int t, string c)
{
	id = i;
	type = t;
	content = c;
}

int Message::getId()
{
	return id;
}

int Message::getType()
{
	return type;
}

void Message::setType(int t)
{
	type = t;
}

string Message::toString()
{
	// Arrumar isso aqui
	return content;
}

string Message::get()
{
	return content;
}

void Message::set(string c)
{
	content = c;
}

void Message::clear()
{
	content = "";
}

Message::~Message()
{
}
