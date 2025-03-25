#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "blink_led.h"
#include "event_flag.h"

void blink_leds(INT stacd, void *exinf)
{   
    const UB PIN_NUM = 5;
    static UB led_pins[PIN_NUM] = {10,12,14,19,21};
    for(UB i=0; i<PIN_NUM; i++)
    {
        gpio_set_pin(led_pins[i], GPIO_MODE_OUT);
    }

    while (TRUE)
    {
        for(UB i=0; i<PIN_NUM; i++)
        {
            gpio_set_val(led_pins[i], 1);
            tk_dly_tsk(100);
        }
        for(UB i=0; i<PIN_NUM; i++)
        {
            gpio_set_val(led_pins[i], 0);
            tk_dly_tsk(100);
        }
    }
    
}