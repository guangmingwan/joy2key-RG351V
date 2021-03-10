#ifndef __VKEY_H__
#define __VKEY_H__
int reportvkey(uint16_t type, uint16_t keycode, int32_t value);
int openvkey(void);
void closevkey(void);
#endif