#include "gSensor/gSensor_manage.h"
#include "device/device.h"
#include "app_config.h"
#include "debug.h"
#include "key_event_deal.h"
#include "btstack/avctp_user.h"
#include "app_main.h"
#include "tone_player.h"
#include "user_cfg.h"
#include "system/os/os_api.h"

#if TCFG_GSENOR_USER_IIC_TYPE
#define iic_init(iic)                       hw_iic_init(iic)
#define iic_uninit(iic)                     hw_iic_uninit(iic)
#define iic_start(iic)                      hw_iic_start(iic)
#define iic_stop(iic)                       hw_iic_stop(iic)
#define iic_tx_byte(iic, byte)              hw_iic_tx_byte(iic, byte)
#define iic_rx_byte(iic, ack)               hw_iic_rx_byte(iic, ack)
#define iic_read_buf(iic, buf, len)         hw_iic_read_buf(iic, buf, len)
#define iic_write_buf(iic, buf, len)        hw_iic_write_buf(iic, buf, len)
#define iic_suspend(iic)                    hw_iic_suspend(iic)
#define iic_resume(iic)                     hw_iic_resume(iic)
#else
#define iic_init(iic)                       soft_iic_init(iic)
#define iic_uninit(iic)                     soft_iic_uninit(iic)
#define iic_start(iic)                      soft_iic_start(iic)
#define iic_stop(iic)                       soft_iic_stop(iic)
#define iic_tx_byte(iic, byte)              soft_iic_tx_byte(iic, byte)
#define iic_rx_byte(iic, ack)               soft_iic_rx_byte(iic, ack)
#define iic_read_buf(iic, buf, len)         soft_iic_read_buf(iic, buf, len)
#define iic_write_buf(iic, buf, len)        soft_iic_write_buf(iic, buf, len)
#define iic_suspend(iic)                    soft_iic_suspend(iic)
#define iic_resume(iic)                     soft_iic_resume(iic)
#endif

#define LOG_TAG             "[GSENSOR]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"




static const struct gsensor_platform_data *platform_data;
G_SENSOR_INTERFACE *gSensor_hdl = NULL;
G_SENSOR_INFO  __gSensor_info = {.iic_delay = 10};
#define gSensor_info (&__gSensor_info)


extern spinlock_t sensor_iic;
extern u8 sensor_iic_init_status;

static cbuffer_t *data_w_cbuf = NULL;
#if(!TCFG_P11GSENSOR_EN)
static short *data_buf;
extern int gsensorlen;
#define BUF_SIZE gsensorlen*3
#endif

void gSensor_event_to_user(u8 event)
{
    struct sys_event e;
    e.type = SYS_KEY_EVENT;
    e.u.key.event = event;
    e.u.key.value = 0;
    sys_event_notify(&e);
}

void gSensor_int_io_detect(void *priv)
{
    u8 int_io_status = 0;
    u8 det_result = 0;
    int_io_status = gpio_read(platform_data->gSensor_int_io);
    gSensor_hdl->gravity_sensor_ctl(GSENSOR_INT_DET, &int_io_status);
    if (gSensor_hdl->gravity_sensor_check == NULL) {
        return;
    }
    det_result = gSensor_hdl->gravity_sensor_check();
    if (det_result == 1) {
        log_info("GSENSOR_EVENT_CLICK\n");
        gSensor_event_to_user(KEY_EVENT_CLICK);
    } else if (det_result == 2) {
        log_info("GSENSOR_EVENT_DOUBLE_CLICK\n");
        gSensor_event_to_user(KEY_EVENT_DOUBLE_CLICK);
    } else if (det_result == 3) {
        log_info("GSENSOR_EVENT_THREE_CLICK\n");
        gSensor_event_to_user(KEY_EVENT_TRIPLE_CLICK);
    }
}

int gSensor_read_data(u8 *buf, u8 buflen)
{
    if (buflen < 32) {
        return 0;
    }
    axis_info_t accel_data[32];
    if (!gpio_read(platform_data->gSensor_int_io)) {
        gSensor_hdl->gravity_sensor_ctl(READ_GSENSOR_DATA, accel_data);
    }
    memcpy(buf, accel_data, sizeof(accel_data));
    return sizeof(accel_data) / sizeof(axis_info_t);
}

