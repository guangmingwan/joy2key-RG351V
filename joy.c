#include <stdio.h>  
#include <unistd.h>  
#include <string.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <errno.h>  
#include <linux/input.h>  
#include <linux/joystick.h>

static int fd;
int openjoy(const char *dev)
{
    printf("open:%s\r\n",dev);
    fd = open(dev, O_RDONLY);
    if (fd < 0)    return -1;
    return fd;
}

int readjoy(int *key,int *value)
{
    int len;
    struct js_event js;
    len = read(fd, &js, sizeof(struct js_event));
    if (len < 0)    return -1;
    *key=js.type*10+js.number;
    *value=js.value;
    return 0;
}

void closejoy(void)
{
    close(fd);
} 