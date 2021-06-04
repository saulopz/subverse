#include "Element.h"
#include "World.h"

Element::Element(World *w, string imageName, int t)
{
	name = imageName;
	world = w;
	id = world->getNextId();
	timer = 0;
	loadImages(imageName);
	walking = false;
	working = true;
	direction = DOWN;
	myImage = image[direction];
	posX = 0;
	posY = 0;
	type = t;
	visionRange = 3;
	vision = NULL;
	food = 100;
	counterFood = 20;
	maxCounterFood = 20;
	helth = 100;
	counterHelth = 500;
	maxCounterHelth = 500;
	strong = 10;
	creature = false;
	counterAttack = 20;
	maxCounterAttack = 20;
	counterEat = 20;
	maxCounterEat = 20;
	eraseMe = false;
	live = true;
	counterDead = 0;
	maxCounterDead = 100;
	underAttack = false;
	maxCounterUnderAttack = 40;
	counterUnderAttack = 40;
	attacker = NULL;
	worldSecound = world->getTimer()->getSecond();
	maxTime = 10;
	turnGame = 0;
	maxTimerTalk = 100;
	talk = "";
	moved = false;
	if ((type > 0) && (type < 50))
	{
		creature = true;
	}
}

void Element::run()
{
	int aux = world->getTimer()->getSecond();
	if (worldSecound != aux)
	{
		if (live)
		{
			worldSecound = aux;
			incTimer();

			int temp = direction;
			if (isStep() && (walking || working))
			{
				temp += 1;
			}

			Image *bmp = image[temp];
			if (!bmp)
			{
				bmp = world->images->get("void");
			}
			myImage = bmp;
		}
		else if (creature)
		{
			if (food > 0)
			{
				myImage = meat;
			}
			else
			{
				myImage = dead;
			}
		}
	}
	incCounterAttack();
	incCounterEat();
	incCounterFood();
	incCounterUnderAttack();
	incCounterDead();
	incCounterHelth();
	incFood();
	decTimerTalk();
	if (creature && live)
	{
		reloadVision();
	}
	if (!isWalking() && isAlive())
	{
		moved = false;
		execute();
	}
	if (isStep())
	{
		turnGame++;
	}
}

World *Element::getWorld()
{
	return world;
}

void Element::execute()
{
}

long int Element::getId()
{
	return id;
}

void Element::decTimerTalk()
{
	if (timerTalk > 0)
	{
		timerTalk--;
	}
}

string Element::getTalk()
{
	if (timerTalk == 0)
	{
		return "";
	}
	return talk;
}

void Element::setTalk(string t)
{
	talk = t;
	timerTalk = maxTimerTalk;
}

void Element::setTimerTalk(int t)
{
	maxTimerTalk = t;
}

void Element::incCounterHelth()
{
	if (counterHelth < maxCounterHelth)
	{
		counterHelth++;
	}
	else if (creature)
	{
		decHelth();
		counterHelth = 0;
	}
}

void Element::incCounterDead()
{
	if ((!live) && (food == 0))
	{
		counterDead++;
	}
	if (counterDead >= maxCounterDead)
	{
		eraseMe = true;
	}
}

void Element::incCounterFood()
{
	if (counterFood < maxCounterFood)
	{
		counterFood++;
	}
}

void Element::incCounterAttack()
{
	if (counterAttack < maxCounterAttack)
	{
		counterAttack++;
	}
}

bool Element::isAttack()
{
	return (counterAttack > 0);
}

void Element::incCounterUnderAttack()
{
	if (counterUnderAttack < maxCounterUnderAttack)
	{
		counterUnderAttack++;
	}
	else
	{
		attacker = NULL;
		underAttack = false;
	}
}

void Element::incCounterEat()
{
	if (counterEat < maxCounterEat)
	{
		counterEat++;
	}
}

void Element::incFood()
{
	if ((live) && (type == TREE) && (food < 100) && (counterFood == maxCounterFood))
	{
		food++;
		counterFood = 0;
	}
}

bool Element::isToErase()
{
	return eraseMe;
}

void Element::loadImages(string fileName)
{
	for (unsigned int i = 0; i < 16; i++)
	{
		string temp = fileName + Tools::intToString(i);
		image[i] = world->images->get(temp);
	}
	dead = world->images->get("dead0");
	meat = world->images->get("meat0");
}

