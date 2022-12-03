# Advent of Code 2k22: My Solutions

This repository contains my personal solutions for the [Advent of Code for 2022][aoc].

[aoc]: https://adventofcode.com/2022

## Running

This year I decided to use C, so all the solutions here are written in GNU-ish
C, with a simple Makefile to get everything compiled.

To compile the program, just run:

```
$ make
```

... and you'll get a binary in the root directory named `aoc`. Run this to run
all days' solutions.

## Testing

There is a unit test suite as well.

First, ensure you have cloned all submodules as we pull in an external library:

```
git submodule update --init
```

Then you can compile and run the test suite:

```
$ make test
```
