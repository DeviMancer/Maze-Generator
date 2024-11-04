#include <stdio.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

//#include "maze.h"
//#include <ncurses.h>

int ceil_div(int numerator, int denominator);

int main(){
    
    
    //Supongamos que queremos un laberinto de 3x3
    size_t x = 5;     
    size_t y = 5;

    graph_t * graph = new_graph(x*y);



    //***** Creamos una cuadricula para el laberinto. *****//
    //** Inicializamos una ventana en ncurses.
    initscr();  
    curs_set(0);

    WINDOW * win = newwin(y*2 + 1, x*4 + 1, 0, 0); 
    refresh();

    //** Crea la cuadricula interna del laberinto.
    for(size_t i = 0; i < y; ++i)
    {
	// Linea de + + + + + +
        for(size_t j = 0; j < 2*x + 1; ++j) wprintw(win, "+ ");

	// Linea de vertices +    +    +
	for(size_t k = 0; k < x; ++k) wprintw(win, "   +"); 
    }
   
    for(size_t j = 0; j < 2*x + 1; ++j) wprintw(win, "+ "); // ** Imprime linea temporal divisora. Necesaria (?)

    //** Crea los bordes del laberinto.
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

    //** Obtenemos el vertice donde se encuentra el minotauro.    TODO: PUEDE SER FUNCION
    size_t rowOfMinotaur, colOfMinotaur;
    rowOfMinotaur = (y % 2 == 0) ? y/2 : (size_t)ceil_div(y, 2);
    colOfMinotaur = (x % 2 == 0) ? x/2 : (size_t)ceil_div(x, 2);

    size_t verticeMinotaurAt = x * (rowOfMinotaur-1) + colOfMinotaur;
    //printf("Iniciamos en %ld", verticeMinotaurAt);


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
    matrix_set(graph->adj, verticeMinotaurAt-1, verticeMinotaurAt-1, 1);


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
	            mvwprintw(win, minotaurPositionY, minotaurPositionX-2, " "); // Removemos la pared por donde cruza el minotauro.
		    minotaurPositionX -= 4; // Actualizamos la posicion del minotauro.
		    graph_connect(graph, verticeMinotaurAt, verticeMinotaurAt-1); // Creamos una arista entre anterior posicion con nueva posicion
		    //printf("De %ld a %ld\n", verticeMinotaurAt, verticeMinotaurAt-1); // Debug line
		    --verticeMinotaurAt; // Actualizamos vertice donde se encuentra el minotauro.
		}
		break;

	    case DERECHA:
		if(minotaurPositionX < maxX-3){
	 	    mvwprintw(win, minotaurPositionY, minotaurPositionX+2, " ");
		    minotaurPositionX += 4;
		    graph_connect(graph, verticeMinotaurAt, verticeMinotaurAt+1);
		    //printf("De %ld a %ld\n", verticeMinotaurAt, verticeMinotaurAt+1); 
		    ++verticeMinotaurAt;
		}
		break;

	    case ARRIBA:
		if(minotaurPositionY > 1){
		    mvwprintw(win, minotaurPositionY-1, minotaurPositionX, " ");
	 	    minotaurPositionY -= 2;
		    graph_connect(graph, verticeMinotaurAt, verticeMinotaurAt-x);
		    //printf("De %ld a %ld\n", verticeMinotaurAt, verticeMinotaurAt-x); 
		    verticeMinotaurAt -= x;
		}
		break;

	    case ABAJO:
		if(minotaurPositionY < maxY-2){
		    mvwprintw(win, minotaurPositionY+1, minotaurPositionX, " ");
		    minotaurPositionY += 2;
		    graph_connect(graph, verticeMinotaurAt, verticeMinotaurAt+x);
		    //printf("De %ld a %ld\n", verticeMinotaurAt, verticeMinotaurAt+x); 
		    verticeMinotaurAt += x;
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
    //matrix_set(graph->adj, 1, 1, 1);

    endwin();
    
    //matrix_set(graph->adj, verticeMinotaur
    matrix_print(graph->adj);
    printf("Vertice of M: %ld", verticeMinotaurAt);

    return 0;
}

int ceil_div(int numerator, int denominator) {
    return (numerator + denominator - 1) / denominator;
}
