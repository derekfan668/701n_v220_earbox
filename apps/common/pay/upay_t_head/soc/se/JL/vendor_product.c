/*
 * Copyright (C) 2015-2019 Alibaba Group Holding Limited
 */

#undef _DEBUG_H_
#define LOG_TAG_CONST       ALIPAY_VC          //修改成文件名
#define LOG_TAG             "[ALIPAY_VC]"
#include "debug.h"
#define LOG_v(t)  log_tag_const_v_ ## t
#define LOG_i(t)  log_tag_const_i_ ## t
#define LOG_d(t)  log_tag_const_d_ ## t
#define LOG_w(t)  log_tag_const_w_ ## t
#define LOG_e(t)  log_tag_const_e_ ## t
#define LOG_c(t)  log_tag_const_c_ ## t
#define LOG_tag(tag, n) n(tag)
const char LOG_tag(LOG_TAG_CONST, LOG_v) AT(.LOG_TAG_CONST) = 0;
const char LOG_tag(LOG_TAG_CONST, LOG_i) AT(.LOG_TAG_CONST) = 1; //log_info
const char LOG_tag(LOG_TAG_CONST, LOG_d) AT(.LOG_TAG_CONST) = 1; //log_debug
const char LOG_tag(LOG_TAG_CONST, LOG_w) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST, LOG_e) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST, LOG_c) AT(.LOG_TAG_CONST) = 1;


#include "timestamp.h"
#include "custom_cfg.h"

#include <string.h>
// #include <stdio.h>
#include "utils.h"
#include "iotsec.h"

#include "system/includes.h"
#include "system/malloc.h"
#include "malloc.h"
//#include "driver_system.h"
//


#include "app_config.h"
#if TCFG_PAY_ALIOS_ENABLE

#if (TCFG_PAY_ALIOS_WAY_SEL==TCFG_PAY_ALIOS_WAY_T_HEAD)
#ifndef TCFG_PAY_ALIOS_COMPANY_NAME
#error "TCFG_PAY_ALIOS_COMPANY_NAME not define!!!"
#endif

#ifndef TCFG_PAY_ALIOS_PRODUCT_MODEL
#error "TCFG_PAY_ALIOS_PRODUCT_MODEL not define!!!"
#endif
#endif

const char *mock_company = TCFG_PAY_ALIOS_COMPANY_NAME;//需要申请后填写
const char *mock_productmodel = TCFG_PAY_ALIOS_PRODUCT_MODEL;//需要申请后填写


#else

const char *mock_company = " ";
const char *mock_productmodel = " ";

#endif



//#include "yc11xx_dev_bt.h"

#define CST_OFFSET_TIME			(8*60*60)	// 北京时间时差

// extern void Ble_SendDataSimple(uint8_t* data, uint16_t len);

extern int alipay_ble_send_data(const uint8_t *data, u16 len);
extern void bt_addr2string(u8 *addr, u8 *buf);

//uint32_t get_timestamp(void);
extern char g_mac_address[18];
//extern void ALIPAY_ble_write(uint8_t *data, uint16_t length);
extern uint32_t Unix_time;
extern int le_controller_get_mac(void *addr);
/*○ 功能描述
    ■ 获取设备ID号(以冒号分割的16进制mac地址)，要求内容以‘\0’结尾且长度不包含'\0'。所有字母大写，长度为17。例如：“AA:BB:CC:00:11:22”
  ○ 接口参数
    ■ buf_did - 存放设备ID数据地址
    ■ len_did - 存放设备ID长度地址
  ○ 返回值
    ■ 0表示成功，非0表示失败*/
csi_error_t csi_get_deviceid(uint8_t *buf_did, uint32_t *len_did)
{
#if 0
    u8 mac[6];

    log_info("%s\n", __func__);
    le_controller_get_mac(mac);
    bt_addr2string(mac, buf_did);
    *len_did = strlen(buf_did);
    log_debug("get mac:%d, %s \n", *len_did, buf_did);
    return CSI_OK;
#endif


#if  1
    u8 mac[6];
    u8 temp_buffer[20];
    log_info("%s\n", __func__);
    le_controller_get_mac(mac);
    bt_addr2string(mac, temp_buffer);
    *len_did = strlen(temp_buffer);
    memcpy(buf_did, temp_buffer, *len_did);
    log_debug("2get mac:%d, %s \n", *len_did, buf_did);
    return CSI_OK;
#endif
}

/*○ 功能描述
    ■ 获取当前系统时间戳（Unix时间戳格式）
  ○ 接口参数
    ■ tm - 存放系统时间戳的变量地址
  ○ 返回值
    ■ 0表示成功，非0表示失败*/
csi_error_t csi_get_timestamp(uint32_t *tm)
{
    log_info("%s\n", __func__);
    struct sys_time time;
    void *fd = dev_open("rtc", NULL);
    if (!fd) {
        log_debug("upay_get_timestamp err!!!\n");
        return CSI_ERROR;
    }
    dev_ioctl(fd, IOCTL_GET_SYS_TIME, (u32)&time);
    dev_close(fd);
    uint32_t utime = timestamp_mytime_2_utc_sec(&time) - CST_OFFSET_TIME;
    log_debug("upay_get_timestamp: %d,%d,%d,%d,%d,%d : %d,0x%x \n", time.year, time.month, time.day, time.hour, time.min, time.sec, utime, utime);
    *tm = utime;
    return CSI_OK;
}

/*○ description:
    ■ get compile timestamp
  ○ param
  ○ return
    ■ compile timestamp*/
