#include "maze.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>

void maze_print()
{
    //Supongamos que queremos un laberinto de 5x5
    size_t x = 8;     
    size_t y = 8;

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

    

    //***** Imprime el minotauro en el centro. *****//
    size_t maxX, maxY, offSetX, offSetY;
    getmaxyx(win, maxY, maxX);

    //** Si las dimensiones del laberinto son par, desplaza aparicion del minotauro.
    offSetX = (x % 2 == 0) ? -2 : 0;
    offSetY = (y % 2 == 0) ? -1 : 0;

    //** Seleccionamos las coordenadas centrales, donde aparecera el minotauro.
    size_t minotaurPositionX = maxX/2 + offSetX;
    size_t minotaurPositionY = maxY/2 + offSetY;

    //** Imprimimos por primera vez el minotauro.
    mvwprintw(win, minotaurPositionY, minotaurPositionX, "M"); 
    wrefresh(win);



    //***** Caminata aleatoria. *****//
    getch();

    //** Caminata aleatoria.
    enum minotaurMovement {IZQUIERDA, DERECHA, ARRIBA, ABAJO};

    srand(time(0));
    size_t minotaurMovement;


    //******************** HACER FUNCION minotaurTouchesBorder()
    
     bool minotaurTouchesBorder(WINDOW * window, size_t minotaurPosY, size_t minotaurPosX)
     {
	size_t maxX, maxY;
	getmaxyx(window, maxY, maxX);

	if( minotaurPosX == 2 || minotaurPosX == maxX-3 || minotaurPosY == 1 || minotaurPosY == maxY-2 ) return true;
	
	return false;
     }


    ///********************
    
    while( !minotaurTouchesBorder(win, minotaurPositionY, minotaurPositionX) ){ 
        //** Elimina rastro de la posicion anterior del minotauro
	mvwprintw(win, minotaurPositionY, minotaurPositionX, " ");
	wrefresh(win);

	//** Elige una direccion y crea el pasillo.
	minotaurMovement = rand() % 4;
	
	switch(minotaurMovement)
    	{
            case IZQUIERDA:
		if(minotaurPositionX > 2) 
		{
	            mvwprintw(win, minotaurPositionY, minotaurPositionX-2, " ");
		    minotaurPositionX -= 4;
		}
		break;

	    case DERECHA:
		if(minotaurPositionX < maxX-3){
	 	    mvwprintw(win, minotaurPositionY, minotaurPositionX+2, " ");
		    minotaurPositionX += 4;
		}
		break;

	    case ARRIBA:
		if(minotaurPositionY > 1){
		    mvwprintw(win, minotaurPositionY-1, minotaurPositionX, " ");
	 	    minotaurPositionY -= 2;
		}
		break;

	    case ABAJO:
		if(minotaurPositionY < maxY-2){
		    mvwprintw(win, minotaurPositionY+1, minotaurPositionX, " ");
		    minotaurPositionY += 2;
		}
		break;

	    default:
		printw("What?");
    	}

	//** Imprime la nueva posicion del minotauro.
	mvwprintw(win, minotaurPositionY, minotaurPositionX, "M");
	wrefresh(win);
	getch();
	//napms(500);



	/* DEBUG 
	 mvwprintw(stdscr, 15, 15, "maxX: %ld", maxX);
	mvwprintw(stdscr, 16, 15, "posX: %ld", minotaurPositionX);
	mvwprintw(stdscr, 17, 15, "maxY: %ld", maxY);
	mvwprintw(stdscr, 18, 15, "posY: %ld", minotaurPositionY);

	*/
    }

    getch();
    endwin();
}
