#ifndef _AUD_EFF_DEFAULT_PARM__H
#define _AUD_EFF_DEFAULT_PARM__H

#include "app_config.h"
#include "media/effects_adj.h"
#include "audio_effect/audio_noise_gate_demo.h"
#include "audio_mic/effect_parm.h"
#include "audio_effect/audio_ch_swap_demo.h"

#if LINEIN_MODE_SOLE_EQ_EN
#define mode_add 2
#else
#define mode_add 1
#endif
//music_mode[]选相应buf
#define nor_label  0
#define aux_label    1

//选相应的list
#define nor_list_label 0
#define aux_list_label 1

//phone_mode[]选相应buf
#define dl_wideband_label    0
#define dl_narrowband_label  1
#define ul_wideband_label    2
#define ul_narrowband_label  3

#define HIGH_GRADE_LOW_PASS_FILTER_EN  0//高阶低通滤波器

#define MUSIC_NOISE_GATE_EN    0//虚拟低音前的noisegate

#define PARM_DEBUG  0//调试参数debug
#define CH_SWAP_OLD  0//旧的通道互换
#define AUDIO_VOICE_CHANGER_ENABLE 0//变声模块
#if defined(TCFG_PHASER_GAIN_AND_CH_SWAP_ENABLE) && TCFG_PHASER_GAIN_AND_CH_SWAP_ENABLE || defined(AUDIO_VBASS_CONFIG)&&AUDIO_VBASS_CONFIG
#define GAIN_PROCESS_EN 1
#endif

#if(TCFG_MIC_EFFECT_SEL != MIC_EFFECT_MEGAPHONE)
enum {
    EFFECT_REVERB_PARM_KTV = 0,
    EFFECT_REVERB_PARM_POP,
    EFFECT_REVERB_PARM_qingrou,
    EFFECT_REVERB_PARM_SUPER_REVERB,
    EFFECT_REVERB_PARM_SONG,
    EFFECT_REVERB_PARM_MAX,
};
#else
enum {
    EFFECT_REVERB_PARM_KTV = 0,
    EFFECT_REVERB_PARM_MAX,

    EFFECT_REVERB_PARM_POP,
    EFFECT_REVERB_PARM_qingrou,
    EFFECT_REVERB_PARM_SUPER_REVERB,
    EFFECT_REVERB_PARM_SONG,
};

#endif

struct phone_parm_tool_set {
    struct eq_tool eq_parm;
#if defined(TCFG_PHONE_DRC_ENABLE) && TCFG_PHONE_DRC_ENABLE
    wdrc_struct_TOOL_SET drc_parm;
#endif
};

struct eff_parm {
    NoiseGateParam_TOOL_SET noise_gate_parm;
    HowlingPs_PARM_TOOL_SET howlingps_parm;
    NotchHowlingParam_TOOL_SET notchhowling_parm;
    VoiceChangerParam_TOOL_SET voicechanger_parm;
    Plate_reverb_TOOL_SET plate_reverb_parm;
    EF_ECHO_TOOL_SET echo_parm;
    struct eq_tool eq_parm[5];
    wdrc_struct_TOOL_SET drc_parm[5];
#if 0//GAIN_PROCESS_EN
    Gain_Process_TOOL_SET gain_parm;//增益
#endif
    Mix_TOOL_SET mix_gain;
    struct _AUTOTUNE_TOOL_SET autotune_parm;
    struct tunning_eq_tool tunning_eq_parm;
};
extern struct phone_parm_tool_set phone_mode[4];//通话上下行模式 0:下行宽 1：下行窄  2：上行宽  3:上行窄
extern struct eff_parm  eff_mode[EFFECT_REVERB_PARM_MAX];//混响的8个模式
extern struct music_parm_tool_set music_mode[mode_add];//音乐模式
extern struct music_eq2_tool music_eq2_parm[mode_add];
extern DynamicEQParam_TOOL_SET  dynamic_eq[mode_add];//动态eq
extern Gain_Process_TOOL_SET gain_parm[mode_add];//音乐模式尾部的增益调节
extern LowPassParam_TOOL_SET  low_pass_parm[mode_add];//rl rr通道低通滤波器
extern struct music_eq_tool rl_eq_parm[mode_add];//rl通道eq
extern struct nband_drc rl_drc_parm[mode_add];//rl通道drc
extern Gain_Process_TOOL_SET rl_gain_parm[mode_add];//rl通道gain parm
extern Gain_Process_TOOL_SET vbass_prev_gain_parm[mode_add];
extern VirtualBass_TOOL_SET vbass_parm[mode_add];//虚拟低音
extern struct tunning_eq_tool tunning_eq[mode_add];//高低音eq相关参数


extern struct music_eq_tool high_bass_eq_parm[mode_add];
extern wdrc_struct_TOOL_SET high_bass_drc_parm[mode_add];
extern NoiseGateParam_TOOL_SET music_noisegate_parm[mode_add];
extern struct music_eq_tool fr_eq_parm[mode_add];//fr通道eq
extern struct music_eq_tool rr_eq_parm[mode_add];//rr通道eq
extern SurroundEffect_TOOL_SET sur_parm[mode_add];
extern struct eq_tool muisc_ext_eq[mode_add];//drc之后额外添加的eq
extern Mix_TOOL_SET multi_mix_gain;//混响内多路mix的增益
extern ChannelSwap_TOOL_SET music_ch_swap[mode_add];//声道互换
extern dac_pga_TOOL_SET  dac_pga;

