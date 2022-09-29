#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "my_spi.h"

uint8_t count = 0;

void app_main(void)
{
    my_spi_init();
    vTaskDelay(2000/portTICK_PERIOD_MS);
    while(1)
    {
        printf("10\r\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
