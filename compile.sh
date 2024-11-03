#!/usr/bin/env sh
gcc -O0 -Wall -Wextra -Werror -Wfatal-errors -std=c17 -pedantic -c graph.c -o graph.o
gcc -O0 -Wall -Wextra -Werror -Wfatal-errors -std=c17 -pedantic -c matrix.c -o matrix.o
gcc -O0 -Wall -Wextra -Werror -Wfatal-errors -std=c17 -pedantic -c maze.c -o maze.o
gcc -O0 -Wall -Wextra -Werror -Wfatal-errors -std=c17 -pedantic maze.o matrix.o graph.o main.c -o laberinto -lncurses

