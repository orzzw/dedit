#include "../editor.h"

#include <string.h>


int test_editor_init()
{
    struct Editor editor;

    editor_init(&editor);

    if(editor.lines != NULL)
        return 0;

    if(editor.size != 0)
        return 0;

    if(editor.capacity != 0)
        return 0;

    if(editor.modified != 0)
        return 0;

    return 1;
}

int test_insert_char()
{
    struct Editor editor;

    editor_init(&editor);

    if(!editor_add_line(&editor, "abc")) return 0;

    if(!editor_insert_char(&editor, 0, 1, 'X'))
    {
        editor_destroy(&editor);
        return 0;
    }

    if(strcmp(editor.lines[0], "aXbc") != 0)
    {
        editor_destroy(&editor);
        return 0;
    }

    editor_destroy(&editor);

    return 1;
}

int test_delete_char()
{
    struct Editor editor;

    editor_init(&editor);

    if(!editor_add_line(&editor, "abc")) return 0;

    if(!editor_delete_char(&editor, 0, 2))
    {
        editor_destroy(&editor);
        return 0;
    }

    if(strcmp(editor.lines[0], "ac") != 0)
    {
        editor_destroy(&editor);
        return 0;
    }

    editor_destroy(&editor);

    return 1;
}

int test_delete_forward_char()
{
    struct Editor editor;

    editor_init(&editor);

    if(!editor_add_line(&editor, "abc")) return 0;

    if(!editor_delete_forward_char(&editor, 0, 1))
    {
        editor_destroy(&editor);
        return 0;
    }

    if(strcmp(editor.lines[0], "ac"))
    {
        editor_destroy(&editor);
        return 0;
    }

    editor_destroy(&editor);

    return 1;
}

int test_insert_newline()
{
    struct Editor editor;

    editor_init(&editor);
    
    if(!editor_add_line(&editor, "Hello World")) return 0;

    if(!editor_insert_newline(&editor, 0, 5))
    {
        editor_destroy(&editor);
        return 0;
    }

    if(strcmp(editor.lines[0], "Hello") != 0 || strcmp(editor.lines[1], " World") != 0)
    {
        editor_destroy(&editor);
        return 0;
    }

    editor_destroy(&editor);

    return 1;
}

int test_save_load()
{
    struct Editor editor;

    editor_init(&editor);

    editor_add_line(&editor,"hello");
    editor_add_line(&editor,"world");


    if(!editor_save(&editor,"test.txt"))
    {
        editor_destroy(&editor);
        return 0;
    }


    editor_destroy(&editor);


    struct Editor loaded;

    editor_init(&loaded);


    if(!editor_load(&loaded,"test.txt"))
    {
        editor_destroy(&loaded);
        return 0;
    }


    if(loaded.size != 2)
    {
        editor_destroy(&loaded);
        return 0;
    }


    if(strcmp(loaded.lines[0],"hello") != 0)
    {
        editor_destroy(&loaded);
        return 0;
    }


    if(strcmp(loaded.lines[1],"world") != 0)
    {
        editor_destroy(&loaded);
        return 0;
    }


    editor_destroy(&loaded);

    return 1;
}