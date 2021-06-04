#include "World.h"

using namespace std;

World::World(std::string fileName)
{
	g = Singleton<Enjin>::getInstance();
	background = g->createImage(g->screen->w + (CELL_SIZE * 2), g->screen->h + (CELL_SIZE * 2));
	timer = new Timer();
	height = 0;
	width = 0;
	posX = 0;
	posY = 0;
	elementInfo = NULL;
	avatar = NULL;
	idIndex = 0;
	turnGame = 0;
	step = 0;

	images = new Images();
	images->add("meat");
	images->add("dead");
	images->add("avatar");
	images->add("cyclope");
	images->add("water");
	images->add("adobe");
	images->add("spider");
	images->add("ground");
	images->add("fire");
	images->add("lawn");
	images->add("littlelawn");
	images->add("rocks");
	images->add("tree");
	images->add("wall");
	images->add("bat");
	images->add("rectwhite");

	font12 = g->loadFont("midia/fonte/verdanab.ttf", 12);
	colorWhite = g->color(255, 255, 255);

	// Connection operations
	server = new Server(5050);
	if (server->startConnection())
	{
		cout << "server started at port: " << server->getPort() << endl;
	}
	server->start();
	loadWorld(fileName);
}

int World::getTurnGame()
{
	return turnGame;
}

u_long World::getNextId()
{
	idIndex++;
	return idIndex;
}

Element *World::get(Element *e, int type, int direction)
{
	Element *aux = NULL;
	switch (direction)
	{
	case DOWN_RIGHT:
		if ((e->getY() < getHeight() - 1) && (e->getX() < getWidth() - 1))
		{
			aux = get(type, e->getX() + 1, e->getY() + 1);
		}
		break;
	case DOWN_LEFT:
		if ((e->getY() < getHeight() - 1) && (e->getX() > 0))
		{
			aux = get(type, e->getX() - 1, e->getY() + 1);
		}
		break;
	case UP_RIGHT:
		if ((e->getY() > 0) && (e->getX() < getWidth() - 1))
		{
			aux = get(type, e->getX() + 1, e->getY() - 1);
		}
		break;
	case UP_LEFT:
		if ((e->getY() > 0) && (e->getX() > 0))
		{
			aux = get(type, e->getX() - 1, e->getY() - 1);
		}
		break;
	case UP:
		if (e->getY() > 0)
		{
			aux = get(type, e->getX(), e->getY() - 1);
		}
		break;
	case DOWN:
		if (e->getY() < getHeight() - 1)
		{
			aux = get(type, e->getX(), e->getY() + 1);
		}
		break;
	case LEFT:
		if (e->getX() > 0)
		{
			aux = get(type, e->getX() - 1, e->getY());
		}
		break;
	case RIGHT:
		if (e->getX() < getWidth() - 1)
		{
			aux = get(type, e->getX() + 1, e->getY());
		}
		break;
	}
	return aux;
}

bool World::move(Element *e, int direction)
{
	bool freeWay = false;
	Element *land = get(e, LAND, direction);
	if (land != NULL)
	{
		if (land->getType() < WALL)
		{
			freeWay = true;
		}
		Element *aux = get(e, ELEMENT, direction);
		if (aux != NULL)
		{
			freeWay = false;
		}
	}
	bool moved = false;
	if (freeWay)
	{
		int auxX = e->getX();
		int auxY = e->getY();
		switch (direction)
		{
		case DOWN_RIGHT:
			auxX++;
			auxY++;
			break;
		case DOWN_LEFT:
			auxX--;
			auxY++;
			break;
		case UP_RIGHT:
			auxX++;
			auxY--;
			break;
		case UP_LEFT:
			auxX--;
			auxY--;
			break;
		case UP:
			auxY--;
			break;
		case DOWN:
			auxY++;
			break;
		case RIGHT:
			auxX++;
			break;
		case LEFT:
			auxX--;
			break;
		}
		set(ELEMENT, auxX, auxY, e);
		set(ELEMENT, e->getX(), e->getY(), NULL);
		e->setX(auxX);
		e->setY(auxY);
		moved = true;
	}
	return moved;
}

