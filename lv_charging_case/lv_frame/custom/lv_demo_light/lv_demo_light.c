#include "custom.h"

static const char *light_title[] = {"灯光", "Light Level"};


// 打开灯光
static void screen_light_img_light_on_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		lv_obj_clear_flag(guider_ui.screen_light_cont_lighting, LV_OBJ_FLAG_HIDDEN); // 打开灯光

		// 隐藏上下状态栏
		lv_status_bar_top_hide(); 
		lv_status_bar_bottom_hide();
		
		lv_auto_sleep_enable(false); // 设置常亮
		break;
	}
	default:
		break;
	}
}

// 关闭灯光
static void screen_light_cont_lighting_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		lv_obj_add_flag(guider_ui.screen_light_cont_lighting, LV_OBJ_FLAG_HIDDEN); // 关闭灯光

		// 显示上下状态栏
		lv_status_bar_top_show(); 
		lv_status_bar_bottom_show();

		lv_auto_sleep_enable(true); // 取消常亮
		break;
	}
	default:
		break;
	}
}

void events_init_screen_light(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_light_img_light_on, screen_light_img_light_on_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_light_cont_lighting, screen_light_cont_lighting_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_light_loaded;
void screen_light_refresh()
{
	//判断页面存活
	if(!screen_light_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();
	lv_label_set_text_fmt(guider_ui.screen_light_label_light_title, "%s", light_title[language]);
	switch (language) {
		case CHINESE:
			lv_img_set_src(guider_ui.screen_light_img_light_on, "F:/ic_dakai_pingmudengguang.bin");
			break;
		case ENGLISH:
			lv_img_set_src(guider_ui.screen_light_img_light_on, "F:/ic_dakai_pingmudengguang_eng.bin");
			break;
		default:
			break;
	}


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