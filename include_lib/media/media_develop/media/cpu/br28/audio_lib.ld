SECTIONS
{
    .data : ALIGN(4)
    {
		#include "audio_lib_data.ld"
        . = ALIGN(4);
        *(.jlsp_data)
        *(.jlsp_aec_data)
        *(.jlsp_nlp_data)
        *(.jlsp_dns_data)
        *(.jlsp_enc_data)
        *(.jlsp_prep_data)
        *(.jlsp_wn_data)
    } > ram0

    .bss (NOLOAD) :ALIGN(4)
    {
		#include "audio_lib_bss.ld"

        *(.jlsp_bss)
        *(.jlsp_aec_bss)
        *(.jlsp_nlp_bss)
        *(.jlsp_dns_bss)
        *(.jlsp_enc_bss)
        *(.jlsp_prep_bss)
        *(.jlsp_wn_bss)
    } > ram0

    .text : ALIGN(4)
    {
		#include "audio_lib_text.ld"

        *(.bark_const)
        . = ALIGN(4);
        *(.jlsp_code)
        . = ALIGN(4);
        *(.jlsp_const)
        . = ALIGN(4);
        *(.dns_16k_data)
        . = ALIGN(4);
        *(.dns_8k_data)
        . = ALIGN(4);
        *(.jlsp_dns_code)
        *(.jlsp_dns_const)
        *(.dns_param_data_wind)
        *(.dns_common_data_wind)
        *(.jlsp_nlp_code)
        *(.jlsp_nlp_const)
        *(.jlsp_aec_code)
        *(.jlsp_aec_const)
        *(.jlsp_prep_code)
        *(.jlsp_prep_const)
        *(.jlsp_enc_code)
        *(.jlsp_enc_const)
        *(.jlsp_wn_code)
        *(.jlsp_wn_const)
        *(.dms_sparse_code)
    } > code0

	.data_code ALIGN(32):
	{
		#include "audio_lib_data_text.ld"
        *(.dms_code)
        *(.dms_const)
	} > ram0
}

