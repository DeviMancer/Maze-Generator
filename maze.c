#include "maze.h"
#include <ncurses.h>
#include <stdio.h>
//#include <conio.h>

void maze_print()
{
    //Supongamos que queremos un laberinto de 5x5
    size_t x = 5;     
    size_t y = 5;

    // Usamos ncurses.
    initscr();
    
    WINDOW * win = newwin(y*2 + 1, x*4 + 1, 0, 0);
    refresh();

    for(size_t i = 0; i < y; ++i)
    {
	// Linea de + + + + + +
        for(size_t j = 0; j < 2*x + 1; ++j) wprintw(win, "+ ");
	//wprintw(win, "\n");

	// Linea de vertices +    +    +
	for(size_t k = 0; k < x; ++k) wprintw(win, "   +"); 
	//wprintw(win, "+\n");
    }
   
    for(size_t j = 0; j < 2*x + 1; ++j) wprintw(win, "+ "); // ** Imprime linea temporal divisora.
    //wprintw(win, "\n\n");

    // Crea una caja donde el borde esta formado por el caracter c.
    char c = '+';

    box(win, 0, 0);
    wborder(win, (int)c, (int)c, (int)c, (int)c, (int)c, (int)c, (int)c, (int)c);
    wrefresh(win);

    //TO-DO: Que el borde top y bottom tengan coherencia con la estetica.
    //
    getch();
    endwin();
}
