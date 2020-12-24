#include <ncurses.h>

int main(){
	char ch;

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	printw("Type any character to see it in bold\n");
	refresh();
	ch = getch();
	
	while (ch != 'q'){
		printw("The pressed key was: ");
		attron(A_BOLD);
		printw("%c\n", ch);
		attroff(A_BOLD);
		refresh();
		ch = getch();
	}

	clear();
	printw("it in bold\n");
	refresh();
	ch = getch();

	while (ch != 'q'){
		printw("The pressed key was: ");
		attron(A_BOLD);
		printw("%c\n", ch);
		attroff(A_BOLD);
		refresh();
		ch = getch();
	}
	endwin();

	return 0;
}