void World::draw()
{
	// draw land
	for (int x = (-1); x < getScreenWidth() + 1; x++)
	{
		for (int y = (-1); y < getScreenHeight() + 1; y++)
		{
			Element *e = get(LAND, getX() + x, getY() + y);
			if (e != NULL)
			{
				// maybe I need draw only objects that are on the screen
				g->drawImage(e->getImage(), background, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE, 255);
			}
		}
	}
	// draw elements
	for (int x = (-1); x < getScreenWidth() + 1; x++)
	{
		for (int y = (-1); y < getScreenHeight() + 1; y++)
		{
			Element *e = get(ELEMENT, getX() + x, getY() + y);
			if (e != NULL)
			{
				int aux = (int)(CELL_SIZE / 2);
				int auxX = ((x + 1) * CELL_SIZE) - aux;
				int auxY = ((y + 1) * CELL_SIZE) - aux;
				if (e->isWalking() && e->isStep())
				{
					switch (e->getDirection())
					{
					case DOWN_RIGHT:
						auxY -= aux;
						auxX -= aux;
						break;
					case DOWN_LEFT:
						auxY -= aux;
						auxX += aux;
						break;
					case UP_RIGHT:
						auxY += aux;
						auxX -= aux;
						break;
					case UP_LEFT:
						auxY += aux;
						auxX += aux;
						break;
					case DOWN:
						auxY -= aux;
						break;
					case RIGHT:
						auxX -= aux;
						break;
					case UP:
						auxY += aux;
						break;
					case LEFT:
						auxX += aux;
						break;
					}
				}
				if (e == elementInfo)
				{
					g->drawImage(images->get("rectwhite0"), background, auxX + 25 - 1, auxY + 25 - 1, 255);
				}
				string talk = e->getTalk();
				if (talk.compare("") != 0)
				{
					g->drawText(talk, background, font12, auxX + 37, auxY, &colorWhite, NULL);
				}
				g->drawImage(e->getImage(), background, auxX, auxY, 255);
			}
		}
	}
	int auxX = CELL_SIZE;
	int auxY = CELL_SIZE;
	int aux = (int)(CELL_SIZE / 2);
	if (avatar != NULL)
	{
		if (avatar->isWalking() && avatar->isStep())
		{
			switch (avatar->getDirection())
			{
			case DOWN_RIGHT:
				if (((getY() > 0) && (getY() < (getHeight() - getScreenHeight()))) &&
					((getX() > 0) && (getX() < (getWidth() - getScreenWidth()))))
				{
					auxY -= aux;
					auxX -= aux;
				}
				break;
			case DOWN_LEFT:
				if (((getY() > 0) && (getY() < (getHeight() - getScreenHeight()))) &&
					((getX() > 0) && (getX() < (getWidth() - getScreenWidth()))))
				{
					auxY -= aux;
					auxX += aux;
				}
				break;
			case UP_RIGHT:
				if (((getY() > 0) && (getY() < (getHeight() - getScreenHeight()))) &&
					((getX() > 0) && (getX() < (getWidth() - getScreenWidth()))))
				{
					auxY += aux;
					auxX -= aux;
				}
				break;
			case UP_LEFT:
				if (((getY() > 0) && (getY() < (getHeight() - getScreenHeight()))) &&
					((getX() > 0) && (getX() < (getWidth() - getScreenWidth()))))
				{
					auxY += aux;
					auxX += aux;
				}
				break;
			case UP:
				if ((getY() > 0) && (getY() < (getHeight() - getScreenHeight())))
				{
					auxY += aux;
				}
				break;
			case DOWN:
				if ((getY() > 0) && (getY() < (getHeight() - getScreenHeight())))
				{
					auxY -= aux;
				}
				break;
			case LEFT:
				if ((getX() > 0) && (getX() < (getWidth() - getScreenWidth())))
				{
					auxX += aux;
				}
				break;
			case RIGHT:
				if ((getX() > 0) && (getX() < (getWidth() - getScreenWidth())))
				{
					auxX -= aux;
				}
				break;
			}
		}
	}
	g->blitImage(background, auxX, auxY, g->screen->w, g->screen->h, g->screen, 0, 0, 255);
	if (elementInfo != NULL)
	{
		string strout = elementInfo->toString();
		g->drawText(strout, g->screen, font12, 10, 10, &colorWhite, NULL);
	}
	string strDate;
	strDate += Tools::intToString(timer->getDay());
	strDate += "/";
	strDate += Tools::intToString(timer->getMonth());
	strDate += "/";
	strDate += Tools::intToString(timer->getYear());
	strDate += " ";
	strDate += Tools::intToString(timer->getHour());
	strDate += ":";
	strDate += Tools::intToString(timer->getMinute());
	strDate += ":";
	strDate += Tools::intToString(timer->getSecond());
	g->drawText(strDate, g->screen, font12, 10, g->screen->h - 20, &colorWhite, NULL);
	g->drawScreen();
}

