#ifndef __JOY_H__
#define __JOY_H__
int openjoy(const char *dev);
int readjoy(int *key,int *value);
void closejoy(void);
#endif