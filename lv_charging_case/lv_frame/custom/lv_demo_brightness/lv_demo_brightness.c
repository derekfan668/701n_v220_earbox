#include "custom.h"

static const char *brightness_title[] = {"屏幕亮度", "Brightness"};

static void screen_brightness_imgbtn_bn_up_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		int brightness = box_info_base_cb.lv_ui_bl_levl_get();
		printf("brightness: %d", brightness);
		brightness = brightness <= LIGHT_LEVEL_MAX - LIGHT_LEVEL_STEP ? brightness + LIGHT_LEVEL_STEP: LIGHT_LEVEL_MAX;
		lv_slider_set_value(guider_ui.screen_brightness_slider_bn, brightness, LV_ANIM_OFF);
		box_info_base_cb.lv_ui_bl_levl_set(brightness);
		break;
	}
	default:
		break;
	}
}
static void screen_brightness_imgbtn_bn_down_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		int brightness = box_info_base_cb.lv_ui_bl_levl_get();
		printf("brightness: %d", brightness);
		brightness = brightness >= LIGHT_LEVEL_MIN + LIGHT_LEVEL_STEP ? brightness - LIGHT_LEVEL_STEP : LIGHT_LEVEL_MIN;
		lv_slider_set_value(guider_ui.screen_brightness_slider_bn, brightness, LV_ANIM_OFF);
		box_info_base_cb.lv_ui_bl_levl_set(brightness);
		break;
	}
	default:
		break;
	}
}


void events_init_screen_brightness(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_brightness_imgbtn_bn_up, screen_brightness_imgbtn_bn_up_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_brightness_imgbtn_bn_down, screen_brightness_imgbtn_bn_down_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_brightness_loaded;
void screen_brightness_refresh()
{
	//判断页面存活
	if(!screen_brightness_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();
	lv_label_set_text_fmt(guider_ui.screen_brightness_label_bn_title, "%s", brightness_title[language]);
	// switch (language) {
	// 	case CHINESE:
	// 		break;
	// 	case ENGLISH:
	// 		break;
	// 	default:
	// 		break;
	// }

    // //使能状态刷新
	// u8 phone_state = box_info_base_cb.lv_phone_state_get();
	// u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	// u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	// if(contorl_enable){
	// }else{
	// }

	// //状态刷新
	// if(contorl_enable){
	// }
}