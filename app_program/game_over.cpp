#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "tasks.h"
#include "settings.h"

void game_over(INT stacd, void *exinf)
{
    // TODO : この時にはすでに初期化処理がされているという前提.ピンの初期化タスク作ったほうがいいかな
    for (UB i = 0; i < 5; i++)
    {
        for (UB i = 0; i < UNIT_NUM; i++)
        {
            gpio_set_val(LEDS[i], 1);
        }
        tk_dly_tsk(500);
        for (UB i = 0; i < UNIT_NUM; i++)
        {
            gpio_set_val(LEDS[i], 0);
        }
        tk_dly_tsk(500);
    }
    
    tk_ext_tsk();
}