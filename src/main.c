#include<stdio.h>
#include<stdlib.h>

#include "day1.h"
#include "day2.h"

int main()
{
	/**
	 * Day 1
	 */
	long int day1_result[3];
	if(day1(day1_result) == -1)
		return(EXIT_FAILURE);
	printf("Day 1-1: %d\n", day1_result[0]);
	printf("Day 1-2: %d\n", day1_result[0] + day1_result[1] + day1_result[2]);

	/**
	 * Day 2
	 */
	int day2_result = 0;
	if(day2(&day2_result) == -1)
		return(EXIT_FAILURE);
	printf("Day 2-1: %d\n", day2_result);
}
