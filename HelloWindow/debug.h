#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#ifdef ERROR
#undef ERROR
#endif

#define ERROR(fmt, ...)																\
	do {																			\
		printf("[ERROR] %s %d: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);	\
		assert(false);																\
	} while (0)

#define WARN(fmt, ...) printf("[WARN] %s %d: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define INFO(fmt, ...) printf("[INFO] %s %d: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define DEBUG(fmt, ...) printf("[DEBUG] %s %d: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#endif