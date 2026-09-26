#include "../editor.h"


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