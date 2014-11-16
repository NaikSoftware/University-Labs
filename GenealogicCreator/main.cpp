/*
 * File:   main.cpp
 * Author: Naik
 *
 * Created on November 16, 2014, 1:11 PM
 *
 * Програма для формування генеологічного дерева
 */

#include <cstdlib>
#include <cstring>
#include <curses.h>
#include <form.h>
#include <locale>

#define KEY_ESC 27
#define KEY_ENTER 10

using namespace std;

const char *PROGRAM = "Генеалогічне дерево 1.0";
const char *HELP = "Стрілки - перемикання між вузлами, ENTER - додати новий, DELETE - видалити, Ctrl+Стрілки - переміщення, ESC - вихід";
const char *INPUT_DATA = "Введіть ім’я і т.п.";
const int WAIT = 0, ADD = 1, REMOVE = 2;

struct NodeStruct {
    struct NodeStruct *parents;
    struct NodeStruct *childrens;
    int chCount;
    chtype *name;
    chtype *age;
};
typedef struct NodeStruct Node;

WINDOW *new_wnd(int, int, int, int, int);

int main(int argc, char** argv) {
    // Init
    setlocale(LC_ALL, "");
    initscr();
    cbreak(); //buff off
    keypad(stdscr, TRUE);
    noecho();
    int w = getmaxx(stdscr), h = getmaxy(stdscr);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    bkgdset(COLOR_PAIR(1));
    clear();
    box(stdscr, 0, 0);
    mvprintw(1, w / 2 - strlen(PROGRAM) / 3, PROGRAM);
    bkgdset(COLOR_PAIR(2));
    mvprintw(2, w / 2 - strlen(HELP) / 3, HELP);
    refresh();

    // Main cycle
    int key, type = WAIT;

    FIELD *field[3];
    field[0] = new_field(4, 10, 4, 18, 0, 0);
    field[1] = NULL;
    set_field_back(field[0], COLOR_PAIR(2));
    FORM *form = new_form(field);
    int windH = 10, windW = 10;
    scale_form(form, &windH, &windW);
    //post_form(form);
    refresh();
    WINDOW *wind;
    while((key = getch()) != KEY_ESC) {
        mvprintw(10, 10, "Key pressed %d", key);
        if (key == KEY_ENTER) {
            if (type == WAIT) { // open new window and input
                wind = new_wnd(w/4, h/4, w/2 - w/8, h/2 - h/8, 3);
                mvwprintw(wind, 2, getmaxx(wind)/2 - strlen(INPUT_DATA)/3, INPUT_DATA);
                //set_form_win(form, wind);
                //set_form_sub(form, derwin(wind, 3, 8, 2, 2));
                post_form(form);
                refresh();
                wrefresh(wind);
            }
        }
        if (key == 263) form_driver(form, REQ_DEL_PREV);
        form_driver(form, key);
    }
    endwin();
    return (EXIT_SUCCESS);
}

WINDOW *new_wnd(int w, int h, int toX, int toY, int color) {
    WINDOW *wind = newwin(h, w, toY, toX);
    wbkgdset(wind, COLOR_PAIR(color));
    wclear(wind);
    box(wind, 0, 0);
    wrefresh(wind);
    return wind;
}

