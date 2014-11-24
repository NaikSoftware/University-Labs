/*
 * File:   main.cpp
 * Author: Naik
 *
 * Created on November 16, 2014, 1:11 PM
 *
 * Програма для формування генеaлогічного дерева
 */

#include <cstdlib>
#include <cstring>
#include <curses.h>
#include <form.h>
#include <panel.h>
#include <locale>
#include <vector>
#include <iterator>
#include <algorithm>

#define KEY_ESC 27
#define KEY_ENTER 10

using namespace std;

const char *PROGRAM = "Генеалогічне дерево 1.0";
const char *HELP = "Стрілки - перемикання між вузлами, ENTER - додати новий, DELETE - видалити, Ctrl+Стрілки - переміщення, ESC - вихід";
const char *INPUT_DATA = "Введіть ім’я і т.п.";
const int WAIT = 0, ADD = 1, REMOVE = 2;
const int NODE_W = 17, NODE_H = 2;

typedef struct NodeStruct Node;
struct NodeStruct {
    Node *parent;
    vector<Node*> childrens;
    char *name;
    WINDOW *w;
};

WINDOW *new_wnd(int, int, int, int, int);
WINDOW *new_node_wnd(WINDOW*);
void drawNodes(Node*, Node*);


int main(int argc, char** argv) {
    // Init
    setlocale(LC_ALL, "");
    initscr();
    cbreak(); //buff off
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    int w = getmaxx(stdscr), h = getmaxy(stdscr);

    /* Заголовок в корневому вікні */
    clear();
    mvprintw(0, w / 2 - strlen(PROGRAM) / 3, PROGRAM);
    mvprintw(1, w / 2 - strlen(HELP) / 3, HELP);

    WINDOW *winMain = new_wnd(w, h-2, 0, 2, 1); // отступ для заголовка
    WINDOW *winAdd = new_wnd(w/3, h/4, w/2 - w/8, h/2 - h/8, 3);
    keypad(winAdd, TRUE);

    FIELD *field[2];
    field[0] = new_field(NODE_H, NODE_W, 1, w/6-NODE_W/2, 0, 0);// h, w, y, x
    field[1] = NULL;
    set_field_back(field[0], COLOR_PAIR(2));

    FORM *form = new_form(field);
    int windH, windW;
    scale_form(form, &windH, &windW);

    set_form_win(form, winAdd);
    set_form_sub(form, derwin(winAdd, windH, windW, 2, 1));

    mvwprintw(winAdd, 1, getmaxx(winAdd)/2 - strlen(INPUT_DATA)/3, INPUT_DATA);

    post_form(form);

    PANEL *panels[2], *topPan;
    panels[0] = new_panel(winAdd);
    panels[1] = new_panel(winMain);
    set_panel_userptr(panels[0], panels[1]);
    set_panel_userptr(panels[1], panels[0]);
    update_panels();
    doupdate();
    topPan = panels[1];
    // Main cycle
    Node *curr = NULL, *root = NULL;
    int key, type = WAIT, x, y;
    while(1) {
        key = wgetch(winAdd);
        //mvwprintw(winMain, 10, 10, "Key pressed %d", key);
        if (type == WAIT) { // open new window and input
            if (key == KEY_ENTER) {
                topPan = (PANEL*) panel_userptr(topPan);
                top_panel(topPan);
                type = ADD;
            } else if (key == KEY_UP && curr != root) {
                curr = curr->parent;
                box(winMain, 0, 0);
                drawNodes(root, curr);
            } else if (key == KEY_DOWN && !curr->childrens.empty()) {
                curr = curr->childrens[0];
                box(winMain, 0, 0);
                drawNodes(root, curr);
            } else if ((key == KEY_LEFT || key == KEY_RIGHT) && curr != root) {
                vector<Node*> v = curr->parent->childrens;
                vector<Node*>::iterator it = std::find_if(v.begin(), v.end(), [curr](Node* n){ return n == curr; });
                int idx = distance(v.begin(), it);
                if (idx > 0 && key == KEY_LEFT) curr = curr->parent->childrens[idx - 1];
                else if (idx < (v.size() - 1) && key == KEY_RIGHT) curr = curr->parent->childrens[idx + 1];
                box(winMain, 0, 0);
                drawNodes(root, curr);
            } else if (key == KEY_ESC) break;
        } else if (type == ADD) {
            if (key == KEY_ENTER) {
                form_driver(form, REQ_END_LINE);
                Node *n = (Node*)calloc(1, sizeof(Node));
                char *buff = field_buffer(field[0], 0);
                n->name = (char*)calloc(strlen(buff), sizeof(char));
                copy(buff, buff + strlen(buff), n->name);
                n->w = new_node_wnd(winMain);
                if (root) {
                    n->parent = curr;
                    getparyx(curr->w, y, x);
                    mvderwin(n->w, y + NODE_H + 2, x + curr->childrens.size() * (NODE_W + 4));
                    curr->childrens.push_back(n);
                } else {
                    mvderwin(n->w, 1, w/2);
                    root = n;
                }
                curr = n;
                box(winMain, 0, 0);
                drawNodes(root, curr);
                set_field_buffer(field[0], 0, "");
                topPan = (PANEL*) panel_userptr(topPan);
                top_panel(topPan);
                type = WAIT;
            } else if (key == KEY_ESC) {
                topPan = (PANEL*) panel_userptr(topPan);
                top_panel(topPan);
                type = WAIT;
            } else if (key == 263) form_driver(form, REQ_DEL_PREV);//backspace pressed
            form_driver(form, key);
        }
        update_panels();
        doupdate();
    }
    endwin();
    return (EXIT_SUCCESS);
}

void drawNodes(Node *node, Node *focused) {
    if (!node) return;
    for (int i = 0; i < node->childrens.size(); i++) drawNodes(node->childrens[i], focused);
    WINDOW *wnd = node->w;
    if (node == focused) wbkgdset(wnd, COLOR_PAIR(3));
    else wbkgdset(wnd, COLOR_PAIR(1));
    wclear(wnd);
    wmove(wnd, 1, 1);// move cursor
    wprintw(wnd, node->name);
    box(wnd, 0, 0);
}

WINDOW* new_node_wnd(WINDOW *parent) {
    WINDOW* w = derwin(parent, NODE_H + 2, NODE_W + 2, 0, 0);
    return w;
}

WINDOW *new_wnd(int w, int h, int toX, int toY, int color) {
    WINDOW *wind = newwin(h, w, toY, toX);
    wbkgdset(wind, COLOR_PAIR(color));
    wclear(wind);
    box(wind, 0, 0);
    return wind;
}
