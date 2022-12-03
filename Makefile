SOURCES=$(shell find src -type f -name '*.c')
OBJECTS=$(SOURCES:%.c=%.o)

aoc: $(OBJECTS) src/main.o
	$(CC) -o $@ $(CARGS) $^

src/%.o: src/%.c
	$(CC) -c $< -o $@ $(CARGS)

clean:
	$(RM) aoc $(OBJECTS)

.PHONY: clean
