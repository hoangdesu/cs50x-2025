.SILENT:

speller:
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o speller.o speller.c
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o dictionary.o dictionary.c
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o speller speller.o dictionary.o -lm

rm:
	rm speller

a:
	rm -f speller
	make speller
	./speller texts/lalaland.txt


.PHONY: b

b: a
	./speller texts/lalaland.txt

c:
	rm -f speller
	make speller


# make a --silent && ./speller texts/lalaland.txt

# diff -y lala.txt keys/lalaland.txt > laladiffs.txt

# make c && ./speller texts/lalaland.txt > lala.txt