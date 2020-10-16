#include <Windows.h>
#include <stdio.h>

extern void serial_port_list(void);

int main(int argc, char *argv[])
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    serial_port_list();

    return 0;
}
