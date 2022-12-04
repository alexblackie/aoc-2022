#include <stdio.h>
#include <stdlib.h>

#include "day1.h"
#include "day2.h"
#include "day3.h"

int main()
{
	/**
	 * Day 1
	 */
	long int day1_result[3];
	if (day1(day1_result) == -1)
		return EXIT_FAILURE;
	printf("Day 1-1: %ld\n", day1_result[0]);
	printf("Day 1-2: %ld\n", day1_result[0] + day1_result[1] + day1_result[2]);

	/**
	 * Day 2
	 */
	int day2_result = 0;
	int day2_result2 = 0;
	if (day2(&day2_result, &day2_result2) == -1)
		return EXIT_FAILURE;
	printf("Day 2-1: %d\n", day2_result);
	printf("Day 2-2: %d\n", day2_result2);

	/**
	 * Day 3
	 */
	int day3_result = 0;
	if (day3(&day3_result) == -1)
		return EXIT_FAILURE;
	printf("Day 3-1: %d\n", day3_result);
}
