#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "tasks.h"
#include "event_flags.h"

UW rand(UW& state) 
{
    // Using XorShift 32bit
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

void blink_leds(INT stacd, void *exinf)
{
    static constexpr UB PIN_NUM = 5;
    static constexpr UB led_pins[PIN_NUM] = {10,12,14,19,21};
    for(UB i=0; i<PIN_NUM; i++)
    {
        gpio_set_pin(led_pins[i], GPIO_MODE_OUT);
    }
    // On board LED
    gpio_set_pin(25, GPIO_MODE_OUT);

    static constexpr UB NODES_MAX = 99;
    static UB nodes[NODES_MAX] = {};
    static UB now_node_num = 0;
    static UW seed = 256;
    static UINT flag_tmp;
    while (TRUE)
    {
        if(now_node_num >= NODES_MAX){
            tk_ext_tsk();
        }

        tk_wai_flg(id_game_flag, WAITING_SYSTEM_TURN, (TWF_ANDW | TWF_CLR), &flag_tmp, TMO_FEVR);

        UB next = rand(seed) % PIN_NUM;
        nodes[now_node_num] = next;
        now_node_num++;
        gpio_set_val(25, 1);
        tk_dly_tsk(500);
        for(UB i=0; i<now_node_num; i++)
        {
            UB index = nodes[i];
            gpio_set_val(led_pins[index], 1);
            tk_dly_tsk(500);
            gpio_set_val(led_pins[index], 0);
            tk_dly_tsk(500);
        }
        gpio_set_val(25, 0);
    }
}