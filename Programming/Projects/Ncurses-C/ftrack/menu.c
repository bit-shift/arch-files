#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"

static char *mainmenu[] = {
	"[?b] Budget Menu                   ",
	"[?e] Expenditure Menu              ",
	"[?g] Goals Menu                    ",
	"[?i] Income Menu                   ",
	"[p] Print Statistics               ",
	"[t] Set the Time Period            ",
	"[s] Save                           ",
	"[q] Quit (without saving)          ",
	"[sq] Save and Quit                 ",
	NULL
};

static char *budgetmenu[] = {
	"[ab] Add an Expense                ",
	"[eb] Edit an Expense               ",
	"[rb] Remove an Expense             ",
	"[cb] Add a Budget Category         ",
	"[xb] Edit a Budget Category        ",
	"[db] Remove a Budget Category      ",
	"[pb] Print Budget                  ",
	"[sb] Save Budget                   ",
	NULL
};

static char *expendituremenu[] = {
	"[ae] Add an Expense                ",
	"[ee] Edit an Expense               ",
	"[re] Remove an Expense             ",
	"[ce] Add an Expense Category       ",
	"[xe] Edit an Expense Category      ",
	"[de] Remove an Expense Category    ",
	"[pe] Print Expenses                ",
	"[se] Save Expenses                 ",
	NULL
};

static char *goalsmenu[] = {
	"[ag] Add to a Goal                 ",
	"[rg] Remove from a Goal            ",
	"[cg] Add a Goal                    ",
	"[xg] Edit a Goal                   ",
	"[dg] Remove a Goal                 ",
	"[pg] Print Goals                   ",
	"[sg] Save Goals                    ",
	NULL
};

static char *incomemenu[] = {
	"[ai] Add a Shift                   ",
	"[ei] Edit a Shift                  ",
	"[ri] Remove a Shift                ",
	"[ci] Add a Job                     ",
	"[xi] Edit a Job                    ",
	"[di] Remove a Job                  ",
	"[pi] Print Income                  ",
	"[si] Save Income                   ",
	NULL
};

static void showmenu (char *name, char *menu[]) {
	int options, half, i;
	printf("\n%s\n", name);
	
	options = 0;
	for (i = 0; menu[i]; i++) {
		options++;
	}
	half = (options+1)/2;

	for (i = 0; i < half; i++) {
		printf("    %-36s", menu[i]);
		if (i+half < options) {
			printf("%s", menu[i+half]);
		}
		printf("\n");
	}
	printf("\n");
}
		

static int cmd_mainmenu (int argc, char **argv) {
	(void)argc;
	(void)argv;

	showmenu("FTRACK Main Menu", mainmenu);
	return 0;
}

static int cmd_budgetmenu (int argc, char **argv) {
	(void)argc;
	(void)argv;

	showmenu("FTRACK Budget Menu", budgetmenu);
	return 0;
}

static int cmd_expendituremenu (int argc, char **argv) {
	(void)argc;
	(void)argv;

	showmenu("FTRACK Expenditure Menu", expendituremenu);
	return 0;
}

static int cmd_goalsmenu (int argc, char **argv) {
	(void)argc;
	(void)argv;

	showmenu("FTRACK Goals Menu", goalsmenu);
	return 0;
}

static int cmd_incomemenu (int argc, char **argv) {
	(void)argc;
	(void)argv;

	showmenu("FTRACK Income Menu", incomemenu);
	return 0;
}

static int cmd_quit (int argc, char **argv) {
	(void)argc;
	(void)argv;

	exit(0);
	return 0;
}

static struct {
	char *name;
	int (*func)(int argc, char **argv);
} cmdtable[] = {
	/* menus */
	{ "?",		cmd_mainmenu },
	{ "?b",		cmd_budgetmenu },
	{ "?e",		cmd_expendituremenu },
	{ "?g",		cmd_goalsmenu },
	{ "?i",		cmd_incomemenu },
	{ "q",		cmd_quit },
	{ "s",		cmd_quit },
	{ "sq",		cmd_quit },
	{ NULL, NULL }
};

void menu (void) {
	int i, len, result;
	char buf[64];

	while (1) {
		printf("[? for menu] $ ");
		fgets(buf, sizeof(buf), stdin);
		len = strlen(buf);
		buf[len-1] = '\0';
		for (i = 0; cmdtable[i].name; i++) {
			if (*cmdtable[i].name && !strcmp(buf, cmdtable[i].name)) {
				result = cmdtable[i].func(0, NULL);
				(void) result;
			}
		}
	}
}
