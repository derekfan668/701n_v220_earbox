#include "custom.h"

static const char *noise_reduction_title[] = {"降噪", "Noise Reduction"};

static void screen_anc_imgbtn_anc_close_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_CHECKED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_CHECKED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_CHECKED);
		box_info_base_cb.lv_anc_mode_set(ANC_STATUS_CLOSE);
		box_info_send_cb.lv_anc_off_cmd_send();
		break;
	}
	default:
		break;
	}
}
static void screen_anc_imgbtn_anc_open_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_CHECKED);
		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_CHECKED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_CHECKED);
		box_info_base_cb.lv_anc_mode_set(ANC_STATUS_OPEN);
		box_info_send_cb.lv_anc_on_cmd_send();
		break;
	}
	default:
		break;
	}
}
static void screen_anc_imgbtn_anc_transparent_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_CHECKED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_CHECKED);
		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_CHECKED);
		box_info_base_cb.lv_anc_mode_set(ANC_STATUS_TRANSPARENCY);
		box_info_send_cb.lv_transparency_cmd_send();
		break;
	}
	default:
		break;
	}
}



void events_init_screen_anc(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_anc_imgbtn_anc_close, screen_anc_imgbtn_anc_close_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_anc_imgbtn_anc_open, screen_anc_imgbtn_anc_open_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_anc_imgbtn_anc_transparent, screen_anc_imgbtn_anc_transparent_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_anc_loaded;
void screen_anc_refresh()
{
	//判断页面存活
	if(!screen_anc_loaded){return;}
	// printf("%s\n", __FUNCTION__);


	//语言更新
	u8 language = box_info_base_cb.lv_language_get();
	lv_label_set_text_fmt(guider_ui.screen_anc_label_anc_title, "%s", noise_reduction_title[language]);
	switch (language) {
		case CHINESE:
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_guan_lianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_guan_weilianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_guan_xuanzhong.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_guan_weilianjie.bin", NULL);

			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kai_lianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_kai_weilianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_kai_xuanzhong.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_kai_weilianjie.bin", NULL);

			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_tongtou_lianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_tongtou_weilianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_tongtou_xuanzhong.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_tongtou_weilianjie.bin", NULL);
			break;
		case ENGLISH:
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_guan_lianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_guan_weilianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_guan_xuanzhong_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_guan_weilianjie_eng.bin", NULL);

			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kai_lianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_kai_weilianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_kai_xuanzhong_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_kai_weilianjie_eng.bin", NULL);

			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_tongtou_lianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_tongtou_weilianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_tongtou_xuanzhong_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_tongtou_weilianjie_eng.bin", NULL);
			break;
		default:
			break;
	}
	
    //使能状态刷新
	u8 phone_state = box_info_base_cb.lv_phone_state_get();
	u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	if(contorl_enable){
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_DISABLED);

	}else{
		if(language == CHINESE) {
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_guan_weilianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_guan_weilianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_kai_weilianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_kai_weilianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_tongtou_weilianjie.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_tongtou_weilianjie.bin", NULL);
		} else if(language == ENGLISH) {
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_guan_weilianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_guan_weilianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_kai_weilianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_kai_weilianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_tongtou_weilianjie_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_tongtou_weilianjie_eng.bin", NULL);
		}

		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_DISABLED);
	}

	// //状态刷新(不响应蓝牙，开机只跑一遍初始化状态)
	// static bool poweron_status_init = true;
	// if(poweron_status_init){
	// 	poweron_status_init = false;
	// }else{
	// 	return;
	// }

	// if(contorl_enable){

	// 	int anc_mode = box_info_base_cb.lv_anc_mode_get();
	// 	// printf("%s %d anc_mode:%d\n", __FUNCTION__, __LINE__, anc_mode);

	// 	// 更新ANC
	// 	switch (anc_mode){
	// 	case ANC_STATUS_CLOSE:
	// 		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_CHECKED);
	// 		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_CHECKED);
	// 		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_CHECKED);
	// 		break;
	// 	case ANC_STATUS_OPEN:
	// 		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_CHECKED);
	// 		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_CHECKED);
	// 		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_CHECKED);
	// 		break;
	// 	case ANC_STATUS_TRANSPARENCY:
	// 		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_CHECKED);
	// 		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_CHECKED);
	// 		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_CHECKED);
	// 		break;
	// 	default:
	// 		break;
	// 	}
	// }
}

void lv_anc_mode_update(int anc_mode)
{
	// 更新ANC
	switch (anc_mode){
	case ANC_STATUS_CLOSE:
		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_CHECKED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_CHECKED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_CHECKED);
		break;
	case ANC_STATUS_OPEN:
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_CHECKED);
		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_CHECKED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_CHECKED);
		break;
	case ANC_STATUS_TRANSPARENCY:
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_close, LV_STATE_CHECKED);
		lv_obj_clear_state(guider_ui.screen_anc_imgbtn_anc_open, LV_STATE_CHECKED);
		lv_obj_add_state(guider_ui.screen_anc_imgbtn_anc_transparent, LV_STATE_CHECKED);
		break;
	default:
		break;
	}
}