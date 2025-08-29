filter:
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -lm -o filter filter.c helpers.c

g: filter
	./filter -g images/yard.bmp out.bmp

e: filter
	./filter -e images/yard.bmp out.bmp

r: filter
	./filter -r images/yard.bmp out.bmp

b: filter
	./filter -b images/yard.bmp out.bmp

check: filter
	check50 cs50/problems/2025/x/filter/more
