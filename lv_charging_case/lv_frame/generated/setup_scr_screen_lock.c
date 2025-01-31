/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


void setup_scr_screen_lock(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_lock
	ui->screen_lock = lv_obj_create(page);
	lv_obj_set_size(ui->screen_lock, 320, 172);

	//Write style for screen_lock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_lock_cont_lock
	ui->screen_lock_cont_lock = lv_obj_create(ui->screen_lock);
	lv_obj_set_pos(ui->screen_lock_cont_lock, 0, 0);
	lv_obj_set_size(ui->screen_lock_cont_lock, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_lock_cont_lock, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_lock_cont_lock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_lock_cont_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_lock_cont_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_lock_cont_lock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_lock_cont_lock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_lock_cont_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_lock_cont_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_lock_cont_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_lock_cont_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_lock_cont_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_clear_flag(ui->screen_lock_cont_lock, LV_OBJ_FLAG_SCROLLABLE);

	//Write codes screen_lock_animimg_lock
	ui->screen_lock_animimg_lock = lv_animimg_create(ui->screen_lock_cont_lock);
	lv_animimg_set_src(ui->screen_lock_animimg_lock, (const void **) screen_lock_animimg_lock_imgs, 1);
	lv_animimg_set_duration(ui->screen_lock_animimg_lock, 100);
#if EXTERN_ANIMING
	usr_free_animing(ui->screen_lock_animimg_lock, (const void **) screen_lock_animimg_lock_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
	usr_update_animing(ui->screen_lock_animimg_lock, lock_big_tab[cur_lock_index]);
	#endif
	lv_animimg_set_repeat_count(ui->screen_lock_animimg_lock, LV_ANIM_REPEAT_INFINITE);
	lv_animimg_start(ui->screen_lock_animimg_lock);
	lv_obj_set_pos(ui->screen_lock_animimg_lock, 0, 0);
	lv_obj_set_size(ui->screen_lock_animimg_lock, 320, 172);
	lv_obj_add_flag(ui->screen_lock_animimg_lock, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_clear_flag(ui->screen_lock_animimg_lock, LV_OBJ_FLAG_GESTURE_BUBBLE);

	//Write codes screen_lock_label_lock_hour
	ui->screen_lock_label_lock_hour = lv_label_create(ui->screen_lock_cont_lock);
	lv_label_set_text(ui->screen_lock_label_lock_hour, "00");
	lv_label_set_long_mode(ui->screen_lock_label_lock_hour, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_lock_label_lock_hour, 81, 39);
	lv_obj_set_size(ui->screen_lock_label_lock_hour, 83, 58);

	//Write style for screen_lock_label_lock_hour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_lock_label_lock_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_lock_label_lock_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_lock_label_lock_hour, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_lock_label_lock_hour, &lv_font_pingfangheiti_bold_56, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_lock_label_lock_hour, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_lock_label_lock_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_lock_label_lock_hour, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_lock_label_lock_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_lock_label_lock_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_lock_label_lock_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_lock_label_lock_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_lock_label_lock_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_lock_label_lock_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_lock_label_lock_min
	ui->screen_lock_label_lock_min = lv_label_create(ui->screen_lock_cont_lock);
	lv_label_set_text(ui->screen_lock_label_lock_min, "00");
	lv_label_set_long_mode(ui->screen_lock_label_lock_min, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_lock_label_lock_min, 162, 82);
	lv_obj_set_size(ui->screen_lock_label_lock_min, 83, 58);

	//Write style for screen_lock_label_lock_min, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_lock_label_lock_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_lock_label_lock_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_lock_label_lock_min, lv_color_hex(0x999999), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_lock_label_lock_min, &lv_font_pingfangheiti_bold_56, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_lock_label_lock_min, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_lock_label_lock_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_lock_label_lock_min, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_lock_label_lock_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_lock_label_lock_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_lock_label_lock_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_lock_label_lock_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_lock_label_lock_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_lock_label_lock_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_lock_label_lock_MD
	ui->screen_lock_label_lock_MD = lv_label_create(ui->screen_lock_cont_lock);
	lv_label_set_text(ui->screen_lock_label_lock_MD, "01/02");
	lv_label_set_long_mode(ui->screen_lock_label_lock_MD, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_lock_label_lock_MD, 179, 145);
	lv_obj_set_size(ui->screen_lock_label_lock_MD, 100, 28);

	//Write style for screen_lock_label_lock_MD, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_lock_label_lock_MD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_lock_label_lock_MD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_lock_label_lock_MD, lv_color_hex(0xe1e1e1), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_lock_label_lock_MD, &lv_font_pingfangheiti_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_lock_label_lock_MD, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_lock_label_lock_MD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_lock_label_lock_MD, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_lock_label_lock_MD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_lock_label_lock_MD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_lock_label_lock_MD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_lock_label_lock_MD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_lock_label_lock_MD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_lock_label_lock_MD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_lock_label_lock_week
	ui->screen_lock_label_lock_week = lv_label_create(ui->screen_lock_cont_lock);
	lv_label_set_text(ui->screen_lock_label_lock_week, "MON");
	lv_label_set_long_mode(ui->screen_lock_label_lock_week, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_lock_label_lock_week, 48, 145);
	lv_obj_set_size(ui->screen_lock_label_lock_week, 100, 28);

	//Write style for screen_lock_label_lock_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_lock_label_lock_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_lock_label_lock_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_lock_label_lock_week, lv_color_hex(0xdfdfdf), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_lock_label_lock_week, &lv_font_pingfangheiti_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_lock_label_lock_week, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_lock_label_lock_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_lock_label_lock_week, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_lock_label_lock_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_lock_label_lock_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_lock_label_lock_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_lock_label_lock_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_lock_label_lock_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_lock_label_lock_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_lock);

	
}
