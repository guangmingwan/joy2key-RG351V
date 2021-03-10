#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

static int fd;
int reportvkey(uint16_t type, uint16_t keycode, int32_t value)
{
    int ret;
    struct input_event ev;
    memset(&ev, 0, sizeof(struct input_event));
    ev.type = type;
    ev.code = keycode;
    ev.value = value;
    ret = write(fd, &ev, sizeof(struct input_event));
    if (ret < 0) {
        printf("report key error!\n");
        return ret;
    }
    return 0;
}

 

int openvkey(void)
{
    struct uinput_user_dev uidev;
    int ret,i;
    //鎵撳紑uinput璁惧
    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        printf("error:%d\r\n",fd);
        return fd;
    }

    //娉ㄥ唽浜嬩欢
    ioctl(fd, UI_SET_EVBIT, EV_SYN);    //鍚屾浜嬩欢
    ioctl(fd, UI_SET_EVBIT, EV_KEY);    //鎸夐敭浜嬩欢

    //娉ㄥ唽鎸夐敭
    for(i = 0; i < 128; i++){
        ioctl(fd, UI_SET_KEYBIT, i);
    }

    //鍒涘缓铏氭嫙璁惧
    memset(&uidev, 0, sizeof(struct uinput_user_dev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-sample");
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor = 0x1234;    //搴旇鏄殢渚垮啓鐨?    
    uidev.id.product = 0xfedc;    //搴旇鏄殢渚垮啓鐨?    
    uidev.id.version = 1;        //搴旇鏄殢渚垮啓鐨?    
    ret = write(fd, &uidev, sizeof(struct uinput_user_dev));
    ret = ioctl(fd, UI_DEV_CREATE);
    if (ret < 0) {
        printf("create dev error:%d\r\n",ret);
        close(fd);
        return ret;
    }
    return 0;
}

void closevkey(void)
{
    //鍒犻櫎涓嬭櫄鎷熻澶?    
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
} 