#include "Tools.h"
#include <malloc.h>

char *Tools::intToString(int d)
{
	char *aux = (char *)malloc(255 * sizeof(char));
	sprintf(aux, "%d", d);
	return aux;
}

int Tools::c_strToInt(char *s)
{
	int out;
	sscanf(s, "%d", &out);
	return out;
}

int Tools::stringToInt(string s)
{
	char *aux = (char *)malloc(255 * sizeof(char));
	strcpy(aux, s.c_str());
	return c_strToInt(aux);
}
