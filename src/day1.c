#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Elf {
	struct Elf *next;
	struct Food *food;
};

struct Food {
	int calories;
	struct Food *next;
};

int comparator(const void *a, const void *b)
{
	return *(long int*)b - *(long int*)a;
}

int main()
{
	char *line_buf = NULL;
	size_t line_bufsize = 0;
	int elf_count = 0;

	struct Elf *last_elf = NULL;
	struct Food *last_food = NULL;

	FILE *fp = fopen("inputs/day1.txt", "r");
	if (fp == NULL)
		return(EXIT_FAILURE);

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

	qsort(calorie_sums, elf_count, sizeof(long int), comparator);
	printf("Day 1-1: %d\n", calorie_sums[0]);
	printf("Day 1-2: %d\n", calorie_sums[0] + calorie_sums[1] + calorie_sums[2]);

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

	fclose(fp);
	free(line_buf);
	line_buf = NULL;
	return(EXIT_SUCCESS);
}
