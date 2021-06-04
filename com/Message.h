#ifndef MESSAGE_H
#define MESSAGE_H

#include "Config.h"

class Message
{
private:
	int id;
	int type;
	string content;

public:
	Message(int);
	Message(int, string);
	Message(int, int, string);
	string toString();
	string get();
	int getId();
	int getType();
	void addMessage(Message *);
	void setType(int);
	void set(string);
	void clear();
	virtual ~Message();
};

#endif /* MESSAGE_H */
