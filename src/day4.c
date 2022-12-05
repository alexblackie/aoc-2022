#include <day4.h>

/**
 * Finds complete range overlap in the ranges for the two given elves. Overlap
 * exists if this returns true.
 */
bool cleaning_overlap(CleaningElf *elf1, CleaningElf *elf2)
{
	return (
		/* Does elf1's range fit within elf2? */
		((elf1->start >= elf2->start) && (elf1->end <= elf2->end)) ||
		/* OR does elf2's range fit within elf1? */
		((elf2->start >= elf1->start) && (elf2->end <= elf1->end)));
}

/**
 * Finds *any* overlap in the ranges for the two given elves. Overlap exists if
 * this returns true.
 */
bool cleaning_any_overlap(CleaningElf *elf1, CleaningElf *elf2)
{
	return (((elf2->start >= elf1->start) && (elf2->start <= elf1->end)) ||
			((elf1->start >= elf2->start) && (elf1->start <= elf2->end)));
}

/**
 * Parses string ranges of the format "1-2", returning each side as an element
 * in the given results array.
 */
void cleaning_parse_range(int result[], char *src)
{
	char *cursor, *line, *mutable_line;
	line = mutable_line = strdup(src);

	int i = 0;
	while ((cursor = strsep(&mutable_line, "-")))
	{
		result[i] = atoi(cursor);
		i++;
	}

	free(line);
}

/**
 * Parses a comma-separated list of elves of the format "1-2,3-4" into the two
 * given `CleaningElf` structs. If more than two elves are in the `src`, the
 * middle elves will be ignored.
 */
void cleaning_parse_elves(char *src, CleaningElf *elf1, CleaningElf *elf2)
{
	char *cursor, *line, *mutable_line;
	line = mutable_line = strdup(src);

	int i = 0;
	while ((cursor = strsep(&mutable_line, ",")))
	{
		int results[2];
		cleaning_parse_range(results, cursor);
		if (i == 0)
		{
			elf1->start = results[0];
			elf1->end = results[1];
			i++;
		}
		else
		{
			elf2->start = results[0];
			elf2->end = results[1];
		}
	}

	free(line);
}

int day4(int *count, int *all_count)
{
	FILE *fp = fopen("inputs/day4.txt", "r");
	if (fp == NULL)
		return -1;

	char *line_buf = NULL;
	size_t line_bufsize = 0;
	while (getline(&line_buf, &line_bufsize, fp) != -1)
	{
		CleaningElf *elf1 = malloc(sizeof(CleaningElf));
		CleaningElf *elf2 = malloc(sizeof(CleaningElf));

		cleaning_parse_elves(line_buf, elf1, elf2);

		if (cleaning_overlap(elf1, elf2))
			*count += 1;

		if (cleaning_any_overlap(elf1, elf2))
			*all_count += 1;

		free(elf1);
		free(elf2);
	}

	fclose(fp);
	free(line_buf);
	line_buf = NULL;
	return 0;
}
