#include "../src/day2.h"
#include "greatest/greatest.h"

TEST test_rps_outcomes()
{
	Outcomes *po = rps_outcomes(PAPER);
	ASSERT_EQ(ROCK, po->win);
	ASSERT_EQ(SCISSORS, po->loss);
	free(po);

	Outcomes *ro = rps_outcomes(ROCK);
	ASSERT_EQ(SCISSORS, ro->win);
	ASSERT_EQ(PAPER, ro->loss);
	free(ro);

	Outcomes *so = rps_outcomes(SCISSORS);
	ASSERT_EQ(PAPER, so->win);
	ASSERT_EQ(ROCK, so->loss);
	free(so);

	PASS();
}

TEST test_rps_calculate_win()
{
	hand us, them;

	us = ROCK;
	them = PAPER;
	ASSERT_EQ(POINTS_LOSS, rps_calculate_win(us, them));

	us = PAPER;
	them = ROCK;
	ASSERT_EQ(POINTS_WIN, rps_calculate_win(us, them));

	us = SCISSORS;
	them = ROCK;
	ASSERT_EQ(POINTS_LOSS, rps_calculate_win(us, them));

	us = SCISSORS;
	them = PAPER;
	ASSERT_EQ(POINTS_WIN, rps_calculate_win(us, them));

	us = PAPER;
	them = PAPER;
	ASSERT_EQ(POINTS_DRAW, rps_calculate_win(us, them));

	PASS();
}

TEST test_rps_parse_hand()
{
	ASSERT_EQ(ROCK, rps_parse_hand('A'));
	ASSERT_EQ(PAPER, rps_parse_hand('B'));
	ASSERT_EQ(SCISSORS, rps_parse_hand('C'));
	PASS();
}

TEST test_rps_strategise_move()
{
	ASSERT_EQ(ROCK, rps_strategise_move(SCISSORS, STRAT_WIN));
	ASSERT_EQ(SCISSORS, rps_strategise_move(SCISSORS, STRAT_DRAW));
	ASSERT_EQ(PAPER, rps_strategise_move(SCISSORS, STRAT_LOSE));

	ASSERT_EQ(ROCK, rps_strategise_move(PAPER, STRAT_LOSE));
	ASSERT_EQ(SCISSORS, rps_strategise_move(PAPER, STRAT_WIN));
	ASSERT_EQ(PAPER, rps_strategise_move(PAPER, STRAT_DRAW));

	PASS();
}

SUITE(day2_suite)
{
	/* SET_SETUP(setup, NULL); */
	/* SET_TEARDOWN(teardown, NULL); */

	RUN_TEST(test_rps_outcomes);
	RUN_TEST(test_rps_calculate_win);
	RUN_TEST(test_rps_parse_hand);
	RUN_TEST(test_rps_strategise_move);
}
