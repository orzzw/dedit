#include "editor.h"

#include <stdio.h>

int main(void)
{
    struct Editor editor;

    editor_init(&editor);

    if(!editor_load(&editor, "test.txt"))
    {
        printf("load failed\n");
        editor_destroy(&editor);
        return 1;
    }

    editor_print_lines(&editor);

    editor_destroy(&editor);

    return 0;
}