#include "../src/day6.h"
#include "greatest/greatest.h"

TEST test_day6_unique()
{
	char buffer[] = {'a', 'b', 'z', 'c'};
	ASSERT(day6_unique(buffer));

	char buffer2[] = {'a', 'b', 'b', 'c'};
	ASSERT_FALSE(day6_unique(buffer2));

	char buffer3[] = {'n', 'z', 'n', 'r'};
	ASSERT_FALSE(day6_unique(buffer3));

	PASS();
}

SUITE(day6_suite)
{
	RUN_TEST(test_day6_unique);
}
