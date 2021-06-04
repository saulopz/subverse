#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "Enjin.h"
#include "Globals.h"
#include "Tools.h"
#include "Vision.h"
#include "ElementMessage.h"

class World;
class Vision;

class Element
{
private:
	// Attributes
	long int id;
	int posX, posY;
	World *world;
	Image *image[16];
	Image *myImage;
	Image *meat;
	Image *dead;
	bool moved;
	string name;
	string talk;
	int timerTalk;
	int maxTimerTalk;
	int turnGame;
	int type;
	int direction;
	int timer;
	int maxTime;
	int worldSecound;
	int visionRange;
	int helth;
	int counterHelth;
	int maxCounterHelth;
	int strong;
	int counterAttack;
	int counterEat;
	int maxCounterEat;
	int maxCounterAttack;
	Vision *vision;
	bool walking;
	bool working;
	bool eraseMe;
	bool live;
	int counterDead;
	int maxCounterDead;
	int food;
	int counterFood;
	int maxCounterFood;
	bool underAttack;
	int maxCounterUnderAttack;
	int counterUnderAttack;
	bool creature;
	Element *attacker;
	// Private Methods
	void loadImages(string);
	void incTimer();
	void incCounterFood();
	void incCounterAttack();
	void incCounterUnderAttack();
	void incCounterEat();
	void incCounterDead();
	void incCounterHelth();
	void incFood();
	void decTimerTalk();
	void reloadVision();
	void resetTime();

	vector<ElementMessage *> messages;

public:
	// Public Methods
	Element(World *, string, int);
	virtual string toString();
	bool isWalking();
	bool isWorking();
	bool isStep();
	bool isAlive();
	bool isCreature();
	bool isUnderAttack();
	bool isAttack();
	bool isToErase();
	bool attack(Element *);
	bool move(int);
	bool eat(Element *);
	bool areAttackedBy(Element *);
	void setTurnGame(int tg);
	void setCreature(bool);
	void setWalking(bool);
	void setWorking(bool);
	void setX(int);
	void setY(int);
	void setMaxTime(int);
	void setVisionRange(int);
	void setVision(Vision *);
	void setFood(int);
	void setHelth(int);
	void incHelth();
	void decHelth();
	void setStrong(int);
	void setAttacker(Element *);
	void setTimerTalk(int t);
	void setTalk(string t);
	long int getId();
	int getTurnGame();
	int isEatenBy(Element *);
	int getStrong();
	int getHelth();
	int getFood();
	int getMaxTime();
	int getDirection();
	int getAddX();
	int getAddY();
	int getX();
	int getY();
	int getType();
	int getTime();
	int getVisionRange();
	string getTalk();
	bool isAround(int t, Element *e);
	Element *getAround(int t, int dir);
	Element *getAttacker();
	Vision *getVision();
	// World* getWorld();
	string getName();
	void setDirection(int);
	virtual void run();
	virtual void execute();
	virtual Image *getImage();
	virtual ~Element();

	World *getWorld();

	// Mensagens
	bool hasMessage();
	ElementMessage *getMessage();
	int messagesSize();
	void clearMessages();
	void sendMessage(Element *sender, string content);
};

#endif /* ELEMENT_H_ */
