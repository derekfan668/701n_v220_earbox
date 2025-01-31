#include "includes.h"
#include "asm/sfc_spi.h"


//CS,CLK,DO,DI,D2,D3均开强驱2挡,drv0 drv1 = 11;
void ZB25VQ128DSJG_norflash_config_drv()
{
    JL_PORTC->HD |= BIT(0);
    JL_PORTC->HD |= BIT(1);
    JL_PORTC->HD |= BIT(2);
    JL_PORTC->HD |= BIT(3);
    JL_PORTC->HD |= BIT(4);
    JL_PORTC->HD |= BIT(5);

    u32 norflash_drv_config = 0x60;
//读SR3当前值
    u8 sr_3 = 0;
    sfc1_spi_cs(0);
    sfc1_spi_write_byte(0x15);
    sr_3 = sfc1_spi_read_byte();
    sfc1_spi_cs(1);
    printf("source_sr3=%x\n", sr_3);

    if (sr_3 == norflash_drv_config) {
        printf("flash drv config done!\n");
        return;
    }

//写寄存器SR3
    norflash_drv_config |= (sr_3 & 0x9f);
    norflash_send_write_enable();
    sfc1_spi_cs(0);
    sfc1_spi_write_byte(0x11);//SR3
    sfc1_spi_write_byte(norflash_drv_config);//norflash_drv_config
    sfc1_spi_cs(1);

//等待写好
    norflash_wait_ok();

//读取SR_3
    sfc1_spi_cs(0);
    sfc1_spi_write_byte(0x15);
    sr_3 = sfc1_spi_read_byte();
    sfc1_spi_cs(1);

    if (sr_3 == norflash_drv_config) {
        printf("write sr_3 successs!\n");
    } else {
        printf("write sr_3 fail! %x \n", sr_3);
    }
}
