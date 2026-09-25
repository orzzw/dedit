#include "editor.h"

#include <ncurses.h>
#include <stdio.h>

#define CTRL_S 19

int main(int argc, char *argv[])
{
    struct Editor editor;

    editor_init(&editor);

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

    size_t cursor_row = 0;
    size_t cursor_col = 0;

    int saved = 0;

    while(1)
    {
        clear();

        for(size_t i = 0; i < editor.size; i++)
        {
            mvprintw((int)i, 0, "%s", editor.lines[i]);
        }

        move((int)cursor_row, (int)cursor_col);

        if(saved == 1)
        {
            mvprintw(LINES - 1, 0, "Saved!");
        }
        else if(saved == -1)
        {
            mvprintw(LINES - 1, 0, "Save failed!");
        }

        refresh();

        int key = getch();

        if(key == 'q')
        {
            break;
        }
        else if(key == KEY_UP)
        {
            if(cursor_row > 0) cursor_row--;
        }
        else if(key == KEY_DOWN)
        {
            if(cursor_row + 1 < editor.size) cursor_row++;
        }
        else if(key == KEY_LEFT)
        {
            if(cursor_col > 0) cursor_col--;
        }
        else if(key == KEY_RIGHT)
        {
            cursor_col++;
        }
        else if(key == KEY_BACKSPACE)
        {
            if(editor_delete_char(&editor, cursor_row, cursor_col))
            {
                cursor_col--;
            }
        }
        else if(key == '\n')
        {
            if(editor_insert_newline(&editor, cursor_row, cursor_col))
            {
                cursor_row++;
                cursor_col = 0;
            }
        }
        else if(key == CTRL_S)
        {
            if(editor_save(&editor, argv[1]))
            {
                saved = 1;
            }
            else
            {
                saved = -1;
            }
        }
        else
        {
            if(editor_insert_char(&editor, cursor_row, cursor_col, (char)key))
            {
                cursor_col++;
            }
        }

        if(cursor_col > editor_strlen(editor.lines[cursor_row]))
        {
            cursor_col = editor_strlen(editor.lines[cursor_row]);
        }
    }

    endwin();

    editor_destroy(&editor);

    return 0;
}