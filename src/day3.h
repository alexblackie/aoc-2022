#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ruck_priority(char c);
void ruck_partition(char *line, char left[], char right[]);
int ruck_score(char left[], char right[]);
int day3(int *result);
