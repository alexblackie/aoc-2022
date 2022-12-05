#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
	int start;
	int end;
} CleaningElf;

bool cleaning_overlap(CleaningElf *elf1, CleaningElf *elf2);
bool cleaning_any_overlap(CleaningElf *elf1, CleaningElf *elf2);
void cleaning_parse_range(int result[], char *src);
void cleaning_parse_elves(char *line, CleaningElf *elf1, CleaningElf *elf2);
int day4(int *result, int *result2);
