#ifndef WORLD_H_
#define WORLD_H_

#include "Enjin.h"
#include "Globals.h"
#include "Avatar.h"
#include "Cyclope.h"
#include "Spider.h"
#include "Bat.h"
#include "Images.h"
#include "Timer.h"
#include "LoadWorld.h"
#include "Vision.h"
#include "../com/Subcom.h"

class Line
{
public:
	vector<Element *> x;
};

class Type
{
public:
	vector<Line *> y;
};

class World
{
private:
	Server *server;
	vector<Proxy *> proxyList;

	Enjin *g;
	u_long idIndex;
	Image *background;
	vector<Type *> element;
	int posX;
	int posY;
	Element *avatar;
	Element *elementInfo;
	int height;
	int width;
	Timer *timer;
	int step;
	int turnGame;

	TTF_Font *font12;
	SDL_Color colorWhite;

	void loadWorld(string);

public:
	Images *images;

	World(string);
	Timer *getTimer();
	void incTimer();
	Image *getImage();

	u_long getNextId();
	Element *get(int, int, int);
	Element *get(Element *, int, int);
	void set(int, int, int, Element *);
	bool move(Element *, int);
	int getWidth();
	int getHeight();
	int getScreenWidth();
	int getScreenHeight();
	int getX();
	int getY();
	int getTurnGame();
	string worldToString(string);
	string landToString();
	string elementToString();
	void setMusic(bool);
	void setX(int);
	void setY(int);
	void setPosition(int, int);
	Vision *getVision(Element *, int);
	virtual void draw();
	virtual void run();
	virtual ~World();
};

#endif /* WORLD_H_ */
