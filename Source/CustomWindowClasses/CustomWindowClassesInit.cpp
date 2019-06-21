#include <Windows.h>

extern int MyButtonRegister(HINSTANCE hInstance);
extern int EmptyBoardRegister(HINSTANCE hInstance);

void CustomWindowClassesInit(HINSTANCE hInstance)
{
	MyButtonRegister(hInstance);
	EmptyBoardRegister(hInstance);
}
