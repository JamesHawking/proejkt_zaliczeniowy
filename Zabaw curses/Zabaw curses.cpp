// Zabaw curses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "curses.h"
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;
int x = 30, y = 28;
int przeciwnikX, przeciwnikY;
int punkty = 0;
int iloscPrzeciwnikow = 500;
int tymczasowaPozcjaY[500];
int tymczasowaPozcjaX[500];


char *choices[] = {
	"Start gry",
	"Instrukcja",
	"Wyjscie",
};
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
void menu();
void oknoGry();
void oknoPomocy();
int strzelaj(int y, int x);
void generujBanana();
void detekcjaKolizji();
void sterowanie();
void input();
void logic();

int main()
{
	srand(time(NULL));
	 menu();
	return 0;
}

void menu()
{
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	clear();
	noecho();
	cbreak();   /* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(22, 10, "Uzyj strzalek by podswietlic wybor, zatwierdz enterem.");
	refresh();
	print_menu(menu_win, highlight);
	while (1)
	{
		c = wgetch(menu_win);
		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = n_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == n_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case 10:
			choice = highlight;
			break;
		default:
			mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
			refresh();
			break;
		}
		print_menu(menu_win, highlight);
		if (choice != 0) /* User did a choice come out of the infinite loop */
			break;
	}

	switch (choice)
	{
	case 1:
		oknoGry();
		//oknoPomocy();
		break;
	}

	refresh();
	endwin();

}
void oknoGry() 
{
		WINDOW *gra;
		
		initscr();
		curs_set(0);
		start_color();
		clear();
		refresh();
		oknoPomocy();
		gra = newwin(0,90,0,0);
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
		wbkgd(gra, COLOR_PAIR(2));
		int statek = 208;
		int ch;
		keypad(gra, TRUE);
		box(gra, 0, 0);
		attron(COLOR_PAIR(2));
		mvprintw(0, 1, "|Gwiezdny dezintegrator bananow|");
		mvprintw(y, x, "^");
		wrefresh(gra);
		//Generowanie Bananow!
		generujBanana();
	//Glowna petla, wyjscie po wcisnieciu q.
		while ((ch=getch()) != 'q')
		{
			
			switch (ch)
			{
				//case 'W':
				//case 'w':
				//	mvwdelch(gra, y, x);
				//	y--;
				//	mvprintw(y, x, "O");
				//	break;
			case 'A':
			case 'a':
				x--;
				if (x > 9)
				{
					mvprintw(y, x, "^");
					mvprintw(y, x + 1, " ");
				}
				else {
					x++;
				}
				

				//mvwaddch(gra, y, x, 'O');
				//move(y, x);
				

	
				break;
			//case 's':
			//case 'S':
			//	mvwdelch(gra, y, x);
			//	y++;
			//	mvprintw(y, x, "O");
			//	break;
			case 'D':
			case 'd':
				x++;
				if (x < 'Y')
				{
				mvprintw(y, x, "^");
				mvprintw(y, x - 1, " ");
				}
				else {
					x--;
				}
				break;
			case 'S':
			case 's':
				strzelaj(y, x);
				break;
			}
			mvprintw((y / 2) + 7, 92, "%c", x);
			
			mvprintw((y / 2) + 10, 92, "statekY = %d", y);
			mvprintw((y / 2) + 11, 92, "statekX = %d", x);
			wrefresh(gra);
			
		}
		
		delwin(gra);

		endwin();
}
void oknoPomocy()
{
	WINDOW *pomoc;

	initscr();
	curs_set(0);
	start_color();

	
	int przesuniecie_tekstu = 92;

	clear();
	refresh();
	//pomoc = newwin(92, 120, 0, 0);
	//box(pomoc, 0, 0);
	mvprintw((y / 2) - 10, przesuniecie_tekstu, "     .-.");
	mvprintw((y / 2) - 9, przesuniecie_tekstu, "    /  |");
	mvprintw((y / 2) - 8, przesuniecie_tekstu, "    |  /");
	mvprintw((y / 2) - 7, przesuniecie_tekstu, " .'\|.-; _");
	mvprintw((y / 2) - 6, przesuniecie_tekstu, "/.-.;\  |\|");
	mvprintw((y / 2) - 5, przesuniecie_tekstu, " '  |'._/ `");
	mvprintw((y / 2) - 3, przesuniecie_tekstu, "    \  |");
	mvprintw((y/2)-1, przesuniecie_tekstu, "Pomoc:");
	mvprintw(y/2, przesuniecie_tekstu, "A - lewo");
	mvprintw((y / 2) + 1, przesuniecie_tekstu, "D - prawo");
	mvprintw((y / 2) + 2, przesuniecie_tekstu, "S - strzal");
	mvprintw((y / 2)+3, przesuniecie_tekstu, "Q - wyjscie");
	
	
	refresh();

	


}

int strzelaj(int y, int x)
{
	
	int strzalY = y, strzalX = x;
	for (int i=0; i < y-1; i++) {
		refresh();
		strzalY--;
		mvprintw(strzalY, strzalX, "|");
		Sleep(25);
		mvprintw(strzalY+1, strzalX, " ");
		mvprintw(y, x, "^");
		mvprintw((y / 2) + 8, 92, "strzalY = %d", y);
		mvprintw((y / 2) + 9, 92, "strzalX = %d", x);
		//Petla spradza czy nastapilo trafenie, jezeli tak, to dodaje punkty.
		for (int j=0; j < iloscPrzeciwnikow; j++) {
			if (tymczasowaPozcjaX[j] == strzalX && tymczasowaPozcjaY[j] == strzalY) {
				punkty++;
				tymczasowaPozcjaX[j] = 501; // Zmiana koordynatow zeby petla nie naliczala podwojnego trafienia.
				tymczasowaPozcjaY[j] = 502; // Zmiana koordynatow zeby petla nie naliczala podwojnego trafienia.
			}
				
			
				
		}
			
		mvprintw((y / 2) + 6, 92, "Punkty: %d", punkty);
	}
	mvprintw(strzalY, strzalX, " ");
	return 1;
}

void generujBanana()
{
	

	for (int i = 0; i < iloscPrzeciwnikow; i++)
	{
		refresh();
		tymczasowaPozcjaY[i] = przeciwnikY = ((std::rand() % 24) + 2);
		tymczasowaPozcjaX[i] = przeciwnikX = ((std::rand() % 80) + 2);
		mvprintw(przeciwnikY, przeciwnikX, "B");
		mvprintw((y / 2) + 10, 92, "PrzeciwnikX %d", przeciwnikX);
		mvprintw((y / 2) + 11, 92, "PrzeciwnikY %d", przeciwnikY);
		Sleep(10);
		
	}
	
	
}



void detekcjaKolizji()
{

	



}

void logic()
{
	


}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for (i = 0; i < n_choices; ++i)
	{
		if (highlight == i + 1) /* High light the present choice */
		{
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}