bool Element::move(int d)
{
	bool out = false;
	if (!moved)
	{
		setDirection(d);
		if (world->move(this, d))
		{
			walking = true;
			out = true;
			moved = true;
		}
		resetTime();
	}
	return out;
}

void Element::resetTime()
{
	timer = 0;
}

void Element::setTurnGame(int tb)
{
	turnGame = tb;
}

int Element::getTurnGame()
{
	return turnGame;
}

void Element::reloadVision()
{
	if (vision != NULL)
	{
		delete vision;
	}
	vision = world->getVision(this, visionRange);
}

void Element::incTimer()
{
	timer++;
	if (timer > maxTime)
	{
		timer = 0;
		walking = false;
	}
}

bool Element::isStep()
{
	if (timer < ((int)(maxTime / 2)))
	{
		return true;
	}
	return false;
}

bool Element::isWalking()
{
	return walking;
}

bool Element::isWorking()
{
	return working;
}

bool Element::isUnderAttack()
{
	return underAttack;
}

void Element::setWalking(bool b)
{
	walking = b;
}

void Element::setWorking(bool b)
{
	working = b;
}

void Element::setMaxTime(int t)
{
	maxTime = t;
}

void Element::setVisionRange(int r)
{
	visionRange = r;
}

void Element::setFood(int f)
{
	if ((f >= 0) && (f <= 100))
	{
		food = f;
	}
}

void Element::incHelth()
{
	if (helth < 100)
	{
		helth++;
	}
}

void Element::decHelth()
{
	if ((helth > 0) && (creature))
	{
		// AVATAR INVENCIVEL
		//if (type == AVATAR) return;
		helth--;
	}
	else
	{
		walking = false;
		live = false;
		working = false;
	}
}

int Element::isEatenBy(Element *e)
{
	int foodValue = 0;
	if (isCreature())
	{
		if (!live && (food > 0))
		{
			foodValue++;
			food -= 10;
		}
	}
	else if (type == TREE)
	{
		if (food > 0)
		{
			foodValue++;
			food -= 10;
		}
	}
	return foodValue;
}

bool Element::eat(Element *e)
{
	if ((counterEat == maxCounterEat) && (helth < 100))
	{
		int foodValue = e->isEatenBy(this);
		if (foodValue > 0)
		{
			counterEat = 0;
			incHelth();
			return true;
		}
	}
	return false;
}

void Element::setCreature(bool c)
{
	creature = c;
}

void Element::setStrong(int s)
{
	if ((s >= 0) && (s <= 100))
	{
		strong = s;
	}
}

int Element::getHelth()
{
	return helth;
}

int Element::getFood()
{
	return food;
}

int Element::getStrong()
{
	return strong;
}

int Element::getTime()
{
	return timer;
}

int Element::getMaxTime()
{
	return maxTime;
}

int Element::getDirection()
{
	return direction;
}

int Element::getVisionRange()
{
	return visionRange;
}

void Element::setVision(Vision *v)
{
	vision = v;
}

Vision *Element::getVision()
{
	return vision;
}

void Element::setDirection(int dir)
{
	if ((dir >= 0) && (dir < 8))
	{
		direction = dir;
	}
}

void Element::setX(int x)
{
	posX = x;
}

void Element::setY(int y)
{
	posY = y;
}

int Element::getX()
{
	return posX;
}

int Element::getY()
{
	return posY;
}

string Element::getName()
{
	return name;
}

int Element::getType()
{
	return type;
}

bool Element::isCreature()
{
	return creature;
}

Image *Element::getImage()
{
	return myImage;
}

bool Element::areAttackedBy(Element *from)
{
	if (creature)
	{
		underAttack = true;
		attacker = from;

		int me = getStrong() + getHelth();
		int other = from->getStrong() + from->getHelth();

		if (me <= other)
		{
			decHelth();
			decHelth();
		}
		else
		{
			decHelth();
		}
		counterUnderAttack = 0;
		return true;
	}
	return false;
}

bool Element::isAlive()
{
	return live;
}

bool Element::attack(Element *who)
{
	bool success = false;
	if (counterAttack == maxCounterAttack)
	{
		if (who->areAttackedBy(this))
		{
			success = true;
			counterUnderAttack = 0;
		}
		counterAttack = 0;
	}
	return success;
}

