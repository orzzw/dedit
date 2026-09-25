#include "ui.h"

#include <ncurses.h>

void ui_init(struct UI *ui, const char *filename)
{
    ui->filename = filename;
    ui->cursor_row = 0;
    ui->cursor_col = 0;
    ui->scroll_row = 0;

    editor_strcpy(ui->status_message, "Welcome!");
}

void ui_draw_status_bar(struct UI *ui)
{
    mvprintw(
        LINES - 1,
        0,
        "%s | Ln %zu, Col %zu | %s",
        ui->filename,
        ui->cursor_row + 1,
        ui->cursor_col + 1,
        ui->status_message
    );
}

void ui_draw_window(struct UI *ui, struct Editor *editor)
{
    if(ui->cursor_row < ui->scroll_row)
    {
        ui->scroll_row = ui->cursor_row;
    }
    else if(ui->cursor_row - ui->scroll_row >= (size_t)(LINES - 1))
    {
        ui->scroll_row = ui->cursor_row - (size_t)LINES + 2;
    }

    for(size_t i = ui->scroll_row;
        i < editor->size &&
        i < ui->scroll_row + (size_t)LINES - 1;
        i++)
    {
        mvprintw(
            (int)(i - ui->scroll_row),
            0,
            "%s",
            editor->lines[i]
        );
    }

    ui_draw_status_bar(ui);

    move(
        (int)(ui->cursor_row - ui->scroll_row),
        (int)ui->cursor_col
    );
}