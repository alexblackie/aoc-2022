#include "day3.h"

const char ruck_alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/**
 * Return the "sorting priority" of the given item, which is based on its
 * relative position in the alphabet.
 */
int ruck_priority(char c)
{
	const char *match = strchr(ruck_alphabet, c);
	if (match != NULL)
		return (match - ruck_alphabet) + 1;
	return -1;
}

/**
 * Given a line, split it into equal halves, left and right.
 */
void ruck_partition(char *line, char *left, char *right)
{
	int len = strlen(line);
	int midpoint = (len / 2) - 1;
	for (int i = 0; i < len; i++)
	{
		if (i <= midpoint)
			left[i] = line[i];
		else
			right[i - midpoint - 1] = line[i];
	}
	left[midpoint + 1] = '\0';
	right[midpoint + 1] = '\0';
}

/**
 * Look through both halves for a matching item and return its priority.
 */
int ruck_score(char left[], char right[])
{
	for (size_t i = 0; i < strlen(left); i++)
	{
		for (size_t j = 0; j < strlen(right); j++)
		{
			if (left[i] == right[j])
				return ruck_priority(left[i]);
		}
	}
	return 0;
}

int day3(int *result)
{
	FILE *fp = fopen("inputs/day3.txt", "r");
	if (fp == NULL)
		return -1;

	char *line_buf = NULL;
	size_t line_bufsize = 0;
	while (getline(&line_buf, &line_bufsize, fp) != -1)
	{
		char left[255], right[255];
		ruck_partition(line_buf, left, right);
		*result += ruck_score(left, right);
	}

	fclose(fp);
	free(line_buf);
	line_buf = NULL;
	return 0;
}
