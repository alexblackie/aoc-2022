#include "../src/day5.h"
#include "greatest/greatest.h"

TEST test_crates_parse_move()
{
	char *cmd = "move 4 from 6 to 1";
	CrateMovement *m = crates_parse_move(cmd);

	ASSERT_EQ_FMT(4, m->quantity, "%d");
	/* src, dest are decremented to match 0-indexing */
	ASSERT_EQ_FMT(5, m->src, "%d");
	ASSERT_EQ_FMT(0, m->dest, "%d");

	free(m);
	PASS();
}

SUITE(day5_suite)
{
	RUN_TEST(test_crates_parse_move);
}
