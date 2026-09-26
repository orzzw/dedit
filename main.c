#include "editor.h"
#include "ui.h"

#include <ncurses.h>
#include <stdio.h>

#define CTRL_S 19
#define CTRL_Q 17

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

        ui_draw_window(&ui, &editor);
    
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
        else if(key == KEY_DC)
        {
            editor_delete_forward_char(&editor, ui.cursor_row, ui.cursor_col);
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

