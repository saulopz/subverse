#ifndef CYCLOPE_H_
#define CYCLOPE_H_

#include <string>
#include "Globals.h"
#include "Element.h"

#define RUNAWAY 0
#define WALK 1
#define EAT 2
#define ATTACK 3
#define GROUP 4
#define TURN 5

class Cyclope : public Element
{
private:
	int behavior;
	bool hunger;
	bool askForSupport;
	bool askForHelp;
	int randomCounter;
	vector<Element *> friends;
	Element *helpsTo;

public:
	Cyclope(World *);
	virtual void execute();
	virtual string toString();
	virtual ~Cyclope();

	// Comportamentos
	void walk();
	void randomWalk();
	void goTo(Element *e);
	bool goToVertical(Element *e);
	bool goToHorizontal(Element *e);
	void eat(Element *e);
	void runAway(Element *e);
	void attack(Element *e);
	void group(Element *e);
	int benefit();

	void addFriend(Element *e);
	void talkToFriends(string text);
};

#endif /* CYCLOPE_H_ */
