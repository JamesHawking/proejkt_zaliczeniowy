// Zabaw curses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "curses.h"
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;
int x = 30, y = 28;
int przeciwnikX, przeciwnikY;
int punkty = 0;
int iloscPrzeciwnikow = 250;
int iloscWrogow = iloscPrzeciwnikow; //Dla statystyki w funkcji strzelaj, bez wplywu na zmienna iloscPrzeciwnikow.
int tymczasowaPozcjaY[500];
int tymczasowaPozcjaX[500];


char *choices[] = {
	"Start gry",
	"Instrukcja (nie zrobiona)",
	"Wyjscie",
};
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
void menu();
void oknoGry();
void oknoPomocy();
int strzelaj(int y, int x);
void generujBanana();
void wygrana();
void generujBossa();
void animujBanana();

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
	int przesuniecie_tekstu = 65;
	initscr();
	clear();
	noecho();
	cbreak();   /* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	start_color();
	attron(A_BOLD);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	mvprintw(22, 10, "Uzyj strzalek by podswietlic wybor, zatwierdz enterem.");
	mvprintw((y / 2) - 13, przesuniecie_tekstu, "     ____                           ___");
	mvprintw((y / 2) - 12, przesuniecie_tekstu, "    |  _ \  ___              _   _.' _ `.");
	mvprintw((y / 2) - 11, przesuniecie_tekstu, " _  | [_) )' _ `._   _  ___ ! \ | | (_) |    _");
	mvprintw((y / 2) - 10, przesuniecie_tekstu, "|:;.|  _ <| (_) | \ | |' _ `|  \| |  _  |  .:;|");
	mvprintw((y / 2) - 9, przesuniecie_tekstu, "|   `.[_) )  _  |  \| | (_) |     | | | |.',..|");
	mvprintw((y / 2) - 8, przesuniecie_tekstu, " :.   `. /| | | |     |  _  | |\  | | |.' :;:: ");
	mvprintw((y / 2) - 7, przesuniecie_tekstu, "!::;       :; : !.!.\_!_!_!.!- '-':; : ''    '''!");
	mvprintw((y / 2) - 6, przesuniecie_tekstu, "';:'        `::;::;'             ''     .,  .");
	mvprintw((y / 2) - 5, przesuniecie_tekstu, "  `:     .,.    `'    .::... .      .::;::;'");
	mvprintw((y / 2) - 4, przesuniecie_tekstu, "     `..:;::;:..      ::;::;:;:;,    :;::;'");
	mvprintw((y / 2) - 3, przesuniecie_tekstu, "         - :; ::; :; : ':;::;:''     ;.-'");
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
		oknoPomocy();
		refresh();
		gra = newwin(0,90,0,0);
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
		wbkgd(gra, COLOR_PAIR(2));
		int statek = 208;
		int ch;
		keypad(gra, TRUE);
		box(gra, 0, 0);
		attron(COLOR_PAIR(2));
		attron(A_BOLD);
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
					attron(A_BOLD);
					init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
					attron(COLOR_PAIR(2));
					mvprintw(y, x, "^");
					mvprintw(y, x + 1, " ");
				}
				else {
					x++;
				}
				
				animujBanana();
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
				attron(A_BOLD);
				init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
				attron(COLOR_PAIR(2));
				mvprintw(y, x, "^");
				mvprintw(y, x - 1, " ");
				}
				else {
					x--;
				}
				animujBanana();
				break;
			case 'S':
			case 's':
				strzelaj(y, x);
				//animujBanana();
				break;
			}
			
		//mvprintw((y / 2) + 7, 92, "%i", x);	
		//	mvprintw((y / 2) + 10, 92, "statekY = %d", y);
		//	mvprintw((y / 2) + 11, 92, "statekX = %d", x);
			
			wygrana();
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
	int przesuniecie_tekstu = 100;
	clear();
	refresh();
	pomoc = newwin(0, 0, 0, 90);
	box(pomoc, 0, 0);
	wrefresh(pomoc);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	mvprintw((y / 2) - 10, przesuniecie_tekstu, "   /\\   ");
	mvprintw((y / 2) - 9, przesuniecie_tekstu, "  (  )  ");
	mvprintw((y / 2) - 8, przesuniecie_tekstu, "  (  )  ");
	mvprintw((y / 2) - 7, przesuniecie_tekstu, " /|  |\\ ");
	mvprintw((y / 2) - 6, przesuniecie_tekstu, "/_||||_\\ ");

	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));
	mvprintw((y/2)-1, przesuniecie_tekstu, "Pomoc:");
	mvprintw(y/2, przesuniecie_tekstu, "A - lewo");
	mvprintw((y / 2) + 1, przesuniecie_tekstu, "D - prawo");
	mvprintw((y / 2) + 2, przesuniecie_tekstu, "S - strzal");
	mvprintw((y / 2)+3, przesuniecie_tekstu, "Q - wyjscie");
	//mvprintw((y / 2) + 6, 92, "Punkty: %i", punkty);
	//mvprintw((y / 2) + 5, 92, "Wrogowie: %i", iloscWrogow);
	
	
	refresh();

	


}

int strzelaj(int y, int x)
{
	int wysokoscStrzalu = y - 1;
	int strzalY = y, strzalX = x;
	for (int i=1; i < wysokoscStrzalu; i++) 
	{
		refresh();
		strzalY--;
		mvprintw(strzalY, strzalX, "|");
		Sleep(30);
		mvprintw(strzalY+1, strzalX, " ");
		mvprintw(y, x, "^");
		//mvprintw((y / 2) + 8, 92, "strzalY = %d", y);
		//mvprintw((y / 2) + 9, 92, "strzalX = %d", x);
		//Petla spradza czy nastapilo trafenie, jezeli tak, to dodaje punkty.
		for (int j=0; j < iloscPrzeciwnikow; j++) 
		{
			if (tymczasowaPozcjaX[j] == strzalX && tymczasowaPozcjaY[j] == strzalY)
			{
				punkty++;
				iloscWrogow -=1;
				wysokoscStrzalu = 0;
				tymczasowaPozcjaX[j] = 501; // Zmiana koordynatow zeby petla nie naliczala podwojnego trafienia.
				tymczasowaPozcjaY[j] = 502; // Zmiana koordynatow zeby petla nie naliczala podwojnego trafienia.
			}
			
		}
		

		mvprintw(29, 58, "|Punkty: %i", punkty);
		mvprintw(29, 71, "Wrogowie: %i|", iloscWrogow);

		//if (iloscWrogow == 0)
			//mvprintw(15, 30, "WYGRANA");
	}
	mvprintw(strzalY, strzalX, " ");
	return 1;
}

void generujBanana()
{
	

	for (int i = 0; i <= iloscPrzeciwnikow-1; i++) //-1 poniewaz petla leci od 0
	{
		refresh();
		start_color();
		init_pair(1, COLOR_YELLOW, COLOR_BLACK);
		tymczasowaPozcjaY[i] = przeciwnikY = ((std::rand() % 24) + 2);
		tymczasowaPozcjaX[i] = przeciwnikX = ((std::rand() % 70) + 11);
		attron(COLOR_PAIR(1));
		attron(A_BOLD);
		mvprintw(przeciwnikY, przeciwnikX, "B");
		//mvprintw((y / 2) + 10, 92, "PrzeciwnikX %d", przeciwnikX);
		//mvprintw((y / 2) + 11, 92, "PrzeciwnikY %d", przeciwnikY);
		Sleep(10);
		
	}
	
	
}

void animujBanana()
{

	int animujY= 0, animujX= 0;
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	for (int i = 0; i <= iloscPrzeciwnikow - 1; i++)
	{
		if ((x % 2 == 0)) {
			mvprintw(tymczasowaPozcjaY[i], tymczasowaPozcjaX[i], " ");
			tymczasowaPozcjaX[i] = tymczasowaPozcjaX[i]++;
			mvprintw(tymczasowaPozcjaY[i], tymczasowaPozcjaX[i], "B");
		}
		else {
			mvprintw(tymczasowaPozcjaY[i], tymczasowaPozcjaX[i], " ");
			tymczasowaPozcjaX[i] = tymczasowaPozcjaX[i]--;
			mvprintw(tymczasowaPozcjaY[i], tymczasowaPozcjaX[i], "B");
		}


			if (x > 87)
				break;
			
	
		//mvprintw(tymczasowaPozcjaY[i], tymczasowaPozcjaX[i], " ");
		//refresh();
	}
	
		
}

void generujBossa()
{
	std::fstream boss;
	boss.open("boss.txt");
	std::string linia;
	char output[100];
	int offset = 35;
	int k = 10;
	if (boss.is_open())
	{
		while (!boss.eof())
		{

			boss >> linia;
			mvprintw((y / 2) - k, offset, "%s", linia.c_str());
			k--;
		}
	}
	boss.close();
}

void wygrana() 
{
	if (iloscWrogow == 0)
	{
		//generujBossa();
		mvprintw(15, 35, "WYGRANA !!!");
		Sleep(30);
		mvprintw(16, 35, "Wcisnij Q by wyjsc z gry.");
		refresh;
	}
		



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