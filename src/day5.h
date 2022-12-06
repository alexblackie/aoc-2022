#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
int day5(char result[9]);
