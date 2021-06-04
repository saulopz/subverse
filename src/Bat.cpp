#include "Bat.h"
#include "World.h"
#include <stdlib.h>

Bat::Bat(World *w) : Element(w, "bat", BAT)
{
}

void Bat::execute()
{
	bool found = false;
	Vision *vision = getVision();
	Element *e = NULL;

	// if not under attack, attack and get out randomicaly
	if (isUnderAttack())
	{
		Element *front = getAround(ELEMENT, FRONT);
		if (front != NULL)
		{
			attack(getAttacker());
		}
		move((rand() % 4) * 2);
	}
	else
	{
		do
		{
			e = vision->next(ELEMENT);
			if (e != NULL)
			{
				if (getHelth() < 20)
				{
					if ((e->getType() == TREE) && (e->getFood() > 0))
					{
						found = true;
					}
					else if ((e->isCreature()) && (!e->isAlive()) && (e->getFood() > 0))
					{
						found = true;
					}
				}
				else if (isUnderAttack() && (e == getAttacker()) && e->isAlive())
				{
					found = true;
				}
				else if ((e->getType() == AVATAR) && e->isCreature() && e->isAlive())
				{
					found = true;
				}
			}
		} while ((!found) && (e != NULL));

		if (found)
		{
			Element *front = getAround(ELEMENT, FRONT);
			if ((front != NULL) && (e == front))
			{
				if ((e->getType() != CYCLOPE) && (e->getType() != AVATAR) && (e->isCreature()))
				{
					attack(e);
				}
				else if ((e->getType() == TREE) && (e->getFood() > 0))
				{
					eat(e);
				}
				else if ((e->isCreature()) && (!e->isAlive()) && (e->getFood() > 0))
				{
					eat(e);
				}
				else
				{
					move((rand() % 4) * 2);
				}
			}
			else
			{
				if (e->getX() > getX())
				{
					move(RIGHT);
				}
				else if (e->getX() < getX())
				{
					move(LEFT);
				}
				else if (e->getY() > getY())
				{
					move(DOWN);
				}
				else if (e->getY() < getY())
				{
					move(UP);
				}
			}
		}
		move((rand() % 4) * 2);
	}
}

Bat::~Bat()
{
}