void World::run()
{
	Element *e = NULL;
	do
	{
		for (int y = 0; y < getHeight(); y++)
		{
			for (int x = 0; x < getWidth(); x++)
			{
				e = get(LAND, x, y);
				if (e != NULL)
				{
					e->run();
					if (e->isToErase())
					{
						set(LAND, x, y, NULL);
					}
				}
				e = get(ELEMENT, x, y);
				if (e != NULL)
				{
					e->run();
					if (e->isToErase())
					{
						set(ELEMENT, x, y, NULL);
					}
				}
			}
		}
		setX(avatar->getX() - (int)(getScreenWidth() / 2));
		setY(avatar->getY() - (int)(getScreenHeight() / 2));
		incTimer();
		if (g->isMouseDown())
		{
			if (g->getMouseButton() == 1)
			{
				int mouseX = getX() + ((int)(g->getMouseX() / CELL_SIZE));
				int mouseY = getY() + ((int)(g->getMouseY() / CELL_SIZE));
				Element *eInfo = get(ELEMENT, mouseX, mouseY);
				if (eInfo != NULL)
				{
					elementInfo = eInfo;
				}
			}
		}
		draw();
		// maybe calculate FPS
		g->delay(10);
		g->updateEvents();

		// step = (step == 0) ? 1 : 0;
		// turnGame++;

		// Connection operations
		if (server->hasNewClient())
		{
			int client = server->getClient();
			cout << "Client: " << client << endl;
			proxyList.push_back(new Proxy(client));
		}
		for (u_int i = 0; i < proxyList.size(); i++)
		{
			Proxy *proxy = proxyList[i];
			if (proxy != NULL)
			{
				if (proxy->isTerminated())
				{
					proxyList.erase(proxyList.begin() + i);
				}
				else if (proxy->hasMessage())
				{
					string message = proxy->getMessage();
					cout << "[" << proxy->getSock() << "] received: " << message << endl;
					proxy->sendMessage(worldToString(message).c_str());
				}
			}
		}
	} while (!g->isKeyDown(SDLK_ESCAPE));
}

string World::worldToString(string type)
{
	if (type.find("land") != string::npos)
	{
		return landToString();
	}
	else if (type.find("element") != string::npos)
	{
		return elementToString();
	}
	return "none";
}

string World::landToString()
{
	string out = "[";
	out += Tools::intToString(getWidth());
	out += ",";
	out += Tools::intToString(getHeight());
	out += "]";
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			Element *e = get(LAND, x, y);
			if (e != NULL)
			{
				out += "(";
				out += Tools::intToString(x);
				out += ",";
				out += Tools::intToString(y);
				out += ",";
				out += Tools::intToString(e->getType());
				out += ")";
			}
		}
	}
	return out;
}

string World::elementToString()
{
	string out = "[";
	out += getTimer()->toString();
	out += "]";
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			Element *e = get(ELEMENT, x, y);
			if (e != NULL)
			{
				out += "(";
				out += Tools::intToString(x);
				out += ",";
				out += Tools::intToString(y);
				out += ",";
				out += Tools::intToString(e->getId());
				out += ",";
				out += Tools::intToString(e->getType());
				out += ",";
				out += Tools::intToString(e->isAlive());
				out += ",";
				out += Tools::intToString(e->isUnderAttack());
				out += ",";
				out += Tools::intToString(e->getStrong());
				out += ",";
				out += Tools::intToString(e->getHelth());
				out += ",";
				out += Tools::intToString(e->getFood());
				out += ",";
				out += Tools::intToString(e->getDirection());
				out += ",";
				out += Tools::intToString(e->isAttack());
				out += ")";
			}
		}
	}
	return out;
}

