#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "tasks.h"
#include "settings.h"
#include "event_flags.h"

UW rand(UW& state) 
{
    // Using XorShift 32bit
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

void blink_leds(UB now_node_num,
                UB* nodes)
{
    gpio_set_val(25, 1);
    tk_dly_tsk(500);
    for(UB i=0; i<now_node_num; i++)
    {
        UB index = nodes[i];
        gpio_set_val(LEDS[index], 1);
        tk_dly_tsk(500);
        gpio_set_val(LEDS[index], 0);
        tk_dly_tsk(500);
    }
    gpio_set_val(25, 0);
}

void show_lighting_pattern(INT stacd, void *exinf)
{
    for(UB i=0; i<UNIT_NUM; i++)
    {
        gpio_set_pin(LEDS[i], GPIO_MODE_OUT);
    }
    // On board LED
    gpio_set_pin(25, GPIO_MODE_OUT);

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

        UB next = rand(seed) % UNIT_NUM;
        nodes[now_node_num] = next;
        now_node_num++;

        blink_leds(now_node_num, nodes);
        tk_set_flg(id_game_flag, WAITING_PLAYER_TURN);
    }
}