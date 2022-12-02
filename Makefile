all: build/day1

build:
	@mkdir build

build/day%: build/day%.o
	$(CC) -o $@ $(CARGS) $^

build/day%.o: src/day%.c build
	$(CC) -c $< -o $@ $(CARGS)

clean:
	$(RM) -fr build
