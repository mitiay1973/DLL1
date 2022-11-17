#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

//__declspec(dllimport) int myFunc(LPWSTR str);
//__declspec(dllimport) void FileRead(struct person* pers);


//__declspec(dllimport) void writeToFileIvanova(struct person* current, int countCurrent);
//__declspec(dllimport) void searchSurnameIvanova(struct person* pers);

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

__declspec(dllimport) void MyFunc(struct MyStruct* us);
__declspec(dllimport) void PoiskSurName(struct MyStruct* us);
__declspec(dllimport) void writeToFile(struct MyStruct* current, int countCurrent);
__declspec(dllimport) void PoiskSurNameIv(struct MyStruct* us);
__declspec(dllimport) void writeToFileIv(struct MyStruct* current, int countCurrent);
typedef int (_cdecl* forReadData)(struct MyStruct*);
struct MyStruct
{
	char* Surname;
	char* Name;
	char* Otchestvo;
	int Age;
};
void MyFunc(struct MyStruct* us)
{
	system("chcp 1251>nul");
	HANDLE user = CreateFile(L"Users2.csv", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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
	char* Pars = strtok(argumentsFromFile, ";");
	int CR;
	for (int i = 0; i < 100; i++)
	{
		CR = i;
		us[i].Surname = Pars;
		Pars = strtok(NULL, ";\r\n");
		us[i].Name = Pars;
		Pars = strtok(NULL, ";\r\n");
		us[i].Otchestvo = Pars;
		Pars = strtok(NULL, ";\r\n");
		us[i].Age = atoi (Pars);
		Pars = strtok(NULL, ";\r\n");
	}
	CloseHandle(user);
	PoiskSurName(us);
	PoiskSurNameIv(us);
}
void PoiskSurName(struct MyStruct* us)
{
	struct MyStruct* Us = malloc(sizeof(struct MyStruct));
	struct MyStruct* poiskSurName;
	int j = 0, countOfRows = 1;
	char* forComprasion = "Тевосова";
	for (int i = 0; i < 100; i++)
	{
		if (strstr(us[i].Surname, forComprasion) != NULL)
		{
			Us[j] = us[i];
			poiskSurName = realloc(Us, (j + 2) * sizeof(struct MyStruct));
			j++;
			Us = poiskSurName;
		}
	}
	writeToFile(Us, j);
}
void writeToFile(struct MyStruct* current, int countCurrent)
{
	HANDLE OTV = CreateFile(L"OTV.csv", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
	//GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL запись
	//GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0 создание
	DWORD countFileSymbols;
	float averageAge = 0;
	char* dataForWritting = calloc(100, sizeof(char));
	for (int i = 0; i < countCurrent; i++)
	{
		sprintf(dataForWritting, "%s;%s;%s;%d\n", current[i].Surname, current[i].Name, current[i].Otchestvo, current[i].Age);
		WriteFile(OTV, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
		averageAge += current[i].Age;
	}
	averageAge /= countCurrent;
	sprintf(dataForWritting, "Средний возраст: %f", averageAge);
	WriteFile(OTV, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
	free(dataForWritting);
	CloseHandle(OTV);
}
void PoiskSurNameIv(struct MyStruct* us)
{
	struct MyStruct* Us = malloc(sizeof(struct MyStruct));
	struct MyStruct* NIV;
	int j = 0, countOfRows = 1;
	char* forComprasion = "Иванов";
	for (int i = 0; i < 100; i++)
	{
		if (strstr(us[i].Surname, forComprasion) != NULL)
		{
			Us[j] = us[i];
			NIV = realloc(Us, (j + 2) * sizeof(struct MyStruct));
			j++;
			Us = NIV;
		}
	}
	writeToFileIv(Us, j);
}
void writeToFileIv(struct MyStruct* current, int countCurrent)
{
	HANDLE OTVIv = CreateFile(L"OTVIv.csv", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL запись
	//GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0 создание
	DWORD countFileSymbols;
	float averageAge = 0;
	char* dataForWritting = calloc(100, sizeof(char));
	for (int i = 0; i < countCurrent; i++)
	{
		sprintf(dataForWritting, "%s;%s;%s;%d\n", current[i].Surname, current[i].Name, current[i].Otchestvo, current[i].Age);
		WriteFile(OTVIv, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
		averageAge += current[i].Age;
	}
	averageAge /= countCurrent;
	sprintf(dataForWritting, "Средний возраст: %f", averageAge);
	WriteFile(OTVIv, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
	free(dataForWritting);
	CloseHandle(OTVIv);
}