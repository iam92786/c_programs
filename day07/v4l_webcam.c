
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

static char *dev_name = "/dev/video0";
static int fd         = -1;
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static void *buffer_start   = NULL;
static size_t length        = 0;
static struct v4l2_format fmt;
        
void open_device(void);
void init_device(void);
void init_mmap(void);
void start_capturing(void);
int init_view(void);
int read_frame(void);
int init_view();
void draw_YUV();
void draw_MJPEG();
void get_pixelformat();
void close_device(void);
int sdl_filter(void *userdata, SDL_Event *event);


static void errno_exit(const char *s) 
{
        fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
        exit(EXIT_FAILURE);
}


int main(int argc, char **argv)
{

	open_device();
	init_device();

	if(init_view()) {
		close_device();
		return -1;
	}		

	SDL_SetEventFilter(sdl_filter, NULL);

	start_capturing();
	mainloop();
	stop_capturing();
	close_view();
	uninit_device();
	close_device();
	return 0;
}

//Opening the camera device
void open_device(void)
{
	//open system call check the dev path and if exists it returns the filedescritor
	if ((fd = open(dev_name, O_RDWR)) == -1) {
		printf("Cannot open '%s': %d, %s\n", dev_name);
		exit(EXIT_FAILURE);
	}
}

//Intialize the device capabilities..
void init_device(void)
{
	//structure for storing the video capabilites
	struct v4l2_capability cap;

	memset(&cap, 0, sizeof(cap));

	//calling the ioctl to check the video capabilities 
	if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
		printf("Issue in VIDIOC_QUERYCAP");

	//checking the video capture capability of the device
	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
		printf("%s is no video capture device\n", dev_name);
		exit(EXIT_FAILURE);
	}

	//checking the streaming capability of the device.
	if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
		printf("%s does not support streaming i/o\n", dev_name);
		exit(EXIT_FAILURE);
	}

	// Default to MJPEG
	memset(&fmt, 0, sizeof(fmt));
	fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;

	get_pixelformat();

	// it'll adjust to the bigger screen available in the driver
	fmt.fmt.pix.width  = 640;
	fmt.fmt.pix.height = 480;

	
	//Calling ioctl to set the Image format
	if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
		printf("Error in VIDIOC_S_FMT\n");

	//Initialize the mapping
	init_mmap();
}

// Initialize the Memory mapping
void init_mmap(void)
{
	//structure for buffer information
	struct v4l2_requestbuffers req;
	memset(&req, 0, sizeof(req));
	req.count  = 1;
	req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;

	//Calling ioctl to request the buffers
	if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1)
		printf("Issue in VIDIOC_REQBUFS\n");

	//structure for buffer storage
	struct v4l2_buffer buf;
	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;
	buf.index = 0;

	//To get the buffer l
	if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1)
		printf("Issue in VIDIOC_QUERYBUF\n");

	length = buf.length;

	//mapping the device address to our userspace address (buffer start)
	buffer_start = mmap(NULL /* start anywhere */,
			length,
			PROT_READ | PROT_WRITE /* required */,
			MAP_SHARED /* recommended */,
			fd, buf.m.offset);

	if (buffer_start == MAP_FAILED)
		printf("issue in mmap\n");
}

//Start capturing the frames..
void start_capturing(void)
{
	struct v4l2_buffer buf;
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	memset(&buf, 0, sizeof(buf));
	buf.type = type;
	buf.memory = V4L2_MEMORY_MMAP;
	buf.index = 0;

	//Queue the buffer 
	if (ioctl(fd, VIDIOC_QBUF, &buf) == -1)
		errno_exit("VIDIOC_QBUF ... !!!");

	//start streaming using STREAMON
	if (ioctl(fd, VIDIOC_STREAMON, &type) == -1)
		errno_exit("VIDIOC_STREAMON");
}

