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

int main()
{
	char *line_buf = NULL;
	size_t line_bufsize = 0;

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
			continue;
		}

		struct Food *food = malloc(sizeof(struct Food));
		food->calories = atoi(line_buf);
		food->next = last_food;
		last_food = food;
	}

	long int largest = 0;
	struct Elf *elf_ptr = last_elf;
	while(elf_ptr != NULL)
	{
		int calorie_sum = 0;
		struct Food *food_ptr = elf_ptr->food;

		while(food_ptr != NULL)
		{
			calorie_sum += food_ptr->calories;
			food_ptr = food_ptr->next;
		}

		if (calorie_sum > largest)
			largest = calorie_sum;

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

	fclose(fp);
	free(line_buf);
	line_buf = NULL;
	return(EXIT_SUCCESS);
}