void World::loadWorld(std::string fileName)
{
	LoadWorld *loadWorld = new LoadWorld(fileName);
	height = loadWorld->getHeight();
	width = loadWorld->getWidth();

	Type *typeLand = new Type();
	Type *typeElement = new Type();

	for (int y = 0; y < getHeight(); y++)
	{
		Line *lineElement = new Line();
		Line *lineLand = new Line();
		for (int x = 0; x < getWidth(); x++)
		{
			Element *e;
			int iten = loadWorld->getNext(ELEMENT);
			switch (iten)
			{
			case AVATAR:
				if (avatar == NULL)
				{
					e = new Avatar(this);
					avatar = e;
					setX(x - (int)(getScreenWidth() / 2));
					setY(y - (int)(getScreenHeight() / 2));
				}
				else
				{
					e = NULL;
				}
				break;
			case CYCLOPE:
				e = new Cyclope(this);
				break;
			case FIRE:
				e = new Element(this, "fire", FIRE);
				break;
			case TREE:
				e = new Element(this, "tree", TREE);
				break;
			case WALL:
				e = new Element(this, "wall", WALL);
				break;
			case SPIDER:
				e = new Spider(this);
				break;
			case BAT:
				e = new Bat(this);
				break;
			default:
				e = NULL;
			}
			if (e != NULL)
			{
				e->setX(x);
				e->setY(y);
			}
			lineElement->x.push_back(e);

			iten = loadWorld->getNext(LAND);
			switch (iten)
			{
			case ADOBE:
				e = new Element(this, "adobe", ADOBE);
				break;
			case GROUND:
				e = new Element(this, "ground", GROUND);
				break;
			case ROCKS:
				e = new Element(this, "rocks", ROCKS);
				break;
			case LAWN:
				e = new Element(this, "lawn", LAWN);
				break;
			case LITTLELAWN:
				e = new Element(this, "littlelawn", LITTLELAWN);
				break;
			case WATER:
				e = new Element(this, "water", WATER);
				break;
			default:
				e = NULL;
			}
			if (e != NULL)
			{
				e->setX(x);
				e->setY(y);
			}
			e->setMaxTime((rand() % 4) + 10);
			lineLand->x.push_back(e);
		}
		typeElement->y.push_back(lineElement);
		typeLand->y.push_back(lineLand);
	}
	element.push_back(typeLand);
	element.push_back(typeElement);
}

Vision *World::getVision(Element *e, int range)
{
	Vision *vision = new Vision();

	if (e == NULL)
	{
		return NULL;
	}

	int elementX = e->getX();
	int elementY = e->getY();
	int direction = e->getDirection();

	for (int i = 0; i < range; i++)
	{
		for (int j = (-i - 1); j <= i + 1; j++)
		{
			int auxX = elementX;
			int auxY = elementY;
			switch (direction)
			{
			case UP_RIGHT:
			case UP_LEFT:
			case UP:
				auxX += j;
				auxY -= i - 1;
				break;
			case DOWN_RIGHT:
			case DOWN_LEFT:
			case DOWN:
				auxX += j;
				auxY += i + 1;
				break;
			case LEFT:
				auxX -= i - 1;
				auxY += j;
				break;
			case RIGHT:
				auxX += i + 1;
				auxY += j;
				break;
			}
			Element *element = get(ELEMENT, auxX, auxY);
			if (element != NULL)
			{
				vision->add(element, ELEMENT);
			}
			element = get(LAND, auxX, auxY);
			if (element != NULL)
			{
				vision->add(element, LAND);
			}
		}
	}
	return vision;
}

void World::setMusic(bool m)
{
	// if (m) play_midi(music, TRUE);
	// else stop_midi();
}

Element *World::get(int type, int x, int y)
{
	if ((x < 0) || (x >= getWidth()) || (y < 0) || (y >= getHeight()))
	{
		return NULL;
	}
	return element[type]->y[y]->x[x];
}

void World::set(int type, int x, int y, Element *e)
{
	if ((x >= 0) && (x < getWidth()) &&
		(y >= 0) && (y < getHeight()) &&
		(type >= 0) && (type < 2))
	{
		element[type]->y[y]->x[x] = e;
	}
}

int World::getWidth()
{
	return width;
}

int World::getHeight()
{
	return height;
}

int World::getX()
{
	return posX;
}

int World::getY()
{
	return posY;
}

int World::getScreenWidth()
{
	return ((int)(g->screen->w / CELL_SIZE));
}

int World::getScreenHeight()
{
	return ((int)(g->screen->h / CELL_SIZE));
}

void World::setX(int in)
{
	int temp = getScreenWidth();
	if (in > (width - temp))
	{
		posX = width - temp;
	}
	else if (in < 0)
	{
		posX = 0;
	}
	else
	{
		posX = in;
	}
}

void World::setY(int in)
{
	int temp = getScreenHeight();
	if (in > (height - temp))
	{
		posY = height - temp;
	}
	else if (in < 0)
	{
		posY = 0;
	}
	else
	{
		posY = in;
	}
}

void World::setPosition(int x_in, int y_in)
{
	setX(x_in);
	setY(y_in);
}

Timer *World::getTimer()
{
	return timer;
}

Image *World::getImage()
{
	return g->screen;
}

void World::incTimer()
{
	timer->inc();
}

World::~World()
{
	Element *e = NULL;
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			e = get(ELEMENT, x, y);
			if (e != NULL)
			{
				delete e;
			}
			e = get(LAND, x, y);
			if (e != NULL)
			{
				delete e;
			}
		}
	}
	element.clear();
	delete images;
	delete g;
	delete server;
}
