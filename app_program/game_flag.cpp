#include <tk/tkernel.h>
#include "event_flags.h"

ID id_game_flag;
UINT WAITING_SYSTEM_TURN = 0x01;
UINT WAITING_PLAYER_TURN = 0x02;
UINT WAITING_CHECK = 0x04;
UINT GAME_OVER = 0x08;

T_CFLG  game_flag = {
        nullptr,
        TA_TFIFO | TA_WMUL,
        WAITING_SYSTEM_TURN,
};