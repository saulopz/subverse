#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>
#include <map>
#include "Singleton.h"

#define uint unsigned int

#define JOYBUTTON_TRIANGLE 0
#define JOYBUTTON_BALL 1
#define JOYBUTTON_X 2
#define JOYBUTTON_SQUARE 3
#define JOYBUTTON_LEFT_1 4
#define JOYBUTTON_RIGHT_1 5
#define JOYBUTTON_LEFT_2 6
#define JOYBUTTON_RIGHT_2 7
#define JOYBUTTON_SELECT 8
#define JOYBUTTON_START 9
#define JOY_UP 10
#define JOY_RIGHT 11
#define JOY_DOWN 12
#define JOY_LEFT 13
#define JOY_MAX_EVENTS 14
#define JOY_MAX_BUTTONS 10

#define CELL_SIZE 50

#define MAX_MESSAGES 30

#define DOWN 0
#define RIGHT 2
#define UP 4
#define LEFT 6
#define DOWN_RIGHT 8
#define DOWN_LEFT 10
#define UP_RIGHT 12
#define UP_LEFT 14

#define FRONT 1
#define BACK 3
#define FRONT_RIGHT 9
#define FRONT_LEFT 11
#define BACK_RIGHT 13
#define BACK_LEFT 15

#define VOID 0
#define AVATAR 1
#define CYCLOPE 2
#define SPIDER 3
#define BAT 4

#define FIRE 50
#define TREE 51

#define ADOBE 100
#define LITTLELAWN 101
#define GROUND 102
#define ROCKS 103
#define LAWN 104

#define WALL 200

#define WATER 300

#define NONE -1
#define LAND 0
#define ELEMENT 1
#define WORLD 3

#define IMAGES_DIR "midia/img"

using namespace std;

#endif /* GLOBALS_H_ */
