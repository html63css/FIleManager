#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include <list>
#include <Windows.h>

using namespace std;

extern int numERROR;
extern wchar_t ATTRIBUTES[300];
extern wchar_t LOCATION[200];

void consLocation(wchar_t*);
void consError(int);
void utility(wchar_t*,bool = 0);
void ls(bool = 0);
void cd(void);
void touch(void);
void mkdir(void);
void rm(void);
void rmdir(void);
void help(void);