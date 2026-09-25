#include "editor.h"

#include <ncurses.h>
#include <stdio.h>

int main(void)
{
    struct Editor editor;

    editor_init(&editor);

    if(!editor_load(&editor, "test.txt"))
    {
        printf("Failed to load\n");
        editor_destroy(&editor);
        return 1;
    }

    initscr();

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    size_t cursor_row = 0;
    size_t cursor_col = 0;

    while(1)
    {
        clear();

        for(size_t i = 0; i < editor.size; i++)
        {
            mvprintw((int)i, 0, "%s", editor.lines[i]);
        }

        move((int)cursor_row, (int)cursor_col);

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