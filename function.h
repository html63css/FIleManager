#pragma once
#include <string.h>
#include <list>
#pragma warning (disable : 4996)

using namespace std;
extern int numERROR;
extern wchar_t ATTRIBUTES[300];
extern wchar_t LOCATION[200];
extern list <wchar_t*> CATALOG;

//void clearCATALOG(void);
//wchar_t* strdup(wchar_t*);
void consLocation(wchar_t*);
void consError(int);
void utility(wchar_t*,bool = 0);
void ls(bool = 0);
void cd(void);
void touch(void);
void mkdir(void);