#include<stdio.h>
#include<stdlib.h>

#define POINTS_WIN  6
#define POINTS_DRAW 3
#define POINTS_LOSS 0

#define STRAT_LOSE 'X'
#define STRAT_DRAW 'Y'
#define STRAT_WIN  'Z'

#define ROCK     1
#define PAPER    2
#define SCISSORS 3

typedef int hand;
typedef char strat;

typedef struct {
	hand win;
	hand loss;
} Outcomes;

Outcomes * rps_outcomes(hand h);
int rps_calculate_win(hand us, hand them);
hand rps_parse_hand(char c);
hand rps_strategise_move(hand them, strat strategy);

int day2(int *result, int *result2);
