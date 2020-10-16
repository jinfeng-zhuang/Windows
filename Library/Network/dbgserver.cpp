#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "socket.h"

struct package {
    unsigned short cmd;
    unsigned short len;
    unsigned int size;
    unsigned int addr;
    unsigned int count;
    unsigned char data[1];
};

#define GET_VIDEO_DEBUG_INFO_BASE	 0xBADBAD00
#define GET_VIDEO_DEBUG_INFO_AVSYNC	(GET_VIDEO_DEBUG_INFO_BASE + 1)
#define GET_VIDEO_DEBUG_INFO_FORMAT	(GET_VIDEO_DEBUG_INFO_BASE + 2)
#define GET_VIDEO_DEBUG_INFO_FRAMEQ	(GET_VIDEO_DEBUG_INFO_BASE + 3)
#define GET_VIDEO_DEBUG_INFO_PRINTSET	(GET_VIDEO_DEBUG_INFO_BASE + 5)
#define GET_VIDEO_DEBUG_INFO_PRINTPARSE	(GET_VIDEO_DEBUG_INFO_BASE + 6)
#define GET_VIDEO_DEBUG_INFO_PRINTMSGADDR	(GET_VIDEO_DEBUG_INFO_BASE + 8)
#define GET_VIDEO_DEBUG_INFO_FWPRINTADDR	(GET_VIDEO_DEBUG_INFO_BASE + 9)
#define GET_VIDEO_DEBUG_INFO_HEVCDBGADDR	(GET_VIDEO_DEBUG_INFO_BASE + 10)
#define GET_VIDEO_DEBUG_INFO_VESDESCADDR	(GET_VIDEO_DEBUG_INFO_BASE + 11)
#define STEPFRM_MODE_START (GET_VIDEO_DEBUG_INFO_BASE + 12)
#define STEPFRM_MODE_STEP (GET_VIDEO_DEBUG_INFO_BASE + 13)
#define STEPFRM_MODE_STOP (GET_VIDEO_DEBUG_INFO_BASE + 14)
#define AVSYNC_MODE_RECOVER (GET_VIDEO_DEBUG_INFO_BASE + 15)
#define AVSYNC_MODE_DISABLE (GET_VIDEO_DEBUG_INFO_BASE + 16)
#define SET_STATUS_PAUSE (GET_VIDEO_DEBUG_INFO_BASE + 17)
#define SET_STATUS_RESUME (GET_VIDEO_DEBUG_INFO_BASE + 18)
#define GET_VIDEO_DEBUG_INFO_PTSDESCADDR (GET_VIDEO_DEBUG_INFO_BASE + 19)

// refer to dbgserver "COMMAND_HANDLER _handlers[]"
#define _DBGCMD_GET_VERSION_    1
#define _DBGCMD_RD_HD_REG_      2
#define _DBGCMD_WR_HD_REG_      3
#define _DBGCMD_RD_HD_BULK_     4
#define _DBGCMD_WR_HD_BULK_     5
#define _DBGCMD_RD_HD_PORT_     6
#define _DBGCMD_WR_HD_PORT_     7
#define _DBGCMD_RD_HD_IDXPT_    8
#define _DBGCMD_WR_HD_IDXPT_    9
#define _DBGCMD_RD_I2C_REG_     10
#define _DBGCMD_WR_I2C_REG_     11
#define _DBGCMD_RD_I2C_         12
#define _DBGCMD_WR_I2C_         13
#define _DBGCMD_RD_I2C_IDXPT_   14
#define _DBGCMD_WR_I2C_IDXPT_   15
#define _DBGCMD_RD_HD_BULK_2_   16
#define _DBGCMD_WR_HD_BULK_2_   17 // Write buffer
#define _DBGCMD_ENDIAN_         18
#define _DBGCMD_RW_HD_SET_      19
#define _DBGCMD_UART_OPEN_      20
#define _DBGCMD_UART_READ_      21
#define _DBGCMD_UART_WRITE_     22
#define _DBGCMD_UART_CLOSE_     23
#define _DBGCMD_DEVICE_OPEN_    24
#define _DBGCMD_DEVICE_CLOSE_   25
#define _DBGCMD_DEVICE_IOCTL_   26
#define _DBGCMD_RD_CPU2_REG_    27 // Read register
#define _DBGCMD_WR_CPU2_REG_    28
#define _DBGCMD_I2C_START_      29
#define _DBGCMD_I2C_READBYTE_   30
#define _DBGCMD_I2C_SENDNAK_    31
#define _DBGCMD_I2C_STOP_       32
#define _DBGCMD_COMPARE_DATA_   33
#define _DBGCMD_RD_DRX_         34
#define _DBGCMD_WR_DRX_         35
#define _DBGCMD_DEVICE_READ_    36
#define _DBGCMD_DEVICE_WRITE_   37
#define _DBGCMD_DEVICE_SIZE_    38
#define _DBGCMD_BATCH_READ_     39
#define _DBGCMD_BATCH_WRITE_    40

