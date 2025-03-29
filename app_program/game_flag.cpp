#include <tk/tkernel.h>
#include "event_flags.h"

ID id_game_flag;
UINT WAITING_SYSTEM_TURN = 0x01;
T_CFLG  game_flag = {
        nullptr,
        TA_TFIFO | TA_WMUL,
        WAITING_SYSTEM_TURN,
};