#pragma once
#include <tk/tkernel.h>

constexpr UB UNIT_NUM = 5;
constexpr UB SWITCHS[UNIT_NUM] = {16,22,6,7,5};// ピンによっては他のデバイス用にとられてて意図しない動きをする
constexpr UB LEDS[UNIT_NUM] = {10,12,14,19,21};
constexpr UB NODES_MAX = 99;
extern UB NODES[NODES_MAX];
extern UB USER_INPUTS[NODES_MAX];
extern UB NOW_NODE_NUM;
