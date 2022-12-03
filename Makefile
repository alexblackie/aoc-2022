CFLAGS+=-Wall -pedantic -std=c99 -Wextra
CLANG_FORMAT?=clang-format

SOURCES=$(shell find src -type f -name '*.c')
OBJECTS=$(SOURCES:%.c=%.o)
MAINLESS_OBJECTS=$(filter-out src/main.o,$(OBJECTS))
TEST_SOURCES=$(shell find test -maxdepth 1 -type f -name '*.c')
TEST_OBJECTS=$(TEST_SOURCES:%.c=%.o)

aoc: $(OBJECTS) src/main.o
	$(CC) -o $@ $(CARGS) $^

test/aoc_test: $(TEST_OBJECTS) $(MAINLESS_OBJECTS)
	$(CC) $(CFLAGS) -Isrc -o $@ $^

test: test/aoc_test
	@./test/aoc_test

%.o: %.c
	$(CC) $(CFLAGS) -I src -c -o $@ $<

check-format: $(SOURCES) $(TEST_SOURCES)
	$(CLANG_FORMAT) --Werror -n $^

format: $(SOURCES) $(TEST_SOURCES)
	$(CLANG_FORMAT) -i $^

clean:
	$(RM) aoc test/aoc_test $(OBJECTS) $(TEST_OBJECTS)

.PHONY: clean format test
