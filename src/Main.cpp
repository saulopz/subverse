#include "World.h"

int main(int argv, char *argc[])
{
	World *world = new World("subverse.map");
	world->run();
	return 0;
}
