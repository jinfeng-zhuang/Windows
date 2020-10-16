#pragma once

#define PRINT(fmt, ...) \
  printf(fmt, ##__VA_ARGS__)

#define TRACE(fmt, ...) \
  printf("TRACE: %s:%d: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define EXCEPTION(fmt, ...) \
  printf("EXCEPTION: %s:%d: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
