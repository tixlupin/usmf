#include <ncurses.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "usmf.h"

int
print_momowasa(int x, int y, int type)
{
	char *momowasa_body[USMF_BODY_HEIGHT];
	char *momowasa_leg[USMF_LEG_HEIGHT];
	char *p;
	int a, i;

	switch (type) {
	case USMF_NORMAL:
		momowasa_body[0] = strdup(USMF1);
		momowasa_body[1] = strdup(USMF2);
		momowasa_body[2] = strdup(USMF3);
		momowasa_body[3] = strdup(USMF4);
		momowasa_body[4] = strdup(USMF5);
		momowasa_body[5] = strdup(USMF6);
		break;
	case USMF_CENTER1:
		momowasa_body[0] = strdup(USMF1);
		momowasa_body[1] = strdup(USMF2);
		momowasa_body[2] = strdup(USMF3);
		momowasa_body[3] = strdup(USMF4);
		momowasa_body[4] = strdup(USMF5A);
		momowasa_body[5] = strdup(USMF6A);
		break;
	case USMF_CENTER2:
		momowasa_body[0] = strdup(USMF1);
		momowasa_body[1] = strdup(USMF2);
		momowasa_body[2] = strdup(USMF3);
		momowasa_body[3] = strdup(USMF4);
		momowasa_body[4] = strdup(USMF5A);
		momowasa_body[5] = strdup(USMF6B);
		break;
	};

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
		p = momowasa_body[a];
		if (x >= 0)
			move(a + y, x);
		else {
			move(a + y, 0);
			if (-x > strlen(momowasa_body[a]))
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
	refresh();
	for (a = 0; a < USMF_BODY_HEIGHT; a++)
		free(momowasa_body[a]);
	for (a = 0; a < USMF_LEG_HEIGHT; a++)
		free(momowasa_leg[a]);
	return 0;
}


int
main(void)
{
	int i;
	int max_width = strlen(USMF5);
	int y;
	int lucky;

	srand((unsigned)time(NULL));
	lucky = rand() % 10;

	setlocale(LC_ALL, "");
	initscr();
	noecho();
	y = ((LINES - 1) / 2) - (USMF_HEIGHT / 2);

	for (i = COLS - 1; i >= -max_width; i--) {
		print_momowasa(i, y, USMF_NORMAL);
		if (lucky == 0 && i == ((COLS / 2) - (max_width / 2))) {
			sleep(1);
			print_momowasa(i, y, USMF_CENTER1);
			sleep(1);
			print_momowasa(i, y, USMF_CENTER2);
			sleep(1);
		}
		usleep(30000);
	}

	endwin();

	return 0;
}
