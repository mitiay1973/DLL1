#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

	switch (fdwReason)
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
	return TRUE;
}

extern  __declspec(dllimport) int MyFunc();

int MyFunc()
{
	system("chcp 1251>nul");
	DWORD d;
	DWORD d1;
	DWORD a;
	HANDLE OTV = CreateFile(L"OTV.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL запись
	//GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0 создание

	HANDLE user = CreateFile(L"Users.csv", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	/*GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL запись */
	//GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0 создание
	if (user == INVALID_HANDLE_VALUE) //Проверка неоткрывается ли файл
	{
		MessageBox(NULL, L"Ошибка, нельзя открыть файл", L"Оповещение", MB_OK);
		return;
	}
	DWORD countFileSymbols;
	LPCSTR argumentsFromFile = calloc(4000, sizeof(CHAR));
	if (!ReadFile(user, argumentsFromFile, 4000, &countFileSymbols, NULL)) //Проверка на првильность чтения данных
	{
		MessageBox(NULL, L"Возникла ошибка при чтении данных!", L"Оповещение", MB_OK);
		return 0;
	}
}