#include <windows.h>
#include <stdio.h>
#define PATH L"DLLCode.dll"
typedef int(_cdecl* MyFunc)(struct MyStruct*);
struct MyStruct
{
	char* Surname;
	char* Name;
	char* Otchestvo;
	int Age;
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	MyFunc myFun = (MyFunc)GetProcAddress(hMyDLL, "MyFunc");
	struct MyStruct* us = calloc(5000, sizeof(struct MyStruct));
		myFun(us);

	FreeLibrary(hMyDLL);
	return 0;
}
