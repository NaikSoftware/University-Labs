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
#include <clocale>
#include <vector>
#include <cwchar>
#include <iterator>
#include <algorithm>

#define KEY_ESC 27
#define KEY_ENTER 10

using namespace std;

const char *PROGRAM = "Генеалогічне дерево 1.0";
const char *HELP = "Стрілки - перемикання між вузлами, ENTER - додати новий, DELETE - видалити, ESC - вихід";
const char *INPUT_DATA = "Введіть ім’я і т.п.";
const int WAIT = 0, ADD = 1, REMOVE = 2;
const int NODE_W = 17, NODE_H = 2, PADDING = 2;

typedef struct NodeStruct Node;

struct NodeStruct {
    Node *parent;
    vector<Node*> childrens;
    char *name;
    WINDOW *w;
};

WINDOW *new_wnd(int, int, int, int, int);
int drawNodes(Node*, Node*, int, int, WINDOW* = 0);
void removeBrunch(Node*);

int main() {
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

    WINDOW *winMain = new_wnd(w, h - 2, 0, 2, 1); // отступ для заголовка
    WINDOW *winAdd = new_wnd(w / 3, h / 4, w / 2 - w / 8, h / 2 - h / 8, 3);
    keypad(winAdd, TRUE);

    FIELD * field[2];
    field[0] = new_field(NODE_H, NODE_W, 1, w / 6 - NODE_W / 2, 0, 0); // h, w, y, x
    field[1] = NULL;
    set_field_back(field[0], COLOR_PAIR(2));

    FORM *form = new_form(field);
    int windH, windW;
    scale_form(form, &windH, &windW);

    set_form_win(form, winAdd);
    set_form_sub(form, derwin(winAdd, windH, windW, 2, 1));

    mvwprintw(winAdd, 1, getmaxx(winAdd) / 2 - strlen(INPUT_DATA) / 3, INPUT_DATA);

    post_form(form);

    PANEL * panels[2], *topPan;
    panels[0] = new_panel(winAdd);
    panels[1] = new_panel(winMain);
    set_panel_userptr(panels[0], panels[1]);
    set_panel_userptr(panels[1], panels[0]);
    update_panels();
    doupdate();
    topPan = panels[1];
    // Main cycle
    Node *curr = NULL, *root = NULL;
    int key, type = WAIT; //, x, y;
    while (1) {
        key = wgetch(winAdd);
        //mvwprintw(winMain, 10, 10, "Key pressed %d", key);
        if (type == WAIT) { // open new window and input
            if (key == KEY_ENTER) {
                topPan = (PANEL*) panel_userptr(topPan);
                top_panel(topPan);
                type = ADD;
            } else if (key == KEY_LEFT && curr != root) {
                curr = curr->parent;
            } else if (key == KEY_RIGHT && !curr->childrens.empty()) {
                curr = curr->childrens[0];
            } else if ((key == KEY_UP || key == KEY_DOWN) && curr != root) {
                vector<Node*> v = curr->parent->childrens;
                auto iter = find_if(v.begin(), v.end(), [curr](Node * n) {
                        return n == curr;
                });
                size_t idx = distance(v.begin(), iter);
                if (idx > 0 && key == KEY_UP) curr = curr->parent->childrens[idx - 1];
                else if (idx < (v.size() - 1) && key == KEY_DOWN) curr = curr->parent->childrens[idx + 1];
            } else if (key == KEY_DC) {
                Node *p = curr->parent;
                if (root != curr) {
                    vector<Node*> v = p->childrens;
                    auto iter = find_if(v.begin(), v.end(), [curr](Node * n) {
                            return n == curr;
                    });
                    int s1 = v.size();
                    v.erase(v.begin(), v.end());
                } else root = 0;
                int s2 = p->childrens.size();
                removeBrunch(curr);
                curr = p;
            } else if (key == KEY_ESC) break;
        } else if (type == ADD) {
            if (key == KEY_ENTER) {
                form_driver(form, REQ_END_LINE);
                Node *n = (Node*) calloc(1, sizeof (Node));
                char *buff = field_buffer(field[0], 0);
                n->name = (char*) calloc(strlen(buff), sizeof (char));
                copy(buff, buff + strlen(buff), n->name);
                n->w = derwin(winMain, NODE_H + PADDING, NODE_W + PADDING, 0, 0);
                if (root) {
                    n->parent = curr;
                    curr->childrens.push_back(n);
                } else {
                    root = n;
                }
                curr = n;
                set_field_buffer(field[0], 0, "");
                topPan = (PANEL*) panel_userptr(topPan);
                top_panel(topPan);
                type = WAIT;
            } else if (key == KEY_ESC) {
                topPan = (PANEL*) panel_userptr(topPan);
                top_panel(topPan);
                type = WAIT;
            } else if (key == 263) form_driver(form, REQ_DEL_PREV); //backspace pressed
            form_driver(form, key);
        }
        wclear(winMain);
        box(winMain, 0, 0);
        drawNodes(root, curr, 0, 1, winMain);
        update_panels();
        doupdate();
    }
    endwin();
    return (EXIT_SUCCESS);
}

void removeBrunch(Node *node) {
    if (!node) return;
    for (Node *ch: node->childrens) {
        removeBrunch(ch);
    }
    delwin(node->w);
    delete [] node->name;
    delete node;
}

int drawNodes(Node *node, Node *focused, int level, int down, WINDOW *w) {
    static WINDOW *winMain;
    if (w) winMain = w;
    if (!node) return 0;
    WINDOW *wnd = node->w;
    mvderwin(wnd, down, level * (NODE_W + PADDING * 2) + 1);
    if (node == focused) wbkgdset(wnd, COLOR_PAIR(3));
    else wbkgdset(wnd, COLOR_PAIR(1));
    wclear(wnd);
    mbstate_t state = mbstate_t(); //locale state
    const char *ptr = node->name;
    const char *end = ptr + strlen(ptr);
    int len, size = 0, y = 1, lenbin = 0;
    wchar_t wc;
    while ((len = mbrtowc(&wc, ptr, end - ptr, &state)) > 0) {
        ptr += len;
        lenbin += len;
        size++;
        if (size == NODE_W) {
            mvwaddnstr(wnd, y, 1, ptr - lenbin, lenbin);
            y++, lenbin = 0, size = 0;
        }
    }
    box(wnd, 0, 0);
    int addAll = 0, add;
    int shift = level * (NODE_W + PADDING * 2) + 1 + NODE_W / 2;
    level++;
    down += (NODE_H + PADDING);
    for (size_t i = 0, n = node->childrens.size(); i < n; i++) {
        add = drawNodes(node->childrens[i], focused, level, down + addAll);
        addAll += add;
        wmove(winMain, down + addAll - add, shift);
        if (i == (n - 1)) {
            mvwaddch(winMain, down + addAll - add, shift, ACS_LLCORNER);// └
        } else {
            wvline(winMain, ACS_VLINE, add);// │
            mvwaddch(winMain, down + addAll - add, shift, ACS_LTEE);// ├
        }
        wmove(winMain, down + addAll - add, shift + 1);
        whline(winMain, ACS_HLINE, NODE_W / 2 + PADDING * 2); // ─
    }
    return (addAll + NODE_H + PADDING);
}

WINDOW *new_wnd(int w, int h, int toX, int toY, int color) {
    WINDOW *wind = newwin(h, w, toY, toX);
    wbkgdset(wind, COLOR_PAIR(color));
    wclear(wind);
    box(wind, 0, 0);
    return wind;
}
