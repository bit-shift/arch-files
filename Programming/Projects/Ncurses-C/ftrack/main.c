#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "menu.h"

int main (int argc, char *argv[]) {
	boot();
	menu();

	return 0;
}

void boot (void) {
	printf("\nWelcome to FTRACK 0.0\n");
}