bool Element::isAround(int t, Element *e)
{
	if ((e == getAround(t, FRONT)) ||
		(e == getAround(t, BACK)) ||
		(e == getAround(t, LEFT)) ||
		(e == getAround(t, RIGHT)) ||
		(e == getAround(t, FRONT_LEFT)) ||
		(e == getAround(t, FRONT_RIGHT)) ||
		(e == getAround(t, BACK_LEFT)) ||
		(e == getAround(t, BACK_RIGHT)))
	{
		return true;
	}
	return false;
}

Element *Element::getAround(int t, int dir)
{
	int auxDir = UP;

	switch (getDirection())
	{
	case UP:
	case UP_RIGHT:
	case UP_LEFT:
		switch (dir)
		{
		case FRONT:
			auxDir = UP;
			break;
		case BACK:
			auxDir = DOWN;
			break;
		case LEFT:
			auxDir = LEFT;
			break;
		case RIGHT:
			auxDir = RIGHT;
			break;
		case FRONT_LEFT:
			auxDir = UP_LEFT;
			break;
		case FRONT_RIGHT:
			auxDir = UP_RIGHT;
			break;
		case BACK_LEFT:
			auxDir = DOWN_LEFT;
			break;
		case BACK_RIGHT:
			auxDir = DOWN_RIGHT;
			break;
		}
		break;
	case DOWN:
	case DOWN_RIGHT:
	case DOWN_LEFT:
		switch (dir)
		{
		case FRONT:
			auxDir = DOWN;
			break;
		case BACK:
			auxDir = UP;
			break;
		case LEFT:
			auxDir = RIGHT;
			break;
		case RIGHT:
			auxDir = LEFT;
			break;
		case FRONT_LEFT:
			auxDir = DOWN_RIGHT;
			break;
		case FRONT_RIGHT:
			auxDir = DOWN_LEFT;
			break;
		case BACK_LEFT:
			auxDir = UP_RIGHT;
			break;
		case BACK_RIGHT:
			auxDir = UP_LEFT;
			break;
		}
		break;
	case LEFT:
		switch (dir)
		{
		case FRONT:
			auxDir = LEFT;
			break;
		case BACK:
			auxDir = RIGHT;
			break;
		case LEFT:
			auxDir = DOWN;
			break;
		case RIGHT:
			auxDir = UP;
			break;
		case FRONT_LEFT:
			auxDir = DOWN_LEFT;
			break;
		case FRONT_RIGHT:
			auxDir = UP_LEFT;
			break;
		case BACK_LEFT:
			auxDir = DOWN_RIGHT;
			break;
		case BACK_RIGHT:
			auxDir = UP_RIGHT;
			break;
		}
		break;
	case RIGHT:
		switch (dir)
		{
		case FRONT:
			auxDir = RIGHT;
			break;
		case BACK:
			auxDir = LEFT;
			break;
		case LEFT:
			auxDir = UP;
			break;
		case RIGHT:
			auxDir = DOWN;
			break;
		case FRONT_LEFT:
			auxDir = UP_RIGHT;
			break;
		case FRONT_RIGHT:
			auxDir = DOWN_RIGHT;
			break;
		case BACK_LEFT:
			auxDir = UP_LEFT;
			break;
		case BACK_RIGHT:
			auxDir = DOWN_LEFT;
			break;
		}
		break;
	}
	return world->get(this, t, auxDir);
}

Element *Element::getAttacker()
{
	return attacker;
}

void Element::setAttacker(Element *e)
{
	attacker = e;
}

string Element::toString()
{
	string info = getName();
	info += " [";
	info += Tools::intToString(id);
	info += "]: live ";
	info += Tools::intToString(live);
	info += " strong ";
	info += Tools::intToString(strong);
	info += " helth ";
	info += Tools::intToString(helth);
	info += " food ";
	info += Tools::intToString(food);
	return info;
}

Element::~Element()
{
	for (unsigned int i = 0; i < 8; i++)
	{
		if (image[i] != NULL)
		{
			image[i] = NULL;
		}
	}
}

// Mensagens

bool Element::hasMessage()
{
	return !messages.empty();
}

ElementMessage *Element::getMessage()
{
	if (hasMessage())
	{
		ElementMessage *m = messages[0];
		messages.erase(messages.begin());
		return m;
	}
	return NULL;
}

int Element::messagesSize()
{
	return messages.size();
}

void Element::clearMessages()
{
	messages.clear();
}

void Element::sendMessage(Element *sender, string content)
{
	if (messages.size() < MAX_MESSAGES)
	{
		ElementMessage *m = new ElementMessage(sender, content);
		messages.push_back(m);
	}
}
