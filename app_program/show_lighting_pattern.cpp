#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "tasks.h"
#include "settings.h"

LOCAL UW rand(UW& state) 
{
    // Using XorShift 32bit
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

LOCAL void blink_leds(UB now_node_num,
                UB* nodes)
{
    gpio_set_val(ON_BOARD_LED, 1);
    tk_dly_tsk(500);
    for(UB i=0; i<now_node_num; i++)
    {
        UB index = nodes[i];
        gpio_set_val(LEDS[index], 1);
        tk_dly_tsk(500);
        gpio_set_val(LEDS[index], 0);
        tk_dly_tsk(500);
    }
    gpio_set_val(ON_BOARD_LED, 0);
}

static BOOL has_been_initialized = FALSE;
LOCAL void init()
{
    for(UB i=0; i<UNIT_NUM; i++)
    {
        gpio_set_pin(LEDS[i], GPIO_MODE_OUT);
    }
    // On board LED
    gpio_set_pin(ON_BOARD_LED, GPIO_MODE_OUT);
    has_been_initialized = TRUE;
}

void show_lighting_pattern(INT stacd, void *exinf)
{
    static UW seed = 256;

    if(!has_been_initialized){
        init(); 
    }

    if(NOW_NODE_NUM >= NODES_MAX){
        tk_ext_tsk();
    }

    UB next = rand(seed) % UNIT_NUM;
    NODES[NOW_NODE_NUM] = next;
    NOW_NODE_NUM++;

    blink_leds(NOW_NODE_NUM, NODES);
    tk_sta_tsk(id_wait_input,0);
    tk_ext_tsk();
}