#include <tk/tkernel.h>
#include "event_flag.h"

ID      id_switch_flag;                 // イベントフラグのID番号
UINT SWITCH_ON = 0x01;
T_CFLG  switch_flag = {
        .flgatr         = TA_TFIFO | TA_WSGL,   // イベントフラグの属性
        .iflgptn        = 0x00,                // イベントフラグの初期値
};