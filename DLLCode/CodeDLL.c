#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
BOOL WINAPI DLLMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (bAllWentWell)
		return TRUE;
	else
		return FALSE;
}
extern  __declspec(dllimport) int MyFunc();

int MyFunc()
{
	system("chcp 1251>nul");
	DWORD d;

	HANDLE OTV = CreateFile(L"OTV.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL запись
	//GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0 создание

	HANDLE Koef = CreateFile(L"Users.csv", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	/*GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL запись */
	//GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0 создание

	LPCSTR rez = "";
	if (Koef == INVALID_HANDLE_VALUE)
	{
		rez = " Ошибка открытия файла";
		WriteFile(OTV, rez, strlen(rez), &d, NULL);
		CloseHandle(OTV);
		return;
	}


	LPWSTR str= calloc(100000, 1);
		ReadFile(Koef, str, 100000, &d, NULL);
	char number[100000];
	int i = 0;
	char* istr;
	istr = strtok(str, L"\r\n");
	if (ReadFile(Koef, str, 100000, &d, NULL) == NULL)
	{
		rez = "Не удалось считать данные с файла";
		WriteFile(OTV, rez, strlen(rez), &d, NULL);
		CloseHandle(OTV);
	}
	else
	{
		while (istr != NULL)
		{

			number[i] = atof(istr);
			istr = strtok(NULL, L"\r\n");
			i++;


		}
	}
	return str;
}