#pragma once

extern ID id_show_pattern;
void show_lighting_pattern(INT stacd, void *exinf);

extern ID id_wait_input;
void wait_user_input(INT stacd, void *exinf);

extern ID id_game_over;
void game_over(INT stacd, void *exinf);

extern ID id_control_game;
void control_game(INT stacd, void *exinf);
