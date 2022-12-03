#include<stdio.h>
#include<stdlib.h>

#define POINTS_WIN 6
#define POINTS_DRAW 3
#define POINTS_LOSS 0

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

typedef int hand;

int rps_calculate_win(hand us, hand them);
hand rps_parse_hand(char c);
int day2(int *result);
