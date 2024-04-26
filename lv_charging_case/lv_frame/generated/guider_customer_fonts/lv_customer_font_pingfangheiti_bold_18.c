/*
 * Copyright 2023 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */
/*******************************************************************************
 * Size: 18 px
 * Bpp: 4
 * Opts: --user-data-dir=C:\Users\admin\AppData\Roaming\gui-guider --app-path=D:\NXP\GUI-Guider-1.6.1-GA\resources\app.asar --no-sandbox --no-zygote --lang=zh-CN --device-scale-factor=1 --num-raster-threads=4 --enable-main-frame-before-activation --renderer-client-id=5 --time-ticks-at-unix-epoch=-1702521867055255 --launch-time-ticks=15894176299 --mojo-platform-channel-handle=2724 --field-trial-handle=1680,i,1224695379562237286,12397818145915132888,131072 --disable-features=SpareRendererForSitePerProcess,WinRetrieveSuggestionsOnlyOnDemand /prefetch:1
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef LV_CUSTOMER_FONT_PINGFANGHEITI_BOLD_18
#define LV_CUSTOMER_FONT_PINGFANGHEITI_BOLD_18 1
#endif

#if LV_CUSTOMER_FONT_PINGFANGHEITI_BOLD_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+6765 "来" */
    0x0, 0x0, 0x0, 0x0, 0xed, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xed, 0x0, 0x0,
    0x0, 0x0, 0x2, 0xaa, 0xaa, 0xaa, 0xff, 0xaa,
    0xaa, 0xaa, 0x30, 0x3, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x50, 0x0, 0x1, 0x60, 0x0,
    0xed, 0x0, 0x19, 0x20, 0x0, 0x0, 0x8, 0xf5,
    0x0, 0xed, 0x0, 0x8f, 0x50, 0x0, 0x0, 0x0,
    0xed, 0x0, 0xed, 0x0, 0xed, 0x0, 0x0, 0x0,
    0x0, 0x6b, 0x10, 0xed, 0x6, 0xf5, 0x0, 0x0,
    0xe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xd0, 0x9, 0xaa, 0xaa, 0xcf, 0xff, 0xfc, 0xaa,
    0xaa, 0x80, 0x0, 0x0, 0x0, 0xda, 0xed, 0xad,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xb, 0xe1, 0xed,
    0x1e, 0xb0, 0x0, 0x0, 0x0, 0x1, 0xcf, 0x40,
    0xed, 0x3, 0xfc, 0x10, 0x0, 0x0, 0x5e, 0xf5,
    0x0, 0xed, 0x0, 0x5f, 0xe4, 0x0, 0x2c, 0xfe,
    0x40, 0x0, 0xed, 0x0, 0x4, 0xff, 0xb1, 0x1f,
    0xb1, 0x0, 0x0, 0xed, 0x0, 0x0, 0x2c, 0xd0,
    0x2, 0x0, 0x0, 0x0, 0xed, 0x0, 0x0, 0x0,
    0x10,

    /* U+7535 "电" */
    0x0, 0x0, 0x1, 0xfa, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1, 0xfa, 0x0, 0x0, 0x0, 0x0,
    0x89, 0x99, 0x99, 0xfd, 0x99, 0x99, 0x90, 0x0,
    0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x0,
    0xec, 0x0, 0x1, 0xfa, 0x0, 0x9, 0xf1, 0x0,
    0xec, 0x0, 0x1, 0xfa, 0x0, 0x9, 0xf1, 0x0,
    0xee, 0x88, 0x89, 0xfd, 0x88, 0x8c, 0xf1, 0x0,
    0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x0,
    0xec, 0x0, 0x1, 0xfa, 0x0, 0x9, 0xf1, 0x0,
    0xec, 0x0, 0x1, 0xfa, 0x0, 0x9, 0xf1, 0x0,
    0xee, 0xaa, 0xaa, 0xfe, 0xaa, 0xad, 0xf1, 0x0,
    0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x0,
    0xec, 0x0, 0x1, 0xfa, 0x0, 0x0, 0x2, 0x10,
    0x21, 0x0, 0x1, 0xfa, 0x0, 0x0, 0x9, 0xf1,
    0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0xb, 0xf0,
    0x0, 0x0, 0x0, 0xdf, 0xb9, 0x99, 0xaf, 0xd0,
    0x0, 0x0, 0x0, 0x4d, 0xff, 0xff, 0xfe, 0x50
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 288, .box_w = 18, .box_h = 17, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 153, .adv_w = 288, .box_w = 16, .box_h = 17, .ofs_x = 2, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xdd0
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 26469, .range_length = 3537, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 2, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t lv_customer_font_pingfangheiti_bold_18 = {
#else
lv_font_t lv_customer_font_pingfangheiti_bold_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font  default: (f.src.ascent - f.src.descent)*/
    .base_line = 2.6999999999999997,                          /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LV_CUSTOMER_FONT_PINGFANGHEITI_BOLD_18*/

