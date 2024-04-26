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


void setup_scr_screen_squelch(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_squelch
	ui->screen_squelch = lv_obj_create(page);
	lv_obj_set_size(ui->screen_squelch, 320, 172);

	//Write style for screen_squelch, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_squelch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_cont_sq
	ui->screen_squelch_cont_sq = lv_obj_create(ui->screen_squelch);
	lv_obj_set_pos(ui->screen_squelch_cont_sq, 0, 0);
	lv_obj_set_size(ui->screen_squelch_cont_sq, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_squelch_cont_sq, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_squelch_cont_sq, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_squelch_cont_sq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_squelch_cont_sq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_squelch_cont_sq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_squelch_cont_sq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_squelch_cont_sq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_squelch_cont_sq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_squelch_cont_sq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_squelch_cont_sq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_img_sq_start
	ui->screen_squelch_img_sq_start = lv_img_create(ui->screen_squelch_cont_sq);
	lv_obj_add_flag(ui->screen_squelch_img_sq_start, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_squelch_img_sq_start, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_kaishi.png");
#else
	lv_img_set_src(ui->screen_squelch_img_sq_start, "F:/ic_kaishi.bin");
#endif
	lv_img_set_pivot(ui->screen_squelch_img_sq_start, 50,50);
	lv_img_set_angle(ui->screen_squelch_img_sq_start, 0);
	lv_obj_set_pos(ui->screen_squelch_img_sq_start, 127, 106);
	lv_obj_set_size(ui->screen_squelch_img_sq_start, 82, 36);

	//Write style for screen_squelch_img_sq_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_squelch_img_sq_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_label_sq_time
	ui->screen_squelch_label_sq_time = lv_label_create(ui->screen_squelch_cont_sq);
	lv_label_set_text(ui->screen_squelch_label_sq_time, "30分钟");
	lv_label_set_long_mode(ui->screen_squelch_label_sq_time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_squelch_label_sq_time, 65, 71);
	lv_obj_set_size(ui->screen_squelch_label_sq_time, 100, 32);

	//Write style for screen_squelch_label_sq_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_squelch_label_sq_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_squelch_label_sq_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_squelch_label_sq_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_squelch_label_sq_time, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_squelch_label_sq_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_squelch_label_sq_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_squelch_label_sq_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_squelch_label_sq_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_squelch_label_sq_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_squelch_label_sq_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_squelch_label_sq_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_squelch_label_sq_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_squelch_label_sq_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_label_sq_title
	ui->screen_squelch_label_sq_title = lv_label_create(ui->screen_squelch_cont_sq);
	lv_label_set_text(ui->screen_squelch_label_sq_title, "静噪");
	lv_label_set_long_mode(ui->screen_squelch_label_sq_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_squelch_label_sq_title, 0, 35);
	lv_obj_set_size(ui->screen_squelch_label_sq_title, 320, 32);

	//Write style for screen_squelch_label_sq_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_squelch_label_sq_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_squelch_label_sq_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_squelch_label_sq_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_squelch_label_sq_title, &lv_font_pingfangheiti_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_squelch_label_sq_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_squelch_label_sq_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_squelch_label_sq_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_squelch_label_sq_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_squelch_label_sq_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_squelch_label_sq_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_squelch_label_sq_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_squelch_label_sq_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_squelch_label_sq_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_img_sq
	ui->screen_squelch_img_sq = lv_img_create(ui->screen_squelch_cont_sq);
	lv_obj_add_flag(ui->screen_squelch_img_sq, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_squelch_img_sq, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_1.png");
#else
	lv_img_set_src(ui->screen_squelch_img_sq, "F:/ic_1.bin");
#endif
	lv_img_set_pivot(ui->screen_squelch_img_sq, 50,50);
	lv_img_set_angle(ui->screen_squelch_img_sq, 0);
	lv_obj_set_pos(ui->screen_squelch_img_sq, 42, 69);
	lv_obj_set_size(ui->screen_squelch_img_sq, 20, 20);

	//Write style for screen_squelch_img_sq, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_squelch_img_sq, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_img_sleep
	ui->screen_squelch_img_sleep = lv_img_create(ui->screen_squelch_cont_sq);
	lv_obj_add_flag(ui->screen_squelch_img_sleep, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_squelch_img_sleep, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_2.png");
#else
	lv_img_set_src(ui->screen_squelch_img_sleep, "F:/ic_2.bin");
#endif
	lv_img_set_pivot(ui->screen_squelch_img_sleep, 50,50);
	lv_img_set_angle(ui->screen_squelch_img_sleep, 0);
	lv_obj_set_pos(ui->screen_squelch_img_sleep, 192, 69);
	lv_obj_set_size(ui->screen_squelch_img_sleep, 20, 20);

	//Write style for screen_squelch_img_sleep, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_squelch_img_sleep, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_label_sleep_time
	ui->screen_squelch_label_sleep_time = lv_label_create(ui->screen_squelch_cont_sq);
	lv_label_set_text(ui->screen_squelch_label_sleep_time, "30分钟");
	lv_label_set_long_mode(ui->screen_squelch_label_sleep_time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_squelch_label_sleep_time, 214, 71);
	lv_obj_set_size(ui->screen_squelch_label_sleep_time, 100, 32);

	//Write style for screen_squelch_label_sleep_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_squelch_label_sleep_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_squelch_label_sleep_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_squelch_label_sleep_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_squelch_label_sleep_time, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_squelch_label_sleep_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_squelch_label_sleep_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_squelch_label_sleep_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_squelch_label_sleep_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_squelch_label_sleep_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_squelch_label_sleep_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_squelch_label_sleep_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_squelch_label_sleep_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_squelch_label_sleep_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_cont_sq_ing
	ui->screen_squelch_cont_sq_ing = lv_obj_create(ui->screen_squelch);
	lv_obj_set_pos(ui->screen_squelch_cont_sq_ing, 0, 0);
	lv_obj_set_size(ui->screen_squelch_cont_sq_ing, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_squelch_cont_sq_ing, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_squelch_cont_sq_ing, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_squelch_cont_sq_ing, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_squelch_cont_sq_ing, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_squelch_cont_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_squelch_cont_sq_ing, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_squelch_cont_sq_ing, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_squelch_cont_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_squelch_cont_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_squelch_cont_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_squelch_cont_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_squelch_cont_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_squelch_cont_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_squelch_cont_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_label_sq_ing_title
	ui->screen_squelch_label_sq_ing_title = lv_label_create(ui->screen_squelch_cont_sq_ing);
	lv_label_set_text(ui->screen_squelch_label_sq_ing_title, "静噪");
	lv_label_set_long_mode(ui->screen_squelch_label_sq_ing_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_squelch_label_sq_ing_title, 0, 35);
	lv_obj_set_size(ui->screen_squelch_label_sq_ing_title, 320, 32);

	//Write style for screen_squelch_label_sq_ing_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_squelch_label_sq_ing_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_squelch_label_sq_ing_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_squelch_label_sq_ing_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_squelch_label_sq_ing_title, &lv_font_pingfangheiti_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_squelch_label_sq_ing_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_squelch_label_sq_ing_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_squelch_label_sq_ing_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_squelch_label_sq_ing_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_squelch_label_sq_ing_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_squelch_label_sq_ing_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_squelch_label_sq_ing_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_squelch_label_sq_ing_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_squelch_label_sq_ing_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_img_sq_ing_cancel
	ui->screen_squelch_img_sq_ing_cancel = lv_img_create(ui->screen_squelch_cont_sq_ing);
	lv_obj_add_flag(ui->screen_squelch_img_sq_ing_cancel, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_squelch_img_sq_ing_cancel, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_quxiao.png");
#else
	lv_img_set_src(ui->screen_squelch_img_sq_ing_cancel, "F:/ic_quxiao.bin");
#endif
	lv_img_set_pivot(ui->screen_squelch_img_sq_ing_cancel, 50,50);
	lv_img_set_angle(ui->screen_squelch_img_sq_ing_cancel, 0);
	lv_obj_set_pos(ui->screen_squelch_img_sq_ing_cancel, 123, 108);
	lv_obj_set_size(ui->screen_squelch_img_sq_ing_cancel, 82, 36);

	//Write style for screen_squelch_img_sq_ing_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_squelch_img_sq_ing_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_squelch_label_sq_ing
	ui->screen_squelch_label_sq_ing = lv_label_create(ui->screen_squelch_cont_sq_ing);
	lv_label_set_text(ui->screen_squelch_label_sq_ing, "0:45");
	lv_label_set_long_mode(ui->screen_squelch_label_sq_ing, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_squelch_label_sq_ing, 81, 69);
	lv_obj_set_size(ui->screen_squelch_label_sq_ing, 156, 34);

	//Write style for screen_squelch_label_sq_ing, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_squelch_label_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_squelch_label_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_squelch_label_sq_ing, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_squelch_label_sq_ing, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_squelch_label_sq_ing, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_squelch_label_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_squelch_label_sq_ing, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_squelch_label_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_squelch_label_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_squelch_label_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_squelch_label_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_squelch_label_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_squelch_label_sq_ing, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_squelch);

	
}
