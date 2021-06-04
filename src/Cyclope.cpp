#include "Cyclope.h"
#include "World.h"
#include <stdlib.h>
#include <time.h>

Cyclope::Cyclope(World *w) : Element(w, "cyclope", CYCLOPE)
{
	behavior = WALK;
	hunger = false;
	helpsTo = NULL;
	askForSupport = false;
	askForHelp = false;
	randomCounter = 0;
}

void Cyclope::execute()
{
	bool found = false;
	// verifies if health is poor
	if (getHelth() < 50)
	{
		hunger = true;
	}
	else if (getHelth() > 70)
	{
		hunger = false;
	}
	// if not going to help someone
	if (helpsTo == NULL)
	{
		if (isUnderAttack())
		{
			if (hunger)
			{
				if (!getAttacker()->isAlive())
				{
					eat(getAttacker());
					found = true;
				}
				else
				{
					if (getHelth() < 40)
					{
						setTalk("help");
						talkToFriends("help");
						askForHelp = true;
					}
					if (benefit() > 0)
					{
						attack(getAttacker());
					}
					else if (benefit() == 0)
					{
						if (getHelth() > getAttacker()->getHelth() + 10)
						{
							attack(getAttacker());
						}
					}
					else
					{
						runAway(getAttacker());
						talkToFriends("help");
						askForHelp = true;
					}
				}
			}
			else
			{
				if (getAttacker()->isAlive())
				{
					attack(getAttacker());
					if (!askForSupport)
					{
						talkToFriends("help");
						setTalk("I need help");
						askForSupport = true;
					}
					found = true;
				}
			}
		}
		else
		{
			// According to the objects seen by the agent, he tries
			// to choose the objective according to his priority
			Vision *vision = getVision();
			Element *e = NULL;
			Element *aux = NULL;
			while ((aux = vision->next(ELEMENT)) != NULL)
			{
				if (e == NULL)
				{
					e = aux;
				}
				else
				{
					if (e->getType() != aux->getType())
					{
						if (hunger)
						{
							if (aux->getType() == TREE)
							{
								if (aux->getFood() > 0)
								{
									e = aux;
								}
							}
							else if (aux->isCreature())
							{
								if (aux->isAlive())
								{
									if (aux->getType() != CYCLOPE)
									{
										e = aux;
									}
								}
								else if (aux->getFood() > 0)
								{
									e = aux;
								}
							}
						}
						else
						{
							if (!e->isCreature() && aux->isCreature() && aux->isAlive())
							{
								e = aux;
							}
						}
					}
				}
			}
			// Chosen the target, look for the best behavior
			if (e != NULL)
			{
				// if health is poor
				if (hunger)
				{
					if (e->isCreature())
					{
						if (!e->isAlive())
						{
							if (e->getFood() > 0)
							{
								found = true;
								eat(e);
							}
						}
						else if (e->getType() != CYCLOPE)
						{
							found = true;
							if (benefit() > 0)
							{
								attack(e);
							}
							else if (benefit() == 0)
							{
								if (getHelth() > e->getHelth() + 10)
								{
									attack(e);
								}
							}
							else
							{
								talkToFriends("help");
								askForHelp = true;
								runAway(e);
							}
						}
					}
					else if ((e->getType() == TREE) && (e->getFood() > 0))
					{
						found = true;
						eat(e);
					}
					// if health is good
				}
				else if (e->getType() != CYCLOPE)
				{
					if (e->isAlive())
					{
						found = true;
						attack(e);
					}
					else if (getHelth() < 100)
					{
						eat(e);
					}
				}
				else if (e->getType() == CYCLOPE)
				{
					if (e->isAlive())
					{
						found = true;
						group(e);
						addFriend(e);
					}
					else if ((getHelth() < 100) && (e->getFood() > 0))
					{
						eat(e);
						found = true;
					}
				}
				else if ((getHelth() < 100) && (e->getType() == TREE) && (e->getFood() > 0))
				{
					eat(e);
					found = true;
				}
			}
		}
		// verifies if someone is asking for help
		if (hasMessage())
		{
			ElementMessage *msg = getMessage();
			if (this != msg->getSender())
			{
				if ((msg->getContent().compare("help") == 0))
				{
					helpsTo = msg->getSender();
					string t = "I'm going to help ";
					t += Tools::intToString(helpsTo->getId());
					setTalk(t);
					found = true;
				}
				else if ((msg->getContent().compare("support") == 0))
				{
					if ((!isUnderAttack()) && (getHelth() > 30) && (behavior != ATTACK))
					{
						helpsTo = msg->getSender();
						found = true;
						string t = "Giving support to ";
						t += Tools::intToString(helpsTo->getId());
						setTalk(t);
					}
				}
			}
		}
		if (!found)
		{
			askForSupport = false;
			askForHelp = false;
			walk();
		}
	}
	else
	{
		goTo(helpsTo);
		if (isAround(ELEMENT, helpsTo))
		{
			string t = "I found you, ";
			t += Tools::intToString(helpsTo->getId());
			setTalk(t);
			helpsTo = NULL;
		}
		Vision *vision = getVision();
		Element *e = NULL;
		while (((e = vision->next(ELEMENT)) != NULL) && (helpsTo != NULL))
		{
			if (e == helpsTo)
			{
				string t = "I found you, ";
				t += Tools::intToString(helpsTo->getId());
				setTalk(t);
				helpsTo = NULL;
			}
		}
		clearMessages();
	}
}

