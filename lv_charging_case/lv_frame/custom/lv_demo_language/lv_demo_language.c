#include "custom.h"

static const char *lanuage_display_array[] = {"简体中文", "English"};
static const char *lanuage_switch_array[] = {"语言切换", "Language Switch"};

// 切换下一种语言
static void screen_language_imgbtn_lang_next_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		int language = box_info_base_cb.lv_language_get();
		language = language < LANGUAGE_COUNT - 1 ? language + 1 : LANGUAGE_COUNT - 1;
		box_info_base_cb.lv_language_set(language);
		break;
	}
	default:
		break;
	}
}

// 切换上一种语言
static void screen_language_imgbtn_lang_pre_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		int language = box_info_base_cb.lv_language_get();
		language = language > 0 ? language - 1 : 0;
		box_info_base_cb.lv_language_set(language);
		break;
	}
	default:
		break;
	}
}

void events_init_screen_language(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_language_imgbtn_lang_next, screen_language_imgbtn_lang_next_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_language_imgbtn_lang_pre, screen_language_imgbtn_lang_pre_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_language_loaded;
void screen_language_refresh()
{
	//判断页面存活
	if(!screen_language_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();
	lv_label_set_text_fmt(guider_ui.screen_language_label_lang, "%s", lanuage_display_array[language]);
	lv_label_set_text_fmt(guider_ui.screen_language_label_lang_title, "%s", lanuage_switch_array[language]);
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

