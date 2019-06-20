#include <Windows.h>

extern int MyButtonRegister(HINSTANCE hInstance);

void CustomWindowClassesInit(HINSTANCE hInstance)
{
	MyButtonRegister(hInstance);
}
