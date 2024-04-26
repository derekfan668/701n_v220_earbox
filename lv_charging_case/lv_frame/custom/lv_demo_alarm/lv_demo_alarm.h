#ifndef __LV_DEMO_ALARM_H_
#define __LV_DEMO_ALARM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

extern const char *clock_title[];

extern const char clock_common[];

extern const int clock_common_num;

extern int clock_common_index; // 闹钟常用设置索引


void screen_alarm_refresh();

void lv_cont_alarm_reset();



#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_ALARM_H_ */
