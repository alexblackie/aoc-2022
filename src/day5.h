#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Crate
{
	char name;
	struct Crate *next;
} Crate;

typedef struct CrateMovement
{
	int quantity;
	int src;
	int dest;
} CrateMovement;

CrateMovement* crates_parse_move(char *src);
void crates_move(Crate *crates[], CrateMovement *m);
void crates_ordered_move(Crate *crates[], CrateMovement *m);
void crates_parse_stacks(FILE *fp, Crate *crates[]);
void crates_free(Crate *crates[], size_t size);
void crates_debug_stacks(Crate *crates[], size_t size);
int day5(char result[9], bool ordered);