// SUB-BEHAVIOR IMPLEMENTATION *******************************

void Cyclope::walk()
{
	if (randomCounter > 4)
	{
		randomCounter = 0;
		randomWalk();
	}
	behavior = WALK;
	int dir = getDirection();
	if (!move(dir))
	{
		switch (dir)
		{
		case UP:
			move(LEFT);
			break;
		case LEFT:
			move(DOWN);
			break;
		case DOWN:
			move(RIGHT);
			break;
		case RIGHT:
			move(UP);
			break;
		}
	}
	randomCounter++;
}

void Cyclope::randomWalk()
{
	behavior = WALK;
	move((rand() % 4) * 2);
}

void Cyclope::eat(Element *e)
{
	behavior = EAT;
	if (isAround(ELEMENT, e))
	{
		Element::eat(e);
	}
	else
	{
		goTo(e);
	}
}

void Cyclope::attack(Element *e)
{
	behavior = ATTACK;
	if (isAround(ELEMENT, e))
	{
		Element::attack(e);
	}
	else
	{
		goTo(e);
	}
}

void Cyclope::group(Element *e)
{
	behavior = GROUP;
	if (!isAround(ELEMENT, e))
	{
		goTo(e);
	}
	else
	{
		walk();
	}
}

void Cyclope::runAway(Element *e)
{
	behavior = RUNAWAY;
	bool moved = false;
	if (e->getX() < getX())
	{
		if (!move(RIGHT))
		{
			if (e->getY() < getY())
			{
				moved = move(DOWN);
			}
			else
			{
				moved = move(LEFT);
			}
		}
		else
		{
			moved = true;
		}
	}
	else if (e->getX() > getX())
	{
		if (!move(LEFT))
		{
			if (e->getY() < getY())
			{
				moved = move(DOWN);
			}
			else
			{
				moved = move(UP);
			}
		}
		else
		{
			moved = true;
		}
	}
	else if (e->getY() < getY())
	{
		if (!move(DOWN))
		{
			if (!move(LEFT))
			{
				moved = move(RIGHT);
			}
			else
			{
				moved = true;
			}
		}
		else
		{
			moved = true;
		}
	}
	else if (e->getY() > getY())
	{
		if (!move(UP))
		{
			if (!move(RIGHT))
			{
				moved = move(LEFT);
			}
			else
			{
				moved = true;
			}
		}
		else
		{
			moved = true;
		}
	}
	if (!moved)
	{
		randomWalk();
	}
}

