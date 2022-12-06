#include "day6.h"

/**
 * Checks that all elements of the given buffer are unique.
 */
bool day6_unique(char buffer[4])
{
	for (int x = 0; x < 4; x++)
		for (int y = x + 1; y < 4; y++)
			if (buffer[x] == buffer[y])
				return false;
	return true;
}

int day6(int *result)
{
	FILE *fp = fopen("inputs/day6.txt", "r");
	if (fp == NULL)
		return -1;

	char buffer[4];
	char current;
	int i = 0;
	int counter = 1;
	while (!feof(fp))
	{
		current = fgetc(fp);
		if (i == 4)
			i = 0;
		buffer[i] = current;
		if (counter > 3 && day6_unique(buffer))
			break;
		i++;
		counter++;
	}

	*result = counter;

	fclose(fp);
	return 0;
}
