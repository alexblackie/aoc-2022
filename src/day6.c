#include "day6.h"

/**
 * Checks that all elements of the given buffer are unique.
 */
bool day6_unique(char buffer[], int size)
{
	for (int x = 0; x < size; x++)
		for (int y = x + 1; y < size; y++)
			if (buffer[x] == buffer[y])
				return false;
	return true;
}

int day6(int *result, int window)
{
	FILE *fp = fopen("inputs/day6.txt", "r");
	if (fp == NULL)
		return -1;

	char buffer[window];
	char current;
	int i = 0;
	int counter = 1;
	while (!feof(fp))
	{
		current = fgetc(fp);
		if (i == window)
			i = 0;
		buffer[i] = current;
		if (counter >= window && day6_unique(buffer, window))
			break;
		i++;
		counter++;
	}

	*result = counter;

	fclose(fp);
	return 0;
}
