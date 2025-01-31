#ifndef _DEVICE_SLEEP_CONTROL_H_
#define _DEVICE_SLEEP_CONTROL_H_
#include "cpu.h"

void usr_screen_on(u8 on);   //  亮灭屏，必须UI线程调用，外面不能随意使用
void lv_os_event_handle(int msg[]); //  lvgl任务消息处理接口

void lv_auto_sleep_enable(bool enable);
void lv_enter_sleep();
void lv_exit_sleep();
void lv_key_active();
void lv_touch_active();
void hw_sleep_ctrl();
void usr_bl_update(u8 level);

#endif
