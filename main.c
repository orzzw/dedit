#include "editor.h"

#include <ncurses.h>
#include <stdio.h>

#define CTRL_S 19
#define CTRL_Q 17

void ui_draw_status_bar(struct UI *ui)
{
    mvprintw(LINES - 1, 0, "%s | Ln %zu, Col %zu | %s", 
    ui->filename,
    ui->cursor_row + 1,
    ui->cursor_col + 1,
    ui->status_message);
}

int main(int argc, char *argv[])
{
    struct Editor editor;
    struct UI ui;

    editor_init(&editor);
    ui_init(&ui, argv[1]);

    if(!editor_load(&editor, argv[1]))
    {
        printf("Failed to load\n");
        editor_destroy(&editor);
        return 1;
    }

    initscr();

    raw();
    noecho();
    keypad(stdscr, TRUE);

    while(1)
    {
        clear();

        for(size_t i = 0; i < editor.size; i++)
        {
            mvprintw((int)i, 0, "%s", editor.lines[i]);
        }
        
        ui_draw_status_bar(&ui);

        move((int)ui.cursor_row, (int)ui.cursor_col);

        refresh();

        int key = getch();

        if(key == CTRL_Q)
        {
            if(editor.modified == 0) break;
            else
            {
                editor_strcpy(ui.status_message, "Unsaved changes!");
            }
        }
        else if(key == KEY_UP)
        {
            if(ui.cursor_row > 0) ui.cursor_row--;
        }
        else if(key == KEY_DOWN)
        {
            if(ui.cursor_row + 1 < editor.size) ui.cursor_row++;
        }
        else if(key == KEY_LEFT)
        {
            if(ui.cursor_col > 0) ui.cursor_col--;
        }
        else if(key == KEY_RIGHT)
        {
            ui.cursor_col++;
        }
        else if(key == KEY_BACKSPACE)
        {
            if(editor_delete_char(&editor, ui.cursor_row, ui.cursor_col))
            {
                ui.cursor_col--;
            }
        }
        else if(key == '\n')
        {
            if(editor_insert_newline(&editor, ui.cursor_row, ui.cursor_col))
            {
                ui.cursor_row++;
                ui.cursor_col = 0;
            }
        }
        else if(key == CTRL_S)
        {
            if(editor_save(&editor, argv[1]))
            {
                editor_strcpy(ui.status_message, "Saved!");
            }
            else
            {
                editor_strcpy(ui.status_message, "Save failed!");
            }
        }
        else
        {
            if(editor_insert_char(&editor, ui.cursor_row, ui.cursor_col, (char)key))
            {
                ui.cursor_col++;
            }
        }

        if(ui.cursor_col > editor_strlen(editor.lines[ui.cursor_row]))
        {
            ui.cursor_col = editor_strlen(editor.lines[ui.cursor_row]);
        }
    }

    endwin();

    editor_destroy(&editor);

    return 0;
}

