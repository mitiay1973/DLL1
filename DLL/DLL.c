#include <windows.h>
#define PATH L"DLLCode.dll"
typedef int(_cdecl* MyFunction)();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	MyFunction myFun = (MyFunction)GetProcAddress(hMyDLL, "MyFunc");
	myFun();

	FreeLibrary(hMyDLL);
	return 0;
}
