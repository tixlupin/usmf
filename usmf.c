#include <ncurses.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "usmf.h"

int
print_momowasa(int x, int y)
{
	char *momowasa[] = {
		USMF1,
		USMF2,
		USMF3,
		USMF4,
		USMF5,
		USMF6
	};
	char *momowasa_leg[2];
	char *p;
	int a, i;

	if (x & 0x08) {
		momowasa_leg[0] = strdup(USMF_LEG11);
		momowasa_leg[1] = strdup(USMF_LEG12);
	} else {
		momowasa_leg[0] = strdup(USMF_LEG21);
		momowasa_leg[1] = strdup(USMF_LEG22);
	}

	clear();
	for (a = 0; a < USMF_BODY_HEIGHT; a++) {
		i = 0;
		p = momowasa[a];
		if (x >= 0)
			move(a + y, x);
		else {
			move(a + y, 0);
			if (-x > strlen(momowasa[a]))
				continue;
			p += -x;
		}
		while (*p != '\0') {
			if ((x + i) >= COLS)
				break;
			printw("%c", *p);
			i++;
			p++;
		}
	}

	for (a = 0; a < USMF_LEG_HEIGHT; a++) {
		i = 0;
		p = momowasa_leg[a];
		if (x >= 0)
			move(a + y + USMF_BODY_HEIGHT, x);
		else {
			move(a + y + USMF_BODY_HEIGHT, 0);
			if (-x > strlen(momowasa_leg[a]))
				goto end;
			p += -x;
		}
		while (*p != '\0') {
			if ((x + i) >= COLS)
				break;
			printw("%c", *p);
			i++;
			p++;
		}
	}

end:
	free(momowasa_leg[0]);
	free(momowasa_leg[1]);
	return 0;
}


int
main(void)
{
	int i;
	int max_width = strlen(USMF5);
	int y;

	setlocale(LC_ALL, "");
	initscr();
	noecho();
	y = ((LINES - 1) / 2) - (USMF_HEIGHT / 2);

	for (i = COLS - 1; i > -max_width; i--) {
		print_momowasa(i, y);
		refresh();
		usleep(30000);
	}

	endwin();

	return 0;
}
