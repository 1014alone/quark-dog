#ifndef __MY_SPI_H
#define __MY_SPI_H

#include "driver/gpio.h"

#define MOSI_L     gpio_set_level(GPIO_NUM_7, 0);
#define MOSI_H     gpio_set_level(GPIO_NUM_7, 1);
#define CS_L       gpio_set_level(GPIO_NUM_10, 0);
#define CS_H       gpio_set_level(GPIO_NUM_10, 1);
#define SCK_L      gpio_set_level(GPIO_NUM_6, 0);
#define SCK_H      gpio_set_level(GPIO_NUM_6, 1);
// #define MISO       gpio_get_level(GPIO_NUM_2);

void my_spi_init(void);
void my_spi_send_byte(uint8_t data);
uint8_t my_spi_read_byte(void);

#endif


