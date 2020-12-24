#include <ncurses.h>
#include <panel.h>
#include <math.h>

WINDOW *create_window(int height, int width, int startx, int starty);
void format_window(WINDOW *window, char *title);
void highlight_curr_window(WINDOW *window);
void unhighlight_non_curr_window(PANEL *top_p);
void print_window_test(PANEL *panel);

int main(int argc, char *argv[]) {
	initscr();
	start_color();
	use_default_colors();
	cbreak();
	noecho();
	curs_set(0);

	init_pair(1, COLOR_MAGENTA, -1);
	init_pair(2, -1, -1);

	WINDOW *expenditure, *income, *budget, *goals;
	WINDOW *top_win;
	WINDOW *my_windows[4];
	PANEL *my_panels[4];
	PANEL *top_pan;

	expenditure = create_window(floor(5*(LINES/7)), floor(3*(COLS/5)), 0, 0);
	format_window(expenditure, "Expenditure");

	income = create_window(floor(2*(LINES/5)), COLS-ceil(3*(COLS/5)), ceil(3*(COLS/5)), 0);
	format_window(income, "Income");

	budget = create_window(LINES-ceil(2*(LINES/5)), COLS-ceil(3*(COLS/5)), ceil(3*(COLS/5)), ceil(2*(LINES/5)));
	format_window(budget, "Budget");

	goals = create_window(LINES-ceil(5*(LINES/7)), floor(3*(COLS/5)), 0, ceil(5*(LINES/7)));
	format_window(goals, "Goals");

	my_windows[0] = expenditure;
	my_windows[1] = income;
	my_windows[2] = budget;
	my_windows[3] = goals;

	for (int i = 0; i < 4; i++) scrollok(my_windows[i], TRUE);

	for (int i = 0; i < 3; i++) my_panels[i] = new_panel(my_windows[i+1]);
	my_panels[3] = new_panel(my_windows[0]);

	set_panel_userptr(my_panels[0], my_panels[1]);
	set_panel_userptr(my_panels[1], my_panels[2]);
	set_panel_userptr(my_panels[2], my_panels[3]);
	set_panel_userptr(my_panels[3], my_panels[0]);

	top_pan = my_panels[3];
	top_win = panel_window(top_pan);
	highlight_curr_window(top_win);

	update_panels();
	doupdate();

	char ch;
	while ((ch = getch()) != 'q') {
		switch(ch) {
			case 9 :
				top_pan = (PANEL *)panel_userptr(top_pan);
				top_panel(top_pan);
				top_win = (WINDOW *)panel_window(top_pan);
				highlight_curr_window(top_win);
				unhighlight_non_curr_window(top_pan);
				break;
			case 'a' :
				print_window_test(top_pan);
				break;
		}
		update_panels();
		doupdate();
	}
	
	endwin();
	return 0;
}

WINDOW *create_window(int height, int width, int startx, int starty) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	wrefresh(local_win);
	return local_win;
}

void format_window(WINDOW *window, char *title) {
	int row, col;

	box(window, 0, 0);
	mvwprintw(window, 1, 1, "%s", title);
	getmaxyx(window, row, col);
	wmove(window, 2, 1);
	whline(window, 0, col-2);
	wrefresh(window);
}

void highlight_curr_window(WINDOW *window) {
	int row, col;

	wattron(window, COLOR_PAIR (1));
	box(window, 0, 0);
	getmaxyx(window, row, col);
	wmove(window, 2, 1);
	whline(window, 0, col-2);
	wattroff(window, COLOR_PAIR (1));
	wmove(window, 3, 1);
}

void unhighlight_non_curr_window(PANEL *top_p) {
	PANEL *curr;
	WINDOW *currw;
	int row, col;
	curr = (PANEL *)panel_below(top_p);

	while (curr != top_p) {
		currw = panel_window(curr);
		wattron(currw, COLOR_PAIR (2));
		box(currw, 0, 0);
		getmaxyx(currw, row, col);
		wmove(currw, 2, 1);
		whline(currw, 0, col-2);
		wattroff(currw, COLOR_PAIR (2));
		curr = (PANEL *)panel_below(curr);
	}
}

void print_window_test(PANEL *panel) {
	WINDOW *window;
	window = (WINDOW *)panel_window(panel);
	wprintw(window, "Testing focus print\n");
}