//Loop to read conitnuous frames
void mainloop(void)
{
	SDL_Event event;
	for (;;) {
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				return;
		//Infinite loop for reading the frames
		for (;;) {

			//function call to read each frame
			if (read_frame())
				break;
			// EAGAIN - continue select loop.
		}
	}
}

//Frame reading
int read_frame()
{
	struct v4l2_buffer buf;
	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;

	//Dequeue the buffer or putting the buffer in our location
	if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1) {
		printf("ioctl dqbuf is wrong !!!\n");
		switch (errno) {
			case EAGAIN:
				return 0;
			case EIO:
				/* Could ignore EIO, see spec. */
				/* fall through */
			default:
				errno_exit("VIDIOC_DQBUF");
		}
	}

	if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV)
		draw_YUV();
	else if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG)
		draw_MJPEG();

	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;

	if (ioctl(fd, VIDIOC_QBUF, &buf) == -1)
		errno_exit("VIDIOC_QBUF");

	return 1;
}

//Initializing the Display
int init_view()
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("Unable to initialize SDL\n");
		return -1;
	}

	if (SDL_CreateWindowAndRenderer(fmt.fmt.pix.width
					, fmt.fmt.pix.height
					, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
					, &window
					, &renderer)) {
		printf("SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
		return -1;
	}

	if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV) {
		texture = SDL_CreateTexture(renderer
						// YUY2 is also know as YUYV in SDL
						, SDL_PIXELFORMAT_YUY2
						, SDL_TEXTUREACCESS_STREAMING
						, fmt.fmt.pix.width
						, fmt.fmt.pix.height);
		if (!texture) {
			printf("SDL_CreateTexture failed: %s\n", SDL_GetError());
			return -1;
		}
	} else if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG) {
		if (!IMG_Init(IMG_INIT_JPG)) {
			printf("Unable to initialize IMG\n");
			return -1;
		}
	}

	printf("Device: %s\nWidth: %d\nHeight: %d\n"
		, dev_name, fmt.fmt.pix.width, fmt.fmt.pix.height);

	return 0;
}


void draw_YUV()
{
	// YUYV is two bytes per pixel, so multiple line width by 2
	SDL_UpdateTexture(texture, NULL, buffer_start, fmt.fmt.pix.width * 2);

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void draw_MJPEG()
{
	SDL_RWops *buf_stream = SDL_RWFromMem(buffer_start, (int)length);
	SDL_Surface *frame = IMG_Load_RW(buf_stream, 0);
	SDL_Texture *tx = SDL_CreateTextureFromSurface(renderer, frame);

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tx, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(tx);
	SDL_FreeSurface(frame);
	SDL_RWclose(buf_stream);
}



int sdl_filter(void *userdata, SDL_Event *event)
{
	(void)userdata;
	return event->type == SDL_QUIT;
}

//stop capturing process
void stop_capturing(void)
{
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (ioctl(fd, VIDIOC_STREAMOFF, &type) == -1)
		errno_exit("VIDIOC_STREAMOFF");
}

//Free the mapping buffer
void uninit_device(void)
{
	if (munmap(buffer_start, length) == -1)
		errno_exit("munmap");
}

//CLosing the diplay
void close_view()
{
	if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV)
		SDL_DestroyTexture(texture);

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG)
		IMG_Quit();

	if (SDL_WasInit(SDL_INIT_VIDEO)) 
		SDL_Quit();
}

//Get the pixel format
void get_pixelformat()
{
	struct v4l2_fmtdesc desc;
	memset(&desc, 0, sizeof(desc));
	desc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	// iterate over all formats, and prefer MJPEG when available
	while (ioctl(fd, VIDIOC_ENUM_FMT, &desc) == 0) {
		desc.index++;

		if (desc.pixelformat == V4L2_PIX_FMT_MJPEG) {
			fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
			printf("Using MJPEG\n");
			return;
		}
	}
	printf("Using YUYV\n");
}

void close_device(void)
{
	if (close (fd) == -1)
		errno_exit("close");
}
