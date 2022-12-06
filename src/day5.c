#include "day5.h"

/**
 * Read each line of the given file, parsing it into the crate stacks. Stops
 * after encountering the stack labels at the end of the stack columns.
 */
void crates_parse_stacks(FILE *fp, Crate *crates[])
{
	char *line_buf = NULL;
	size_t line_bufsize = 0;
	while (getline(&line_buf, &line_bufsize, fp) != -1)
	{
		if (line_buf[1] == '1')
			break;

		for (size_t i = 0; i * 4 < strlen(line_buf); i++)
		{
			char c = line_buf[i * 4 + 1];
			if (c == ' ')
				continue;

			Crate *cr = malloc(sizeof(Crate));
			cr->name = c;
			cr->next = NULL;

			if (crates[i] == NULL)
			{
				crates[i] = cr;
			}
			else
			{
				Crate *tail = crates[i];
				while (tail && tail->next != NULL)
					tail = tail->next;
				tail->next = cr;
			}
		}
	}
	free(line_buf);
}

/**
 * Converts a "move" command line into a proper `CrateMovement` struct.
 */
CrateMovement *crates_parse_move(char *cmd)
{
	CrateMovement *m = malloc(sizeof(CrateMovement));
	char *cursor, *line, *mutable_line;
	line = mutable_line = strdup(cmd);

	char *args[6];
	int i = 0;
	while ((cursor = strsep(&mutable_line, " ")))
	{
		args[i] = cursor;
		i++;
	}

	m->quantity = atoi(args[1]);
	m->src = atoi(args[3]) - 1;
	m->dest = atoi(args[5]) - 1;

	free(line);
	return m;
}

/**
 * Apply the given `CrateMovement` to the given crate stacks.
 */
void crates_move(Crate *crates[], CrateMovement *move)
{
	for (int count = 0; count < move->quantity; count++)
	{
		Crate *popped = crates[move->src];
		crates[move->src] = popped->next;
		popped->next = crates[move->dest];
		crates[move->dest] = popped;
	}
}

/**
 * Loops over the given file and parses each `move` instruction before
 * then executing it.
 */
void crates_execute_moves(FILE *fp, Crate *crates[])
{
	char *line_buf = NULL;
	size_t line_bufsize = 0;
	while (getline(&line_buf, &line_bufsize, fp) != -1)
	{
		if (line_buf[0] != 'm')
			continue;

		CrateMovement *move = crates_parse_move(line_buf);
		crates_move(crates, move);
		free(move);
	}
	free(line_buf);
}

/**
 * Iterate through all the crate hierarchies and print a visual representation
 * for visual debugging.
 */
void crates_debug_stacks(Crate *crates[9])
{
	for (int i = 0; i < 9; i++)
	{
		Crate *cr = crates[i];
		while (cr)
		{
			printf("[%d %c] ", i, cr->name);
			cr = cr->next;
		}
		printf("\n");
	}
}

int day5(char result[9])
{
	FILE *fp = fopen("inputs/day5.txt", "r");
	if (fp == NULL)
		return -1;

	Crate *crates[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	crates_parse_stacks(fp, crates);
	crates_execute_moves(fp, crates);

	/* crates_debug_stacks(crates); */

	for (int i = 0; i < 9; i++)
	{
		Crate *cr, *tmp;
		cr = tmp = crates[i];
		result[i] = cr->name;
		while (cr)
		{
			tmp = cr->next;
			free(cr);
			cr = tmp;
		}
	}

	fclose(fp);
	return 0;
}