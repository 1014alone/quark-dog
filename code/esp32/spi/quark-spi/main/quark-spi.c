#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "my_spi.h"
#include "esp32/rom/ets_sys.h"

int data = 0;

void app_main(void)
{
    // my_spi_init();
    while(1)
    {
        // if(data<200)
        // {
        //     data++;
        // }else{
        //     data = 0;
        // }
        // my_spi_send_byte(data);
        printf("hello world!\r\n");
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}
