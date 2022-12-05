#include "day4.h"
#include "greatest/greatest.h"

TEST test_cleaning_parse_range()
{
	int result[2];
	char *str = "123-987";

	cleaning_parse_range(result, str);

	ASSERT_EQ_FMT(123, result[0], "%d");
	ASSERT_EQ_FMT(987, result[1], "%d");
	PASS();
}

TEST test_cleaning_parse_elves()
{
	CleaningElf *elf1 = malloc(sizeof(CleaningElf));
	CleaningElf *elf2 = malloc(sizeof(CleaningElf));
	char *line = "2-8,3-7";

	cleaning_parse_elves(line, elf1, elf2);

	ASSERT_EQ(2, elf1->start);
	ASSERT_EQ(8, elf1->end);
	ASSERT_EQ(3, elf2->start);
	ASSERT_EQ(7, elf2->end);

	free(elf1);
	free(elf2);

	PASS();
}

TEST test_cleaning_overlap()
{
	CleaningElf *elf1 = malloc(sizeof(CleaningElf));
	CleaningElf *elf2 = malloc(sizeof(CleaningElf));

	/* 3 - 7 fits within 2 - 8 */
	elf1->start = 2;
	elf1->end = 8;
	elf2->start = 3;
	elf2->end = 7;
	ASSERT(cleaning_overlap(elf1, elf2));

	/* 1 - 2 does not fit within 3 - 4 */
	elf1->start = 1;
	elf1->end = 2;
	elf2->start = 3;
	elf2->end = 4;
	ASSERT_FALSE(cleaning_overlap(elf1, elf2));

	free(elf1);
	free(elf2);

	PASS();
}

TEST test_cleaning_any_overlap()
{
	CleaningElf *elf1 = malloc(sizeof(CleaningElf));
	CleaningElf *elf2 = malloc(sizeof(CleaningElf));

	/* 3 - 7 fits within 2 - 8 */
	elf1->start = 2;
	elf1->end = 8;
	elf2->start = 3;
	elf2->end = 7;
	ASSERT(cleaning_any_overlap(elf1, elf2));

	/* 7 - 9 overlaps with 5 - 7 */
	elf1->start = 7;
	elf1->end = 9;
	elf2->start = 5;
	elf2->end = 7;
	ASSERT(cleaning_any_overlap(elf1, elf2));

	/* 6 - 6 overlaps with 4 - 6 */
	elf1->start = 6;
	elf1->end = 6;
	elf2->start = 4;
	elf2->end = 6;
	ASSERT(cleaning_any_overlap(elf1, elf2));

	/* 2 - 6 overlaps with 4 - 8 */
	elf1->start = 2;
	elf1->end = 6;
	elf2->start = 4;
	elf2->end = 8;
	ASSERT(cleaning_any_overlap(elf1, elf2));
	/* Test that elf1 trailing elf2 also works*/
	ASSERT(cleaning_any_overlap(elf2, elf1));

	/* 1 - 2 does not fit within 3 - 4 */
	elf1->start = 1;
	elf1->end = 2;
	elf2->start = 3;
	elf2->end = 4;
	ASSERT_FALSE(cleaning_any_overlap(elf1, elf2));
	/* Test that elf1 trailing elf2 also works*/
	ASSERT_FALSE(cleaning_any_overlap(elf2, elf1));

	free(elf1);
	free(elf2);

	PASS();
}

SUITE(day4_suite)
{
	RUN_TEST(test_cleaning_parse_elves);
	RUN_TEST(test_cleaning_parse_range);
	RUN_TEST(test_cleaning_overlap);
	RUN_TEST(test_cleaning_any_overlap);
}
