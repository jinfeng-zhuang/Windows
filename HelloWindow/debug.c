#include "app.h"

#define CONFIG_DEBUG_BUFFER_SIZE	1024

static char buf[CONFIG_DEBUG_BUFFER_SIZE];

static FILE *file = NULL;

int debug_add(char *prefix, char *func, int linenum, const char *fmt, ...)
{
	va_list args;

	if (NULL == file) {
		file = fopen("log.txt", "w");
		if (NULL == file) {
			return -1;
		}
	}

	sprintf(buf, "[%s] %s %d: ", prefix, func, linenum);

	va_start(args, fmt);
	vsnprintf(&buf[strlen(buf)], sizeof(buf), fmt, args);
	va_end(args);

	buf[strlen(buf)] = '\n';
	buf[strlen(buf) + 1] = '\0';

	fwrite(buf, sizeof(char), strlen(buf), file);
	fflush(file);

	return strlen(buf);
}

int debug_close(void)
{
	fclose(file);

	return 0;
}