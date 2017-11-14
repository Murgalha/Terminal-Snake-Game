#include <ncurses.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    return ch;

    return 0;
}

int is_valid(char c) {
    if(c == 'w' || c == 'a' || c == 's' || c == 'd')
        return 1;
    return 0;
}

void init_colors() {
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_RED, 700, 0, 0);
    init_color(COLOR_GREEN, 0, 700, 0);
    init_color(COLOR_BLUE, 0, 0, 500);
    init_color(COLOR_GREY, 700, 700, 700);
}

void init_pairs() {
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_WHITE);
    init_pair(4, COLOR_RED, COLOR_GREY);
    init_pair(5, COLOR_BLUE, COLOR_WHITE);
    init_pair(6, COLOR_BLACK, COLOR_GREY);
}
