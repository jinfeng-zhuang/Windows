#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

extern int debug_init(char *filename);
extern int debug_add(char *prefix, char *func, int line, const char *fmt, ...);
extern int debug_close(void);

#ifdef ERROR
#undef ERROR
#endif

#define ERROR(fmt, ...) debug_add("ERROR", __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)  debug_add("WARN",  __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define INFO(fmt, ...)  debug_add("INFO",  __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#ifdef ENABLE_DEBUG
#define DEBUG(fmt, ...) debug_add("DEBUG", __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...) do {} while(0)
#endif

#endif