//输出三轴数组和数据长度
int get_gSensor_data(short *buf)
{
//	printf("%s",__func__);
    axis_info_t accel_data[32];
    if (!gpio_read(platform_data->gSensor_int_io)) {
        gSensor_hdl->gravity_sensor_ctl(READ_GSENSOR_DATA, accel_data);
        for (int i = 0; i < 29; i++) {
            buf[i * 3] = accel_data[i].x;
            buf[i * 3 + 1] = accel_data[i].y;
            buf[i * 3 + 2] = accel_data[i].z;
        }
        return sizeof(accel_data) / sizeof(axis_info_t);
    }
    return 0;
}

int read_gsensor_buf(short *buf)
{
    read_gsensor_nbuf(buf, 1200);
    return 1200;
}
//n组数据
int read_gsensor_nbuf(short *buf, short datalen)
{
#if TCFG_P11GSENSOR_EN
    extern int p11_gsensor_cbuf_read(u8 * data, u16 len);
    return p11_gsensor_cbuf_read(buf, datalen);
#else
//	printf("%s",__func__);
    if (data_w_cbuf == NULL) {
        return 0;
    }
    if (gSensor_info->init_flag  == 1) {
        if (data_w_cbuf->data_len >=  datalen) {
            cbuf_read(data_w_cbuf, buf, datalen);
            cbuf_clear(data_w_cbuf);
            return datalen;
        } else {
            return 0;
        }
    } else {
        printf("%s NOT ONLINE ", __func__);
        return 0;
    }
#endif
}

void write_gsensor_data_handle(u8 index, u8 gpio)
{
    axis_info_t accel_data[32];
    int r_len = 0;
    if (data_w_cbuf == NULL) {
        return ;
    }
    if (gSensor_info->init_flag  == 1) {
        if (!gpio_read(platform_data->gSensor_int_io)) {
            r_len = gSensor_hdl->gravity_sensor_ctl(READ_GSENSOR_DATA, accel_data);
            u8 wlen;
            wlen = cbuf_write(data_w_cbuf, accel_data, 2 * 3 * r_len);
            if (wlen == 0) {
                printf("data_w_cbuf_full");
            }
        }
    } else {
        return ;
    }
}
u8 gravity_sensor_command(u8 w_chip_id, u8 register_address, u8 function_command)
{
    spin_lock(&sensor_iic);
    u8 ret = 1;
    iic_start(gSensor_info->iic_hdl);
    if (0 == iic_tx_byte(gSensor_info->iic_hdl, w_chip_id)) {
        ret = 0;
        log_e("\n gsen iic wr err 0\n");
        goto __gcend;
    }
    delay(gSensor_info->iic_delay);
    if (0 == iic_tx_byte(gSensor_info->iic_hdl, register_address)) {
        ret = 0;
        log_e("\n gsen iic wr err 1\n");
        goto __gcend;
    }
    delay(gSensor_info->iic_delay);
    if (0 == iic_tx_byte(gSensor_info->iic_hdl, function_command)) {
        ret = 0;
        log_e("\n gsen iic wr err 2\n");
        goto __gcend;
    }
__gcend:
    iic_stop(gSensor_info->iic_hdl);
    spin_unlock(&sensor_iic);
    return ret;
}

int _gravity_sensor_get_ndata(u8 r_chip_id, u8 register_address, u8 *buf, int data_len)
{
    spin_lock(&sensor_iic);
    int read_len = 0;
    iic_start(gSensor_info->iic_hdl);
    if (0 == iic_tx_byte(gSensor_info->iic_hdl, r_chip_id - 1)) {
        log_e("\n gsen iic rd err 0\n");
        read_len = 0;
        goto __gdend;
    }
    delay(gSensor_info->iic_delay);
    if (0 == iic_tx_byte(gSensor_info->iic_hdl, register_address)) {
        log_e("\n gsen iic rd err 1\n");
        read_len = 0;
        goto __gdend;
    }
    iic_start(gSensor_info->iic_hdl);
    if (0 == iic_tx_byte(gSensor_info->iic_hdl, r_chip_id)) {
        log_e("\n gsen iic rd err 2\n");
        read_len = 0;
        goto __gdend;
    }
    delay(gSensor_info->iic_delay);
    for (; data_len > 1; data_len--) {
        *buf++ = iic_rx_byte(gSensor_info->iic_hdl, 1);
        read_len ++;
    }
    *buf = iic_rx_byte(gSensor_info->iic_hdl, 0);
    read_len ++;
__gdend:
    iic_stop(gSensor_info->iic_hdl);
    delay(gSensor_info->iic_delay);
    spin_unlock(&sensor_iic);
    return read_len;
}

