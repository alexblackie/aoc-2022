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

/**
 * Finds the common item in all strings in the three-elf group.
 */
char ruck_find_badges(char *group[3])
{
	for (size_t i = 0; i < strlen(group[0]); i++)
	{
		char *match_one = strchr(group[1], group[0][i]);
		char *match_two = strchr(group[2], group[0][i]);
		if (match_one != NULL && match_two != NULL)
			return group[0][i];
	}
	return 0;
}

int day3(int *result, int *badges)
{
	FILE *fp = fopen("inputs/day3.txt", "r");
	if (fp == NULL)
		return -1;

	char *elf_group[3];
	int elf_group_cursor = 0;
	char *line_buf = NULL;
	size_t line_bufsize = 0;
	while (getline(&line_buf, &line_bufsize, fp) != -1)
	{
		char left[255], right[255];
		ruck_partition(line_buf, left, right);
		*result += ruck_score(left, right);

		/* Part two */

		elf_group[elf_group_cursor] = strdup(line_buf);
		if (elf_group_cursor == 2)
		{
			char badge = ruck_find_badges(elf_group);
			*badges += ruck_priority(badge);

			for (int i = 0; i < 3; i++)
			{
				free(elf_group[i]);
				elf_group[i] = NULL;
			}

			elf_group_cursor = 0;
		}
		else
		{
			elf_group_cursor++;
		}
	}

	fclose(fp);
	free(line_buf);
	line_buf = NULL;
	return 0;
}
