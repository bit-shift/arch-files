#include <ncurses.h>

WINDOW *create_window(int height, int width, int startx, int starty);

int main (int argc, char *argv[]) {
	WINDOW *my_win;
	int startx, starty, width, height;
	char ch;

	initscr();
	cbreak();
	noecho();

	height = 3;
	width = 10;
	starty = (LINES - height)/2;
	startx = (COLS - width)/2;
	printw("Press q to quit\n");
	refresh();
	my_win = create_window(height, width, startx, starty);
	
	while ((ch = getch()) != 'q') {
		printw("You pressed %c\n", ch);
	}

	endwin();
	return 0;
}

WINDOW *create_window(int height, int width, int startx, int starty) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);

	wrefresh(local_win);

	return local_win;
}
