#include "custom.h"

const char *clock_title[] = {"闹钟", "Alarm"};

const char clock_common[] = {5, 10, 30, 60};

const int clock_common_num = sizeof(clock_common) / sizeof(clock_common[0]);

int clock_common_index = 0; // 闹钟常用设置索引


static void screen_alarm_imgbtn_alarm_time_down_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		int language = box_info_base_cb.lv_language_get();
		clock_common_index = clock_common_index > 0 ? clock_common_index - 1 : 0;
		if(language == CHINESE){
			lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d%s", clock_common[clock_common_index], "分钟");
		} else if(language == ENGLISH) {
			lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d%s", clock_common[clock_common_index], "min");
		}
		break;
	}
	default:
		break;
	}
}
static void screen_alarm_imgbtn_alarm_time_up_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		int language = box_info_base_cb.lv_language_get();
		clock_common_index = clock_common_index < clock_common_num - 1 ? clock_common_index + 1 : clock_common_num - 1;
		if(language == CHINESE){
			lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d%s", clock_common[clock_common_index], "分钟");
		} else if(language == ENGLISH) {
			lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d%s", clock_common[clock_common_index], "min");
		}
		break;
	}
	default:
		break;
	}
}
static void screen_alarm_imgbtn_alarm_setting_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		alarm_start(clock_common[clock_common_index] * 60);

	  	break;
	}
	default:
		break;
	}
}
static void screen_alarm_img_alarm_cancel_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		alarm_cancel();

		break;
	}
	default:
		break;
	}
}

void events_init_screen_alarm(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_alarm_imgbtn_alarm_time_down, screen_alarm_imgbtn_alarm_time_down_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_alarm_imgbtn_alarm_time_up, screen_alarm_imgbtn_alarm_time_up_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_alarm_imgbtn_alarm_setting, screen_alarm_imgbtn_alarm_setting_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_alarm_img_alarm_cancel, screen_alarm_img_alarm_cancel_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_alarm_loaded;

// 恢复闹钟设置界面
void lv_cont_alarm_reset()
{
	//判断页面存活
	if(!screen_alarm_loaded){return;}
	lv_obj_clear_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
}

void screen_alarm_refresh()
{
	//判断页面存活
	if(!screen_alarm_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();
	lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_title, "%s", clock_title[language]);
	lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_count_title, "%s", clock_title[language]);
	switch (language) {
		case CHINESE:
			lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d%s", clock_common[clock_common_index], "分钟");
			lv_imgbtn_set_src(guider_ui.screen_alarm_imgbtn_alarm_setting, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_dingshishezhi.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_alarm_imgbtn_alarm_setting, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_dingshishezhi.bin", NULL);
			lv_img_set_src(guider_ui.screen_alarm_img_alarm_cancel, "F:/ic_quxiao_chazhaoerji.bin");
			break;
		case ENGLISH:
			lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d%s", clock_common[clock_common_index], "min");
			lv_imgbtn_set_src(guider_ui.screen_alarm_imgbtn_alarm_setting, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_dingshishezhi_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_alarm_imgbtn_alarm_setting, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_dingshishezhi_eng.bin", NULL);
			lv_img_set_src(guider_ui.screen_alarm_img_alarm_cancel, "F:/ic_quxiao_chazhaoerji_eng.bin");
			break;
		default:
			break;
	}
	
    //使能状态刷新
	u8 phone_state = box_info_base_cb.lv_phone_state_get();
	u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	// contorl_enable = true; // 闹钟测试
	if(contorl_enable){
		lv_obj_clear_state(guider_ui.screen_alarm_imgbtn_alarm_time_down, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_alarm_imgbtn_alarm_time_up, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_alarm_imgbtn_alarm_setting, LV_STATE_DISABLED);
	}else{
		lv_obj_add_state(guider_ui.screen_alarm_imgbtn_alarm_time_down, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_alarm_imgbtn_alarm_time_up, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_alarm_imgbtn_alarm_setting, LV_STATE_DISABLED);
	}

	//状态刷新
	if(contorl_enable){

		u8 alarm_state = alarm_status_get();

		switch (alarm_state){
		case ALARM_ON:

			alarm_refresh();

			lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
			break;
		case ALARM_RING:
			// lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
			// lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
			break;
		case ALARM_OFF:
			lv_obj_clear_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
			break;
		default:
			break;
		}
	}
}