csi_error_t csi_get_compile_timestamp(uint32_t *timestamp)
{
    if (timestamp == NULL) {
        return CSI_ERROR;
    }

    *timestamp = get_compile_timestamp();
    return CSI_OK;
}

/*○ 功能描述
    ■ 获取设备SN(厂商印刷在卡片上的设备序列号)，长度不超过32个字符，只能包含大小写字母、数字、下划线。仅卡片类产品且有SN在小程序显示需求的厂商实现，其他厂商请输出""(空字符串)，len_sn=0
  ○ 接口参数
    ■ buf_sn - 存放设备SN数据地址
    ■ len_sn - 存放设备SN长度地址
  ○ 返回值
    ■ 0表示成功，非0表示失败*/
csi_error_t csi_get_sn(uint8_t *buf_sn, uint32_t *len_sn)
{
    u8 serial_len = 0;
    u8 *serial_num = NULL;
    log_info("%s\n", __func__);
    *len_sn = 0;
#if 0
    get_serial_num_cfg_file(&serial_num, &serial_len, GET_SERIAL_FROM_EX_CFG);
    if (serial_len >= 32) {
        serial_len = 31;
    }
    memcpy(buf_sn, serial_num, serial_len);
    buf_sn[serial_len] = '\0';
    *len_sn = serial_len;
#endif
    if (*len_sn == 0) {
        csi_get_deviceid(buf_sn, len_sn);
        buf_sn[*len_sn] = '\0';
    }
    log_debug("get sn:%d, %s \n", *len_sn, buf_sn);

    return CSI_OK;
}

/*○ 功能描述
    ■ 获取设备company name
  ○ 接口参数
    ■ buffer - 存放设备company name数据地址
    ■ len - 存放设备company name长度地址
  ○ 返回值
    ■ 0表示成功，非0表示失败*/
csi_error_t csi_get_companyname(uint8_t *buffer, uint32_t *len)
{
    log_info("%s\n", __func__);
    *len = strlen(mock_company);
    memcpy(buffer, mock_company, strlen(mock_company));

    return CSI_OK;
}

/*○ 功能描述
    ■ 获取设备通讯协议类型
  ○ 接口参数
    ■ ptype - 存放设备通讯协议类型变量地址
  ○ 返回值
    ■ 0表示成功，非0表示失败*/
csi_error_t csi_get_protoctype(uint32_t *ptype)
{
    log_info("%s\n", __func__);
    *ptype = 0;
    return CSI_OK;
}

/*○ 功能描述
    ■ 发送蓝牙数据
  ○ 接口参数
    ■ data - 存放发送数据地址
    ■ len - 存放发送数据长度(len<=20)
  ○ 返回值
    ■ 0表示成功，非0表示失败*/
csi_error_t csi_ble_write(uint8_t *data, uint16_t len)
{
    //Ble_SendDataSimple(0x42,data,len);

    log_info("%s\n", __func__);
    // int ret = alipay_ble_send_data(data, len);
    // if(ret){
    //   log_error("%s[ret:%d]\n", __func__, ret);
    //   return CSI_ERROR;
    // }
    log_info("%s,[len:%d]", __func__, len);
    put_buf(data, len);
    extern int ali2upay_ibuf_to_cbuf(u8 * buf, u32 len);
    extern void ali2upay_send_event(void);
    ali2upay_ibuf_to_cbuf(data, len);
    ali2upay_send_event();

    // ALIPAY_ble_write(data, len);
    return CSI_OK;
}

/*○ 功能描述
    ■ 打印日志信息
  ○ 接口参数
    ■ level - 日志调试打印等级
    ■ format - 格式化输出字符串
    ■ value - 输出数据
  ○ 返回值
    ■ 无*/
void csi_log(int level, const char *format, int32_t value)
{
    //printf("[level%d %d] %s\n",level, value,format);
    printf("[level%d %d] %s\n", level, value, format);
}

/*○ 功能描述
    ■ 打印日志信息
  ○ 接口参数
    ■ format - 格式化输出字符串
    ■ ... - 可变参数
  ○ 返回值
    ■ 无*/
void csi_log_ext(const char *format, va_list *val_list)
{
    // va_list args;
    // va_start(args, format);
    // print(NULL, 0, format, args);;
    // //va_end(arg_list);

#if 1
    extern int ___printf(const char *format, va_list args);
    ___printf(format, *val_list);
    /* vprintf(format, *val_list); */
#else
    printf("123 %s", __func__);
    char log_buf[1024] = {0};
    vsnprintf(log_buf, sizeof(log_buf), format, &val_list);
    printf("%s\n", log_buf);
#endif

}
csi_error_t csi_get_productmodel(uint8_t *buffer, uint32_t *len)
{
    *len = strlen(mock_productmodel);
    memcpy(buffer, mock_productmodel, strlen(mock_productmodel));

    return CSI_OK;
}
#if  1//ALIPAY_SE_FW_V2_0
void *csi_malloc(uint32_t size)
{
    printf("%s\n", __func__);
    return malloc(size);
}

void csi_free(void *pt)
{
    printf("%s\n", __func__);
    free(pt);
}


void *csi_calloc(uint32_t nblock, uint32_t size)
{
    printf("%s\n", __func__);
    void *pt = malloc(nblock * size);
    memset(pt, 0x00, nblock * size);
    return pt;
}

void *csi_realloc(void *pt, uint32_t size)
{
    printf("%s\n", __func__);
    return realloc(pt, size);
}


/* void *_calloc_r(struct _reent *ptr, size_t size, size_t len) */
/* { */
/* return  csi_calloc(size, len); */
/* } */
#endif
