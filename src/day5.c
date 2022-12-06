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
 * Apply the given `CrateMovement` to the given crate stacks, retaining the
 * original order of the `n` crates from the source stack.
 */
void crates_ordered_move(Crate *crates[], CrateMovement *move)
{
	Crate *popped = crates[move->src];
	Crate *tail = popped;
	for (int count = 0; count < move->quantity - 1; count++)
		tail = tail->next;
	crates[move->src] = tail->next;
	tail->next = crates[move->dest];
	crates[move->dest] = popped;
}

/**
 * Loops over the given file and parses each `move` instruction before
 * then executing it.
 */
void crates_execute_moves(FILE *fp, Crate *crates[], bool ordered)
{
	char *line_buf = NULL;
	size_t line_bufsize = 0;
	while (getline(&line_buf, &line_bufsize, fp) != -1)
	{
		if (line_buf[0] != 'm')
			continue;

		CrateMovement *move = crates_parse_move(line_buf);
		if (ordered)
			crates_ordered_move(crates, move);
		else
			crates_move(crates, move);

		free(move);
	}
	free(line_buf);
}

/**
 * Iterate through all the crate hierarchies and print a visual representation
 * for visual debugging.
 */
void crates_debug_stacks(Crate *crates[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		Crate *cr = crates[i];
		while (cr)
		{
			printf("[%ld %c] ", i, cr->name);
			cr = cr->next;
		}
		printf("\n");
	}
}

void crates_free(Crate *crates[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		Crate *cr, *tmp;
		cr = tmp = crates[i];
		while (cr)
		{
			tmp = cr->next;
			free(cr);
			cr = tmp;
		}
	}
}

int day5(char result[9], bool ordered)
{
	FILE *fp = fopen("inputs/day5.txt", "r");
	if (fp == NULL)
		return -1;

	Crate *crates[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	crates_parse_stacks(fp, crates);

	crates_execute_moves(fp, crates, ordered);
	for (int i = 0; i < 9; i++)
		result[i] = crates[i]->name;

	/* crates_debug_stacks(crates, 9); */

	crates_free(crates, 9);

	fclose(fp);
	return 0;
}
