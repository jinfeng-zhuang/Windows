#include <zstack/log.h>

#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>

#define USE_FILE_LOG

#define BUFFER_SIZE		500

static FILE *fp = NULL;
static char log_line[BUFFER_SIZE];

void log_init(void)
{
	//AllocConsole();
	//freopen_s(&fp, "CONOUT$", "w", stdout);
    fopen_s(&fp, "D://log.txt", "w");
}

void log_file(enum log_level_e lvl, const char *fmt, ...)
{
    va_list args;

    memset(log_line, 0, BUFFER_SIZE);

    va_start(args, fmt);
    vsnprintf(log_line, BUFFER_SIZE, fmt, args);
    va_end(args);

    fwrite(log_line, sizeof(unsigned char), strlen(log_line), fp);
    fflush(fp);
}

void log_close(void)
{
    fclose(fp);
}
