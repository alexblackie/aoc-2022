#include "greatest/greatest.h"
#include "day2.h"

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
}

SUITE(day2_suite)
{
	/* SET_SETUP(setup, NULL); */
	/* SET_TEARDOWN(teardown, NULL); */

	RUN_TEST(test_rps_calculate_win);
}