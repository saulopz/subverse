#include "Avatar.h"
#include "World.h"
#include "Tools.h"
#include "Singleton.h"

Avatar::Avatar(World *w) : Element(w, "avatar", AVATAR)
{
	g = Singleton<Enjin>::getInstance();
	setWorking(false);
	//setMaxTime(6);
}

bool Avatar::key(int t)
{
	if (g->isKeyDown(t) || g->isKeyHeld(t))
	{
		return true;
	}
	return false;
}

void Avatar::execute()
{
	if (key(SDLK_UP) || g->isJoystickUp(0))
	{
		move(UP);
	}
	else if (key(SDLK_DOWN) || g->isJoystickDown(0))
	{
		move(DOWN);
	}
	else if (key(SDLK_RIGHT) || g->isJoystickRight(0))
	{
		move(RIGHT);
	}
	else if (key(SDLK_LEFT) || g->isJoystickLeft(0))
	{
		move(LEFT);
	}
	else if (key(SDLK_LCTRL) || g->isJoystickButtonPressed(0, JOYBUTTON_X))
	{
		Element *e = getAround(ELEMENT, FRONT);
		if (e != NULL)
		{
			attack(e);
		}
	}
	else if (key(SDLK_LALT) || g->isJoystickButtonPressed(0, JOYBUTTON_BALL))
	{
		Element *e = getAround(ELEMENT, FRONT);
		if (e != NULL)
		{
			eat(e);
		}
	}
	else if (key(SDLK_SPACE) || g->isJoystickButtonPressed(0, JOYBUTTON_TRIANGLE))
	{
		Element *e = getAround(ELEMENT, FRONT);
		if (e != NULL)
		{
			sendMessage(e, "ola");
		}
	}
}

Avatar::~Avatar()
{
}
