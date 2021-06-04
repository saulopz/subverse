#ifndef CONFIG_H
#define CONFIG_H

#include <thread>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MSG_NULL 0
#define MSG_REQUEST 1
#define MSG_RESPONSE 2
#define MSG_INFO 3

#define MSG_TYPE_NULL 0
#define MSG_TYPE_CHAR 1
#define MSG_TYPE_STRING 2
#define MSG_TYPE_INT 3
#define MSG_TYPE_DOUBLE 4

using namespace std;

#endif /* CONFIG_H */
