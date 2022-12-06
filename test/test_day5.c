#include "../src/day5.h"
#include "greatest/greatest.h"

void _crates_fixture(Crate *crates[])
{
	FILE *fp = fopen("test/fixtures/day5.txt", "r");
	if (fp == NULL)
	{
		printf("Failed to open fixture!");
		return;
	}
	crates_parse_stacks(fp, crates);
	fclose(fp);
}

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

TEST test_crates_move()
{
	Crate *crates[3] = {NULL, NULL, NULL};
	_crates_fixture(crates);

	CrateMovement *move = crates_parse_move("move 2 from 2 to 1");
	crates_move(crates, move);
	free(move);

	ASSERT_EQ_FMT('C', crates[0]->name, "%c");
	ASSERT_EQ_FMT('D', crates[0]->next->name, "%c");

	crates_free(crates, 3);
	PASS();
}

TEST test_crates_ordered_move()
{
	Crate *crates[3] = {NULL, NULL, NULL};
	_crates_fixture(crates);

	CrateMovement *move = crates_parse_move("move 2 from 2 to 1");
	crates_ordered_move(crates, move);
	free(move);

	ASSERT_EQ_FMT('D', crates[0]->name, "%c");
	ASSERT_EQ_FMT('C', crates[0]->next->name, "%c");

	crates_free(crates, 3);
	PASS();
}

SUITE(day5_suite)
{
	RUN_TEST(test_crates_parse_move);
	RUN_TEST(test_crates_move);
	RUN_TEST(test_crates_ordered_move);
}