#define BUFLEN    (1024)

static unsigned char buffer[BUFLEN];

const char* hostname = "10.86.40.84";
const short port = 65528;

const char* message = "device:2,default:1,app_video:2,video_decode:3[core],HEVC:2[drvr]";
unsigned char g_recv_buffer[BUFLEN];

char ip_str[IP_STRING_LENGTH];

static struct package *package;

static int dbgsvr_recv(int fd, unsigned char* buffer, unsigned int len)
{
    int ret;
    unsigned short continue_read;

    if ((-1 == fd) || (NULL == buffer) || (len < 2))
        return 0;

    ret = socket_recv(fd, (unsigned char*)buffer, 2);
    if (-1 == ret)
        return -1;

    continue_read = *(unsigned short*)buffer;

    printf("continue read %d bytes\n", continue_read);

    if (continue_read > len)
        continue_read = len;

    ret = socket_recv(fd, (unsigned char*)buffer, continue_read);
    if (-1 == ret)
        return -1;

    return continue_read;
}

int dbgserver_log_set(void)
{
    int fd;
    int ret;
    int len;
    unsigned int addr;

    if (-1 == network_start())
        goto client_socket_error;

    if (-1 == hostname_to_ipv4(hostname, ip_str)) {
        goto client_socket_error;
    }

    fd = socket_open();
    if (fd < 0)
        goto client_socket_error;

    printf("Connect to %s\n", ip_str);

    if (-1 == socket_connect(fd, hostname, port))
        goto client_socket_error;

    // GET LOG SETTING ADDR
    memset(buffer, 0, BUFLEN);

    package = (struct package*)buffer;
    package->cmd = 0x1b;
    package->len = 12;
    package->size = 4;
    package->addr = 0xbadbad00 + 0x05;
    package->count = 1;

    if (-1 == socket_send(fd, buffer, 4 + package->len))
        goto client_socket_error;

    memset(g_recv_buffer, 0, BUFLEN);

    ret = dbgsvr_recv(fd, (unsigned char*)g_recv_buffer, BUFLEN);
    if (-1 == ret)
        goto client_socket_error;

    addr = *(unsigned int*)g_recv_buffer;

    printf("addr = 0x%x\n", addr);

#if 0
    // SET LOG LEVEL
    memset(buffer, 0, BUFLEN);

    package = (struct package*)buffer;
    package->cmd = 0x11;
    package->len = strlen(message) + 12;
    package->size = 1;
    package->addr = addr;
    package->count = strlen(message);
    memcpy(package->data, message, strlen(message));

    if (-1 == socket_send(fd, buffer, 4 + package->len))
        goto client_socket_error;
#endif

client_socket_error:
    network_stop();
    return 0;
}

int dbgserver_es_desc_get(void)
{
    int fd;
    int ret;
    int len;
    unsigned int addr;

    if (-1 == network_start())
        goto client_socket_error;

    if (-1 == hostname_to_ipv4(hostname, ip_str)) {
        goto client_socket_error;
    }

    fd = socket_open();
    if (fd < 0)
        goto client_socket_error;

    printf("Connect to %s\n", ip_str);

    if (-1 == socket_connect(fd, hostname, port))
        goto client_socket_error;

    while (1) {
        // GET LOG SETTING ADDR
        memset(buffer, 0, BUFLEN);

        package = (struct package*)buffer;
        package->cmd = 0x1b;
        package->len = 12;
        package->size = 4;
        package->addr = 0xbadbad00 + 0x0B;
        package->count = 1;

        if (-1 == socket_send(fd, buffer, 4 + package->len))
            goto client_socket_error;

        memset(g_recv_buffer, 0, BUFLEN);

        ret = dbgsvr_recv(fd, (unsigned char*)g_recv_buffer, BUFLEN);
        if (-1 == ret)
            goto client_socket_error;

        addr = *(unsigned int*)g_recv_buffer;

        printf("addr = 0x%x\n", addr);

        Sleep(100);
    }
#if 0
    // SET LOG LEVEL
    memset(buffer, 0, BUFLEN);

    package = (struct package*)buffer;
    package->cmd = 0x11;
    package->len = strlen(message) + 12;
    package->size = 1;
    package->addr = addr;
    package->count = strlen(message);
    memcpy(package->data, message, strlen(message));

    if (-1 == socket_send(fd, buffer, 4 + package->len))
        goto client_socket_error;
#endif

client_socket_error:
    printf("end\n");
    network_stop();
    return 0;
}
