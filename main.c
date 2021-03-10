#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "joy.h"
#include "vkey.h"
#include <linux/input.h>

#define MASK_UP        1
#define MASK_DOWN    2
#define MASK_LEFT    4
#define MASK_RIGHT    8

int main(void)
{
    int key,value,mask=0;
    
    printf("Programe by netwan!\r\n");
    if(openjoy("/dev/input/js0")<0)
    {
        printf("gamepad not found!\n");
        return 1;
    }
    #if 1
    if(openvkey()<0)
    {
        printf("can not open vkey!\n");
        closejoy();
        return 2;
    }
    #endif
    printf("joy2key init ready\n");
    daemon( 0 , 0 ); 
    while(1)
    {
        if(readjoy(&key,&value)==0)
        {
            printf("key=%d value=%d\r\n",key,value);
            if(key==19)    break;
            if(key==27)
            {
                if(value==-32767)
                {
                    reportvkey(EV_KEY, KEY_UP, 1);
                    mask|=MASK_UP;
                }
                else if(value==32767)
                {
                    reportvkey(EV_KEY, KEY_DOWN, 1);
                    mask|=MASK_DOWN;
                }
                else if(value==0)
                {
                    if(mask&MASK_UP)
                    {
                        reportvkey(EV_KEY, KEY_UP, 0);
                        mask&=~MASK_UP;
                    }
                    if(mask&MASK_DOWN)
                    {
                        reportvkey(EV_KEY, KEY_DOWN, 0);
                        mask&=~MASK_DOWN;
                    }
                }
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }
            else if(key==26)
            {
                if(value==-32767)
                {
                    reportvkey(EV_KEY, KEY_LEFT, 1);
                    mask|=MASK_LEFT;
                }
                else if(value==32767)
                {
                    reportvkey(EV_KEY, KEY_RIGHT, 1);
                    mask|=MASK_RIGHT;
                }
                else if(value==0)
                {
                    if(mask&MASK_LEFT)
                    {
                        reportvkey(EV_KEY, KEY_LEFT, 0);
                        mask&=~MASK_LEFT;
                    }
                    if(mask&MASK_RIGHT)
                    {
                        reportvkey(EV_KEY, KEY_RIGHT, 0);
                        mask&=~MASK_RIGHT;
                    }
                }
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }
            else if(key==10)    
            {
                reportvkey(EV_KEY, KEY_LEFTCTRL, value);
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }
            else if(key==11)
            {
                reportvkey(EV_KEY, KEY_LEFTALT, value);
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }
            else if(key==12)
            {
                reportvkey(EV_KEY, KEY_SPACE, value);
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }
            else if(key==13)
            {
                reportvkey(EV_KEY, KEY_LEFTSHIFT, value);
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }
            else if(key==14)
            {
                reportvkey(EV_KEY, KEY_TAB, value);
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }
            else if(key==15)
            {
                reportvkey(EV_KEY, KEY_BACKSPACE, value);
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }
            else if(key==16)//start
            {
                reportvkey(EV_KEY, KEY_ENTER, value);
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }
            else if(key==17)//select
            {
                reportvkey(EV_KEY, KEY_ESC, value);
                reportvkey(EV_SYN, SYN_REPORT, 0);
            }

        }else usleep(1000);
    }
    closevkey();        
    closejoy();
    return 0;
} 