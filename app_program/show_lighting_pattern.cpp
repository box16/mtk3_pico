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

static BOOL has_been_initialized = FALSE;
void init()
{
    for(UB i=0; i<UNIT_NUM; i++)
    {
        gpio_set_pin(LEDS[i], GPIO_MODE_OUT);
    }
    // On board LED
    gpio_set_pin(25, GPIO_MODE_OUT);
    has_been_initialized = TRUE;
}

void show_lighting_pattern(INT stacd, void *exinf)
{
    static UW seed = 256;
    static UINT flag_tmp;

    if(!has_been_initialized){
        init(); 
    }

    while (TRUE)
    {
        if(NOW_NODE_NUM >= NODES_MAX){
            tk_ext_tsk();
        }

        tk_wai_flg(id_game_flag, WAITING_SYSTEM_TURN, (TWF_ANDW | TWF_CLR), &flag_tmp, TMO_FEVR);

        UB next = rand(seed) % UNIT_NUM;
        NODES[NOW_NODE_NUM] = next;
        NOW_NODE_NUM++;

        blink_leds(NOW_NODE_NUM, NODES);
        tk_set_flg(id_game_flag, WAITING_PLAYER_TURN);
    }
}