#include "Spider.h"
#include "World.h"
#include <stdlib.h>

Spider::Spider(World *w) : Element(w, "spider", SPIDER)
{
}

void Spider::execute()
{
	Vision *vision = getVision();
	bool found = false;
	Element *e = NULL;
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
			else if ((e->getType() == CYCLOPE) && e->isCreature() && e->isAlive())
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
			if ((front->getType() != SPIDER) && (front->isCreature()))
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
	else
	{
		int dir = getDirection();
		if (!move(dir))
		{
			switch (dir)
			{
			case UP:
				setDirection(LEFT);
				break;
			case LEFT:
				setDirection(DOWN);
				break;
			case DOWN:
				setDirection(RIGHT);
				break;
			case RIGHT:
				setDirection(UP);
				break;
			}
		}
	}
}

Spider::~Spider()
{
}
