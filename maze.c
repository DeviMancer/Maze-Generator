#include "maze.h"
#include <ncurses.h>
#include <stdio.h>
//#include <conio.h>

void maze_print()
{
    //Supongamos que queremos un laberinto de 5x5
    size_t x = 9;     
    size_t y = 9;

    //***** Usamos ncurses.
    initscr();
    curs_set(0);

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


    //***** Crea una caja donde el borde esta formado por el caracter c.
    //TO-DO: Que el borde top y bottom tengan coherencia con la estetica.
    char c = '+';

    box(win, 0, 0);
    wborder(win, (int)c, (int)c, (int)c, (int)c, (int)c, (int)c, (int)c, (int)c);
    wrefresh(win);

    
    //***** Imprime el minotauro en el centro.
    size_t maxX, maxY, offSetX, offSetY;
    getmaxyx(win, maxY, maxX);

    // Desplazamos el minotauro si las dimensiones del laberinto son par.
    if(x % 2 == 0) offSetX = -2; // Desplazamiento de 2 columnas a la derecha.  
    if(y % 2 == 0) offSetY = -1; // Desplazamiento de 1 renglon hacia arriba.

    mvwprintw(win, maxY/2 + offSetY, maxX/2 + offSetX, "M"); // Imprime el minotauro.
    wrefresh(win);


    getch();
    endwin();
}
