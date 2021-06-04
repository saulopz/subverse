#ifndef TOOLS_H_
#define TOOLS_H_

#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;

class Tools
{
public:
	static char *intToString(int);
	static int c_strToInt(char *);
	static int stringToInt(string);
};

#endif /* TOOLS_H_ */
