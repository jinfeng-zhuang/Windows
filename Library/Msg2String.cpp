#include <Windows.h>

struct Msg2String_t {
    int uMsg;
    const char *str;
};

struct Msg2String_t Msg2String_Array[] = {
    WM_NULL,        "WM_NULL",
    WM_CREATE,      "WM_CREATE",
    WM_DESTROY,     "WM_DESTROY",
    WM_MOVE,        "WM_MOVE",
    WM_SETCURSOR,   "WM_SETCURSOR",
    WM_MOUSEMOVE,   "WM_MOUSEMOVE",
    WM_NCHITTEST,   "WM_NCHITTEST",
    WM_NCMOUSEMOVE, "WM_NCMOUSEMOVE",
    WM_CTLCOLOREDIT, "WM_CTLCOLOREDIT",
    WM_COMMAND, "WM_COMMAND",
};

const char *Msg2String(int uMsg)
{
    int i;
    
    for (i = 0; i < sizeof(Msg2String_Array) / sizeof(Msg2String_Array[0]); i++) {
        if (Msg2String_Array[i].uMsg == uMsg)
            return Msg2String_Array[i].str;
    }
    
    return "Unknown";
}
