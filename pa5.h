#ifndef PA5_H
#define PA5_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int run_menu(void);
void print_rules(void);
int roll_die(int* dice, int dice_num);
int combo_selection(int* plr_score);
void verify_selection(int num, int* dice, int* plr1_score, int* plr2_score, int cur_plr);
void display_dice(int* dice);
void start_menu(void);
void play_game(void);
void print_scores(int* plr1_score, int* plr2_score);

#endif