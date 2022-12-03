#include "day2.h"

/**
 * Determine the possible outcomes for the given hand. "win" is the opponent
 * that this hand will win against, "loss" is the stronger hand which the given
 * hand will lose against.
 *
 * Ensure you free the struct that is returned when it is no longer needed.
 */
Outcomes *rps_outcomes(hand h)
{
	Outcomes *result = malloc(sizeof(Outcomes));
	switch (h)
	{
	case ROCK:
		result->win = SCISSORS;
		result->loss = PAPER;
		break;
	case PAPER:
		result->win = ROCK;
		result->loss = SCISSORS;
		break;
	case SCISSORS:
		result->win = PAPER;
		result->loss = ROCK;
		break;
	default:
		result->win = 0;
		result->loss = 0;
	}
	return result;
}

/**
 * Calculate the points for a given duel.
 */
int rps_calculate_win(hand us, hand them)
{
	if (them == us)
		return POINTS_DRAW;

	Outcomes *o = rps_outcomes(them);
	int points;
	if (us == o->loss)
		points = POINTS_WIN;
	else
		points = POINTS_LOSS;

	free(o);
	return points;
}

/**
 * Calculate a total score, based on whether we won and the value of our hand.
 */
int rps_calculate_score(hand us, hand them)
{
	return us + rps_calculate_win(us, them);
}

/**
 * Given an opponent's hand and a strategic indicator, chooses a hand that
 * follows the strategy.
 */
hand rps_strategise_move(hand them, strat strategy)
{
	if (strategy == STRAT_DRAW)
		return them;

	Outcomes *o = rps_outcomes(them);
	hand us;

	if (strategy == STRAT_WIN)
		us = o->loss;
	else
		us = o->win;

	free(o);
	return us;
}

hand rps_parse_hand(char c)
{
	switch (c)
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
	return 0;
}

int day2(int *score, int *score2)
{
	FILE *fp = fopen("inputs/day2.txt", "r");
	if (fp == NULL)
		return -1;

	char line[5];
	while (fgets(line, 5, fp) != NULL)
	{
		char us, strat_us, them;
		us = rps_parse_hand(line[2]);
		them = rps_parse_hand(line[0]);
		strat_us = rps_strategise_move(them, line[2]);
		if (us == 0 || them == 0 || strat_us == 0)
			return -1;
		*score += rps_calculate_score(us, them);
		*score2 += rps_calculate_score(strat_us, them);
	}

	fclose(fp);
	return 0;
}
