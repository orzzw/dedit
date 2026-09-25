#ifndef UI_H
#define UI_H

#include "editor.h"

struct UI
{
    const char *filename;
    size_t cursor_row;
    size_t cursor_col;
    size_t scroll_row;
    char status_message[100];
};

void ui_init(struct UI *ui, const char *filename);

void ui_draw_status_bar(struct UI *ui);

void ui_draw_window(struct UI *ui, struct Editor *editor);

#endif