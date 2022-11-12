#include <windows.h>
#define PATH L"DLLCode.dll"
typedef int(_cdecl* MyFunc)();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	MyFunc myFun = (MyFunc)GetProcAddress(hMyDLL, "MyFunc");
		myFun();

	FreeLibrary(hMyDLL);
	return 0;
}