void Cyclope::goTo(Element *e)
{
	bool moved = false;
	int ordem = (rand() % 2);
	if (ordem == 0)
	{
		moved = goToHorizontal(e);
		if (!moved)
		{
			moved = goToVertical(e);
		}
	}
	else if (ordem == 1)
	{
		moved = goToVertical(e);
		if (!moved)
		{
			moved = goToHorizontal(e);
		}
	}
	if (!moved)
	{
		randomWalk();
	}
}

bool Cyclope::goToHorizontal(Element *e)
{
	bool moved = false;
	if (e->getX() < getX())
	{
		if (!move(LEFT))
		{
			if (e->getY() < getY())
			{
				moved = move(UP);
			}
			else
			{
				moved = move(DOWN);
			}
		}
		else
		{
			moved = true;
		}
	}
	else if (e->getX() > getX())
	{
		if (!move(RIGHT))
		{
			if (e->getY() < getY())
			{
				moved = move(UP);
			}
			else
			{
				moved = move(DOWN);
			}
		}
		else
		{
			moved = true;
		}
	}
	return moved;
}

bool Cyclope::goToVertical(Element *e)
{
	bool moved = false;
	if (e->getY() < getY())
	{
		if (!move(UP))
		{
			if (!move(RIGHT))
			{
				moved = move(LEFT);
			}
			else
			{
				moved = true;
			}
		}
		else
		{
			moved = true;
		}
	}
	else if (e->getY() > getY())
	{
		if (!move(DOWN))
		{
			if (!move(LEFT))
			{
				moved = move(RIGHT);
			}
			else
			{
				moved = true;
			}
		}
		else
		{
			moved = true;
		}
	}
	return moved;
}

int Cyclope::benefit()
{
	int enemies = 0;
	int cyclops = 0;
	Vision *vision = getVision();
	vision->reset(ELEMENT);
	Element *e = NULL;
	while ((e = vision->next(ELEMENT)) != NULL)
	{
		if (e->getType() == CYCLOPE)
		{
			cyclops++;
		}
		else if (e->isCreature() && e->isAlive())
		{
			enemies++;
		}
	}
	e = getAround(ELEMENT, LEFT);
	if (e != NULL)
	{
		if (e->getType() == CYCLOPE)
		{
			cyclops++;
		}
		else if (e->isCreature() && e->isAlive())
		{
			enemies++;
		}
	}
	e = getAround(ELEMENT, RIGHT);
	if (e != NULL)
	{
		if (e->getType() == CYCLOPE)
		{
			cyclops++;
		}
		else if (e->isCreature() && e->isAlive())
		{
			enemies++;
		}
	}
	e = getAround(ELEMENT, BACK);
	if (e != NULL)
	{
		if (e->getType() == CYCLOPE)
		{
			cyclops++;
		}
		else if (e->isCreature() && e->isAlive())
		{
			enemies++;
		}
	}
	return cyclops - enemies;
}

void Cyclope::addFriend(Element *e)
{
	if ((e != this) && (e != NULL))
	{
		bool tem = false;
		unsigned int i = 0;
		while ((!tem) && (i < friends.size()))
		{
			tem = (e->getId() == friends[i]->getId());
			i++;
		}
		if (!tem)
		{
			friends.push_back(e);
			string t = "oi ";
			t += Tools::intToString(e->getId());
			setTalk(t);
			Cyclope *c = (Cyclope *)e;
			c->addFriend(this);
		}
	}
}

void Cyclope::talkToFriends(string text)
{
	for (unsigned int i = 0; i < friends.size(); i++)
	{
		if (friends[i] != NULL)
		{
			friends[i]->sendMessage(this, text);
		}
	}
}

string Cyclope::toString()
{
	string strComportamento = Element::toString() + " ";
	switch (behavior)
	{
	case RUNAWAY:
		strComportamento += "RUNAWAY";
		break;
	case EAT:
		strComportamento += "EAT";
		break;
	case ATTACK:
		strComportamento += "ATTACK";
		break;
	case GROUP:
		strComportamento += "GROUP";
		break;
	case TURN:
		strComportamento += "TURN";
		break;
	case WALK:
		strComportamento += "WALK";
		break;
	}
	return strComportamento;
}

Cyclope::~Cyclope()
{
}
