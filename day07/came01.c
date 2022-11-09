#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<linux/videodev2.h>
#include<unistd.h>



int main (int argc, int argv[])
{
    int fd;

    //opening the Device
    fd = open("/dev/video0",O_RDWR);
    if (fd == -1)
    {
        perror("open() Failed !!!");
        exit(EXIT_FAILURE);
    }

    //cheking the capablities
    struct v4l2_capability cap;

    if(ioctl(fd,VIDIOC_QUERYCAP,&cap)<0)
    {
        printf("Error in VIDIOC_QUERYCAP");
        exit(1);
    }
    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        printf("The device does not handle single-planar video capture.\n");
        exit(1);
    }

    //set image formate
    struct v4l2_format format;
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    format.fmt.pix.width = 640;
    format.fmt.pix.height = 480;

    if(ioctl(fd, VIDIOC_S_FMT, &format) < 0)
    {
        printf("Issue in VIDIOC_S_FMT");
        exit(1);
    }

    //req the buffer
    struct v4l2_requestbuffers bufrequest;
    bufrequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufrequest.memory = V4L2_MEMORY_MMAP;
    bufrequest.count = 1;
    
    if(ioctl(fd, VIDIOC_REQBUFS, &bufrequest) < 0)
    {
        printf("Issue in VIDIOC_REQBUFS");
        exit(1);
    }
            
    close(fd);

    return 0;
}