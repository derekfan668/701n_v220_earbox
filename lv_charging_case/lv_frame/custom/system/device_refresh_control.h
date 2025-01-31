#ifndef _DEVICE_REFRESH_CONTROL_H_
#define _DEVICE_REFRESH_CONTROL_H_
#include "cpu.h"

typedef enum
{
    SCREEN_PRIO_LOOP = 0,
    SCREEN_PRIO_PRODUCT_TEST,
    SCREEN_PRIO_LOCK,
    SCREEN_PRIO_CHARGE,
    SCREEN_PRIO_ALARM_RING,
    SCREEN_PRIO_CALL,
    SCREEN_PRIO_POWERON,
    SCREEN_PRIO_MAX,
}
SCREEN_ID; // 反映页面优先级，值越大优先级越高

void screen_list_add(void (*Init)(), void (*Deinit)(), void (*Load)(), void (*Refresh)(), int Screen_Id);
void screen_list_del(int Screen_Id);
void screen_list_clean();
void screen_list_refresh();
void screen_list_printf();

void lv_screen_refresh_start();

#endif
