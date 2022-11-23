#ifndef __PCHAR_IOCTL_H
#define __PCHAR_IOCTL_H

#include <linux/ioctl.h>

typedef struct pchar_info {
    short size;
    short len;
    short avail;
}info_t;

// ioctl cmd (32-bit) = type (8-bit) + seq num (8-bit) + direction (2-bit) + size
#define FIFO_CLEAR      _IO('x', 1)
#define FIFO_GET_INFO   _IOR('x', 2, info_t*)
//#define FIFO_RESIZE     _IOW('x', 3, long)

#endif