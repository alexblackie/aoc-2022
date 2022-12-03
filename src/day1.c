#include "day1.h"

struct Elf {
	struct Elf *next;
	struct Food *food;
};

struct Food {
	int calories;
	struct Food *next;
};

/**
 * Comparator function for `qsort` to sort integers in descending order.
 */
int comparator_desc(const void *a, const void *b)
{
	return *(long int*)b - *(long int*)a;
}

int day1(long int result[3])
{
	char *line_buf = NULL;
	size_t line_bufsize = 0;
	int elf_count = 0;

	struct Elf *last_elf = NULL;
	struct Food *last_food = NULL;

	FILE *fp = fopen("inputs/day1.txt", "r");
	if (fp == NULL)
		return(-1);

	while(getline(&line_buf, &line_bufsize, fp) != -1)
	{
		if (strlen(line_buf) == 1)
		{
			struct Elf *e = malloc(sizeof(struct Elf));
			e->next = last_elf;
			e->food = last_food;
			last_elf = e;
			last_food = NULL;
			elf_count++;
			continue;
		}

		struct Food *food = malloc(sizeof(struct Food));
		food->calories = atoi(line_buf);
		food->next = last_food;
		last_food = food;
	}

	long int calorie_sums[elf_count];
	struct Elf *elf_ptr = last_elf;
	int elf_i = 0;
	while(elf_ptr != NULL)
	{
		long int sum = 0;

		struct Food *food_ptr = elf_ptr->food;
		while(food_ptr != NULL)
		{
			sum += food_ptr->calories;
			food_ptr = food_ptr->next;
		}

		calorie_sums[elf_i] = sum;
		elf_i++;
		elf_ptr = elf_ptr->next;
	}

	while(last_elf != NULL)
	{
		struct Food *food_ptr = last_elf->food;

		while(food_ptr != NULL)
		{
			struct Food *remove = food_ptr;
			food_ptr = food_ptr->next;
			remove->next = NULL;
			free(remove);
		}
		struct Elf *remove = last_elf;
		last_elf = last_elf->next;
		remove->next = NULL;
		free(remove);
	}

	qsort(calorie_sums, elf_count, sizeof(long int), comparator_desc);
	result[0] = calorie_sums[0];
	result[1] = calorie_sums[1];
	result[2] = calorie_sums[2];

	fclose(fp);
	free(line_buf);
	line_buf = NULL;
	return(0);
}
