#pragma warning (disable : 4996)
#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include "function.h"
#include <iostream>
#include <vector>
#define SIZE_HELP 1000
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
/*wchar_t* strdup(wchar_t* s)
{
	wchar_t* r;
	int  i,l(0);
	for (int j = 0; s[j] != '\0'; j++) ++l;
	r = new wchar_t[l];
	for (i = 0; i < l; i++) r[i] = s[i];
	r[l] = 0;
	return r;
}*/
void consLocation(wchar_t* str)
{
	SetConsoleTextAttribute(console, (WORD)((0 << 4) | 9));
	wprintf_s(L"%s$ ", str);
	SetConsoleTextAttribute(console, (WORD)((0 << 4) | 15));
}
void consError(int err)
{
	SetConsoleTextAttribute(console, (WORD)((0 << 4) | 4));
	wprintf(L"Ошибка: ");
	switch (err)
	{
	case 1:
		wprintf(L"нет такой команды\n");
		break;
	case 2:
		wprintf(L"не удалось открыть данную дерикторию\n");
		break;
	case 3:
		wprintf(L"команда help не требует дополнительных атрибутов\n");
		break;
	case 4:
		wprintf(L"нельзя сделать шаг назад из данной директории\n");
		break;
	case 5:
		wprintf(L"нужно ввести название файла\n");
		break;
	case 6:
		wprintf(L"невозможно создать файл\n");
		break;
	case 7:
		wprintf(L"нужно ввести название директории\n");
		break;
	case 8:
		wprintf(L"команда clear вызывается без дополнительных параметров\n");
		break;
	default:
		wprintf(L"Неизвестная ошибка\n");
	}
	SetConsoleTextAttribute(console, (WORD)((0 << 4) | 15));
}
void utility(wchar_t* cmd, bool atr)
{
	numERROR = 0;
	if (!lstrcmpW(cmd, L"q")) exit(0);
	if (!lstrcmpW(cmd, L"cd")) 
	{
		if (atr) cd();
	}
	if (!lstrcmpW(cmd, L"ls"))
	{
		ls(atr);
	}
	if (!lstrcmpW(cmd, L"mkdir"))
	{
		if (atr) mkdir();
		else numERROR = 7;
	}
	//if (!lstrcmpW(cmd, L"rm"))
	//if (!lstrcmpW(cmd, L"rm"))
	if (!lstrcmpW(cmd, L"clear"))
	{
		if (!atr)
		{
			system("cls");
		}
		else
		{
			numERROR = 8;
		}
	}
	if (!lstrcmpW(cmd, L"touch"))
	{
		if (atr) touch();
		else numERROR = 5;
	}
	if (!lstrcmpW(cmd, L"help"))
	{
		if (!atr)
		{
			FILE* help;
			if ((help = fopen("help.mk", "r")) != NULL)
			{
				const int size = 1374*2+1;
				char buf[size] = { '\0' };
				fscanf(help, "%1[^~?]", buf);
				wchar_t buffer_wchar[size/2+1] = { '\0' };
				MultiByteToWideChar(CP_UTF8, 0, buf, -1, buffer_wchar, strlen(buf));
				wprintf(L"%ls\n", buffer_wchar);
				fclose(help);
			}
			else
			{
				wprintf(L"Файл не с содержанием описания функционала не открылся\n");
			}
		}
		else
		{
			numERROR = 3;
		}
	} 
}
void ls(bool atr)
{
	WIN32_FIND_DATA FindFileData;
	if (atr)
		lstrcat(ATTRIBUTES,L"*");
	HANDLE hf = atr ? FindFirstFile(&ATTRIBUTES[1], &FindFileData) : FindFirstFile(LOCATION, &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			//CATALOG.push_back(strdup(FindFileData.cFileName));
			wprintf(L"%s\n", FindFileData.cFileName);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	else
	{
		numERROR = 2;
	}
}
void cd()
{
	if (lstrcmpW(&ATTRIBUTES[1],L"../") == 0 && !( lstrcmp(LOCATION,L"D:\\*") == 0 || lstrcmp(LOCATION,L"C:\\*") == 0 || lstrcmp(LOCATION, L"..\\*") == 0 || lstrcmp(LOCATION, L".\\*") == 0))
	{
		int flage = 0;
		for (int i = lstrlenW(LOCATION) - 1; !(flage == 1 && LOCATION[i] == '\\'); --i)
		{
			if (LOCATION[i] == '\\') ++flage;
			LOCATION[i] = '\0';
		}
		lstrcatW(LOCATION, L"*");
	}
	else if (lstrcmpW(&ATTRIBUTES[1], L"../") == 0 && (lstrcmp(LOCATION, L"D:\\*") == 0 || lstrcmp(LOCATION, L"C:\\*") == 0 || lstrcmp(LOCATION, L"..\\*") == 0 || lstrcmp(LOCATION, L".\\*") == 0))
	{
		numERROR = 4;
		return;
	}
	else if (lstrcmp(&ATTRIBUTES[1], L"D:") == 0 || lstrcmp(&ATTRIBUTES[1], L"C:") == 0)
	{
		lstrcpy(LOCATION,&ATTRIBUTES[1]);
		lstrcatW(LOCATION, L"\\*");
	}
	else
	{
		WIN32_FIND_DATA FindFileData = {'\0'};
		HANDLE hf = FindFirstFile(&ATTRIBUTES[1], &FindFileData);
		if (hf != INVALID_HANDLE_VALUE)
		{
			lstrcpyW(LOCATION, &ATTRIBUTES[1]);
			lstrcatW(LOCATION, L"\\*");
		}
		else
		{
			numERROR = 2;
		}

	}
}
void touch()
{
	wchar_t buf[400] = { '\0' };
	if ((ATTRIBUTES[1] == 'C' || ATTRIBUTES[1] == 'D') && ATTRIBUTES[2] == ':')
	{
		lstrcpyW(buf,&ATTRIBUTES[1]);
	}
	else
	{
		lstrcpyW(buf, LOCATION);
		buf[lstrlenW(buf) - 1] = '\0';
		lstrcatW(buf, &ATTRIBUTES[1]);
	}
	HANDLE FileHandle = CreateFileW(buf, 0, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (FileHandle == INVALID_HANDLE_VALUE)
	{
		numERROR = 6;
	}
	CloseHandle(FileHandle);
}
void mkdir()
{
	wchar_t buf[400] = { '\0' };
	if ((ATTRIBUTES[1] == 'C' || ATTRIBUTES[1] == 'D') && ATTRIBUTES[2] == ':')
	{
		lstrcpyW(buf, &ATTRIBUTES[1]);
	}
	else
	{
		lstrcpyW(buf, LOCATION);
		buf[lstrlenW(buf) - 1] = '\0';
		lstrcatW(buf, &ATTRIBUTES[1]);
	}
	if (CreateDirectoryW(buf, NULL) == 0)
	{
		numERROR = 6;
	}
}
