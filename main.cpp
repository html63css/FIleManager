#include <iostream>
#include <Windows.h>
#include "function.h"

int numERROR = 0;
wchar_t ATTRIBUTES[300] = { '\0' };
wchar_t LOCATION[200] = { '\0' };
list <wchar_t*> CATALOG;
list <wstring> CATALOG_COMMAND= {L"q",				//+ Выход
								L"cd",				//+ Переход
								L"ls",				//+ Содержание
								L"touch",			//+ создать
								L"rm",				//- удалить
								L"mkdir",			//+ Создать дир.
								L"rmdir",			//- удалить дир.
								L"help",			//+ помощь
								L"clear"};			//+ очистить консоль
int main()
{
	setlocale(0, "rus_rus.866");
	wprintf(L"\t\tКурсовая работа студента группы 9395\n\t\tАвтор: ШУМЕЙКО АЛЕКСАНДР\n----------------------------------------\nДля открытия справки введите help\n");
	lstrcatW(LOCATION, L"D:\\\TEST\\*");
	wchar_t COMMAND[100] = { '\0' };
	while (1)
	{
		consLocation(LOCATION);
		wscanf(L"%ls", COMMAND);
		fgetws(ATTRIBUTES,200,stdin);
		if (ATTRIBUTES[1] == '\\')
		{
			wchar_t buf[300] = { '\0' };
			lstrcatW(buf, LOCATION);
			for (wchar_t& element : buf)
				if (element == '*') 
				{
					element = '\0';
					break;
				}
			lstrcatW(buf, &ATTRIBUTES[2]);
			for (int i = 0; buf[i] != '\0'; ++i)
				ATTRIBUTES[i+1] = buf[i];
		}
		ATTRIBUTES[lstrlenW(ATTRIBUTES) - 1] = '\0';
		for (auto element: CATALOG_COMMAND)
		{
			if (!lstrcmpW(&element[0],COMMAND))
			{
				if (ATTRIBUTES[1] == '\0') utility(COMMAND);
				else utility(COMMAND, 1);
				break;
			}
			else
			{
				numERROR = 1;
			}
		}
		if (numERROR != 0) consError(numERROR);
		for (auto& element : COMMAND) element = '\0';
		for (auto& element : ATTRIBUTES) element = '\0';
	}
	return 0;
}