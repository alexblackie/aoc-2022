#include "greatest/greatest.h"

SUITE(day2_suite);
SUITE(day3_suite);

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[])
{
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(day2_suite);
	RUN_SUITE(day3_suite);

	GREATEST_MAIN_END();
}