void gsensor_io_ctl(u8 cmd, void *arg)
{
    if ((!gSensor_hdl) || (!gSensor_hdl->gravity_sensor_ctl)) {
        return;
    }
    gSensor_hdl->gravity_sensor_ctl(cmd, arg);
}

int gravity_sensor_init(void *_data)
{

    if (sensor_iic_init_status == 0) {
        spin_lock_init(&sensor_iic);
        sensor_iic_init_status = 1;
    }
    gSensor_info->init_flag  = 0;
    int retval = 0;
    platform_data = (const struct gsensor_platform_data *)_data;
    gSensor_info->iic_hdl = platform_data->iic;
    retval = iic_init(gSensor_info->iic_hdl);
    log_e("\n  gravity_sensor_init\n");
    if (retval < 0) {
        log_e("\n  open iic for gsensor err\n");
        return retval;
    } else {
        log_info("\n iic open succ\n");
    }
    retval = -EINVAL;
    list_for_each_gsensor(gSensor_hdl) {
        if (!memcmp(gSensor_hdl->logo, platform_data->gSensor_name, strlen(platform_data->gSensor_name))) {
            retval = 0;
            break;
        }
    }
    if (retval < 0) {
        log_e(">>>gSensor_hdl logo err\n");
        return retval;
    }
    if (gSensor_hdl->gravity_sensor_init()) {
        log_e(">>>>gSensor_Int ERROR\n");
    } else {
        log_info(">>>>gSensor_Int SUCC\n");
        gSensor_info->init_flag  = 1;
        if (platform_data->gSensor_int_io != -1) {
            gpio_set_pull_up(platform_data->gSensor_int_io, 1);
            gpio_set_pull_down(platform_data->gSensor_int_io, 0);
            gpio_set_direction(platform_data->gSensor_int_io, 1);
            gpio_set_die(platform_data->gSensor_int_io, 1);
#if(!TCFG_P11GSENSOR_EN)
            data_buf = zalloc(BUF_SIZE);
            if (data_buf == NULL) {
                printf("gsensor_cbuf_error!");
                return 0;
            }
            data_w_cbuf = zalloc(sizeof(cbuffer_t));
            if (data_w_cbuf == NULL) {
                return 0;
            }
            cbuf_init(data_w_cbuf, data_buf, BUF_SIZE);
            /* port_edge_wkup_set_callback(write_gsensor_data_handle); */
            port_edge_wkup_set_callback_by_index(4, write_gsensor_data_handle); // 序号需要和板级配置中的wk_param对应上
            printf("cbuf_init");
#endif
        }
    }

    return 0;
}

int gsensor_disable(void)
{
    int valid = 0;
#if(!TCFG_P11GSENSOR_EN)
    if (data_w_cbuf == NULL) {
        return -1;
    } else {
        if (gSensor_info->init_flag  == 1) {
            gSensor_hdl->gravity_sensor_ctl(GSENSOR_DISABLE, &valid);
            if (valid == 0) {
                free(data_w_cbuf);
                data_w_cbuf = NULL;
                return 0;
            }

        }
    }
    return -1;
#else
    gSensor_hdl->gravity_sensor_ctl(GSENSOR_DISABLE, &valid);
    return 0;
#endif

}

int gsensor_enable(void)
{
    int valid = 0;

#if(!TCFG_P11GSENSOR_EN)
    //查找设备
    gSensor_hdl->gravity_sensor_ctl(SEARCH_SENSOR, &valid);
    if (valid == 0) {
        return -1;
    }
    //工作空间
    data_buf = zalloc(BUF_SIZE);
    if (data_buf == NULL) {
        printf("gsensor_cbuf_error!");
        return -1;
    }
    data_w_cbuf = zalloc(sizeof(cbuffer_t));
    if (data_w_cbuf == NULL) {
        return -1;
    }
    cbuf_init(data_w_cbuf, data_buf, BUF_SIZE);
    printf("cbuf_init");
    //设置参数
#endif
    gSensor_hdl->gravity_sensor_ctl(GSENSOR_RESET_INT, &valid);

    if (valid == -1) {
        return -1;
    }
    printf("gsensor_reset_succeed\n");
    return 0;
}
