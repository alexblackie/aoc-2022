#include "day2.h"

typedef int hand;

const int POINTS_WIN = 6;
const int POINTS_DRAW = 3;
const int POINTS_LOSS = 0;

const hand ROCK = 1;
const hand PAPER = 2;
const hand SCISSORS = 3;

int rps_calculate_win(hand us, hand them)
{
	if(them == us)
		return POINTS_DRAW;

	if((them == ROCK && us == PAPER) ||
		(them == PAPER && us == SCISSORS) ||
		(them == SCISSORS && us == ROCK))
		return POINTS_WIN;

	return POINTS_LOSS;
}

int rps_calculate_score(hand us, hand them)
{
	return(us + rps_calculate_win(us, them));
}

hand rps_parse_hand(char c)
{
	switch(c)
	{
		case 'A':
		case 'X':
			return ROCK;
			break;
		case 'B':
		case 'Y':
			return PAPER;
			break;
		case 'C':
		case 'Z':
			return SCISSORS;
			break;
	}
}

int day2(int *score)
{
	FILE *fp = fopen("inputs/day2.txt", "r");
	if (fp == NULL)
		return(-1);

	char line[5];
	while(fgets(line, 5, fp) != NULL)
	{
		char us, them;
		us = rps_parse_hand(line[2]);
		them = rps_parse_hand(line[0]);
		*score += rps_calculate_score(us, them);
	}

	fclose(fp);
	return(0);
}