extern float powf(float x, float y);
extern void wdrc_printf(void *_wdrc);
extern struct mode_list *get_group_list(u16 module_name);
extern const struct eq_seg_info phone_eq_tab_normal[3];
extern const struct eq_seg_info ul_eq_tab_normal[3];
extern const struct eq_seg_info eq_tab_normal[10];
extern const struct eq_seg_info mic_eff_eq_tab[5];
extern const u16 eff_mode_seq[8];
extern u16 music_mode_seq[mode_add];
extern const u16 mic_eq_name[5] ;
extern const u16 mic_drc_name[5] ;

void vbass_prev_gain_parm_default_init();
void vbass_prev_gain_file_analyze_init();
void music_vbass_parm_default_init();
void music_vbass_file_analyze_init();
void mix_gain_parm_default_init();
void mix_gain_file_analyze_init();
void mic_voice_changer_parm_default_init();
void mic_voice_changer_file_analyze_init();
void high_bass_wdrc_parm_default_init();
void high_bass_wdrc_file_analyze_init();
void aux_music_low_wdrc_parm_default_init();
void aux_music_low_wdrc_file_analyze_init();
void aux_music_eq_parm_default_init();
void aux_music_eq_file_analyze_init();
void rl_eq_parm_default_init();
void rl_eq_file_analyze_init();
void low_pass_parm_default_init();
void low_pass_file_analyze_init();
void uplink_narrowband_eq_parm_default_init();
void uplink_narrowband_eq_file_analyze_init();
void uplink_wideband_eq_parm_default_init();
void uplink_wideband_eq_file_analyze_init();
void downlink_narrowband_eq_parm_default_init();
void downlink_narrowband_eq_file_analyze_init();
void downlink_wideband_eq_parm_default_init();
void downlink_wideband_eq_file_analyze_init();
void mic_eq0_parm_default_init();
void mic_eq0_file_analyze_init();
void mic_eq1_parm_default_init();
void mic_eq1_file_analyze_init();
void mic_eq2_parm_default_init();
void mic_eq2_file_analyze_init();
void mic_eq3_parm_default_init();
void mic_eq3_file_analyze_init();
void mic_eq4_parm_default_init();
void mic_eq4_file_analyze_init();
void high_bass_eq_parm_default_init();
void high_bass_eq_file_analyze_init();
void music_eq_parm_default_init();
void music_eq_file_analyze_init();
void music_eq2_parm_default_init();
void music_eq2_file_analyze_init();
void mic_wdrc0_parm_default_init();
void mic_wdrc0_file_analyze_init();
void mic_wdrc1_parm_default_init();
void mic_wdrc1_file_analyze_init();
void mic_wdrc2_parm_default_init();
void mic_wdrc2_file_analyze_init();
void mic_wdrc3_parm_default_init();
void mic_wdrc3_file_analyze_init();
void mic_wdrc4_parm_default_init();
void mic_wdrc4_file_analyze_init();
void music_rl_wdrc_parm_default_init();
void music_rl_wdrc_file_analyze_init();
void music_crossover_wdrc_parm_default_init();
void music_crossover_wdrc_file_analyze_init();
void music_low_wdrc_parm_default_init();
void music_low_wdrc_file_analyze_init();
void music_mid_wdrc_parm_default_init();
void music_mid_wdrc_file_analyze_init();
void music_high_wdrc_parm_default_init();
void music_high_wdrc_file_analyze_init();
void music_whole_wdrc_parm_default_init();
void music_whole_wdrc_file_analyze_init();
void downlink_wideband_wdrc_parm_default_init();
void downlink_wideband_wdrc_file_analyze_init();
void downlink_narrowband_wdrc_parm_default_init();
void downlink_narrowband_wdrc_file_analyze_init();
void uplink_wideband_wdrc_parm_default_init();
void uplink_wideband_wdrc_file_analyze_init();
void uplink_narrowband_wdrc_parm_default_init();
void uplink_narrowband_wdrc_file_analyze_init();
void noisegate_parm_default_init();
void noisegate_file_analyze_init();
void howling_ps_parm_default_init();
void howling_ps_file_analyze_init();
void notchhowling_parm_default_init();
void notchhowling_file_analyze_init();
void plate_reverb_parm_default_init();
void plate_reverb_file_analyze_init();
void echo_parm_default_init();
void echo_file_analyze_init();
void dynamic_eq_parm_default_init();
void dynamic_eq_file_analyze_init();
void rl_music_gain_parm_default_init();
void rl_music_gain_file_analyze_init();
void music_gain_parm_default_init();
void music_gain_file_analyze_init();
void mic_gain_parm_default_init();
void mic_gain_file_analyze_init();
void music_noise_gate_parm_default_init();
void music_noise_gate_file_analyze_init();
void tunning_parm_default_init();
void tunning_file_analyze_init();
void mic_tunning_parm_default_init();
void mic_tunning_file_analyze_init();
void rr_eq_parm_default_init();
void rr_eq_file_analyze_init();
void fr_eq_parm_default_init();
void fr_eq_file_analyze_init();
void music_surround_effect_parm_default_init();
void music_surround_effect_file_analyze_init();
void music_ext_eq_parm_default_init();
void music_ext_eq_file_analyze_init();
void music_ch_swap_parm_default_init();
void music_ch_swap_file_analyze_init();
#endif
