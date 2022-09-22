#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "my_spi.h"
#include "esp32/rom/ets_sys.h"


void my_spi_init(void)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = 0b10000000|0b01000000|0b10000000000;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = 0b00000100;
    gpio_config(&io_conf);
}

void my_spi_send_byte(uint8_t data)
{
    int8_t i = 0;
    SCK_H;
    ets_delay_us(1);
    for(i = 7;i >= 0;i--) 
    {
        SCK_L;
        if((data>>i)&0x01){
            MOSI_H;
        }else{
            MOSI_L;
        }
        ets_delay_us(1);
        SCK_H;
        ets_delay_us(1);
    }
}

uint8_t my_spi_read_byte(void)
{
    int8_t i = 0;
    uint8_t data = 0;
    SCK_H;
    ets_delay_us(1);
    for(i = 7;i >= 0;i--) 
    {
        SCK_L;
        if(gpio_get_level(GPIO_NUM_2)){
            data = data|(0x01<<i);
        }else{
            data = data&(~(0x01<<i));
        }
        ets_delay_us(1);
        SCK_H;
        ets_delay_us(1);
    }
    return data;
}