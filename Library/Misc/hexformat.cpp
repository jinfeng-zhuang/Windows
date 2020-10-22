#pragma warning(disable:4996)

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* return formated bytes */
int hexformat(unsigned char *dst, unsigned int dstlen, unsigned char *src, unsigned int srclen)
{
    uint32_t i, j;
    uint32_t line_num;
    uint32_t last_bytes;

    line_num = srclen / 16;
    last_bytes = srclen % 16;
    
    if (NULL == dst) {
        return -1;
    }

    dst[0] = '\0';

    for (i = 0; i < line_num; i++) {
        sprintf(&dst[strlen(dst)], "%08x: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
            i * 16,
            src[i * 16 + 0],
            src[i * 16 + 1],
            src[i * 16 + 2],
            src[i * 16 + 3],
            src[i * 16 + 4],
            src[i * 16 + 5],
            src[i * 16 + 6],
            src[i * 16 + 7],
            src[i * 16 + 8],
            src[i * 16 + 9],
            src[i * 16 + 10],
            src[i * 16 + 11],
            src[i * 16 + 12],
            src[i * 16 + 13],
            src[i * 16 + 14],
            src[i * 16 + 15]);
    }

    if (last_bytes) {
        sprintf(&dst[strlen(dst)], "%08x: ", i * 16);
        for (j = 0; j < last_bytes; j++) {
            sprintf(&dst[strlen(dst)], "%02x ", src[i * 16 + j]);
        }
        sprintf(&dst[strlen(dst)], "\n");
    }

    printf("%s\n", dst);
    
    return 0;
}
