#include "day3.h"
#include "greatest/greatest.h"

TEST test_ruck_priority()
{
	ASSERT_EQ(1, ruck_priority('a'));
	ASSERT_EQ(16, ruck_priority('p'));
	ASSERT_EQ(38, ruck_priority('L'));
	ASSERT_EQ(42, ruck_priority('P'));
	ASSERT_EQ(22, ruck_priority('v'));
	ASSERT_EQ(20, ruck_priority('t'));
	ASSERT_EQ(19, ruck_priority('s'));
	PASS();
}

TEST test_ruck_partition()
{
	char left[12], right[12];
	char *str = "vJrwpWtwJgWrhcsFMMfFFhFp";
	ruck_partition(str, left, right);
	ASSERT_STR_EQ(left, "vJrwpWtwJgWr");
	ASSERT_STR_EQ(right, "hcsFMMfFFhFp");
	PASS();
}

TEST test_ruck_score()
{
	char left[] = "vJrwpWtwJgWr";
	char right[] = "hcsFMMfFFhFp";
	ASSERT_EQ_FMT(16, ruck_score(left, right), "%d");
	PASS();
}

SUITE(day3_suite)
{
	RUN_TEST(test_ruck_priority);
	RUN_TEST(test_ruck_partition);
	RUN_TEST(test_ruck_score);
}
