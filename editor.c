#include "editor.h"

#include <stdio.h>
#include <stdlib.h>

void editor_init(struct Editor *editor)
{
    editor->lines = NULL;
    editor->size = 0;
    editor->capacity = 0;
}

size_t editor_strlen(const char *src)
{
    size_t len = 0;

    while(*src)
    {
        len++;
        src++;
    }

    return len;
}

char *editor_strdup(const char *src)
{
    char *dest;

    dest = malloc(editor_strlen(src) + 1);

    if(dest == NULL) return NULL;

    char *temp = dest;

    while(*src)
    {
        *temp = *src;
        temp++;
        src++;
    }
    *temp = '\0';

    return dest;
}

void editor_print_lines(const struct Editor *editor)
{
    for(size_t i = 0; i < editor->size; i++)
    {
        printf("%s\n", editor->lines[i]);
    }
}

int editor_expand(struct Editor *editor)
{
    size_t new_capacity;

    if(editor->capacity == 0) new_capacity = 3;
    else new_capacity = editor->capacity * 2;

    char **temp;

    temp = realloc(editor->lines, sizeof(char *) * new_capacity);

    if(temp == NULL) return 0;

    editor->lines = temp;
    editor->capacity = new_capacity;

    return 1;
}

int editor_delete_line(struct Editor *editor, size_t index)
{
    if(index >= editor->size) return 0;

    free(editor->lines[index]);

    for(size_t i = index; i < editor->size - 1; i++)
    {
        editor->lines[i] = editor->lines[i + 1];
    }

    editor->size--;
    editor->lines[editor->size] = NULL;

    return 1;
}

int editor_insert_line(struct Editor *editor, size_t index, const char *text)
{
    if(index > editor->size) return 0;

    if(editor->size >= editor->capacity)
    {
        if(!editor_expand(editor)) return 0;
    }
    
    for(size_t i = editor->size; i > index; i--)
    {
        editor->lines[i] = editor->lines[i - 1];
    }
    
    char *line;
    line = editor_strdup(text);

    if(line == NULL) return 0;

    editor->lines[index] = line;

    editor->size++;

    return 1;
}

int editor_add_line(struct Editor *editor, const char *text)
{
    return editor_insert_line(editor, editor->size, text);
}

int editor_insert_char(struct Editor *editor, size_t row, size_t col, char ch)
{
    char *line;
    size_t length;

    if(row >= editor->size) return 0;

    line = editor->lines[row];
    length = editor_strlen(line);

    if(col > length) return 0;

    char *temp;

    temp = realloc(line, sizeof(char) * (length + 2));

    if(temp == NULL) return 0;

    line = temp;
    editor->lines[row] = line;

    for(size_t i = length + 1; i > col; i--)
    {
        line[i] = line[i - 1];
    }

    line[col] = ch;

    return 1;
}

void editor_destroy(struct Editor *editor)
{
    for(size_t i = 0; i < editor->size; i++)
    {
        free(editor->lines[i]);
    }
    free(editor->lines);

    editor->lines = NULL;
    editor->size = 0;
    editor->capacity = 0;
}

int editor_save(const struct Editor *editor, const char *filename)
{
    FILE *fp;

    fp = fopen(filename, "w");

    if(fp == NULL) return 0;

    for(size_t i = 0; i < editor->size; i++)
    {
        fprintf(fp, "%s\n", editor->lines[i]);
    }

    fclose(fp);

    return 1;
}

int editor_load(struct Editor *editor, const char *filename)
{
    FILE *fp;
    char buffer[100];
    char *line = NULL;
    size_t length = 0;
    size_t capacity = 0;
    
    fp = fopen(filename, "r");

    if(fp == NULL) return 0;

    while(fgets(buffer, sizeof(buffer), fp))
    {
        size_t chunk_length;

        chunk_length = editor_strlen(buffer);
        if(capacity < length + chunk_length + 1)
        {
            if(capacity == 0) capacity = 100;
            while(capacity < length + chunk_length + 1)
            {
                capacity *= 2;
            }
            char *temp = realloc(line, sizeof(char) * capacity);

            if(temp == NULL)
            {
                free(line);
                fclose(fp);
                return 0;
            }

            line = temp;
        }
        for(size_t i = 0; i < chunk_length; i++)
        {
            line[length + i] = buffer[i];
        }
        length += chunk_length;
        line[length] = '\0';

        if(length > 0 && line[length - 1] == '\n')
        {
            line[length - 1] = '\0';
            length--;

            if(!editor_add_line(editor, line))
            {
                free(line);
                fclose(fp);
                return 0;
            }
            free(line);
            line = NULL;
            length = 0;
            capacity = 0;
        }
    }
    if(line != NULL)
    {
        if(!editor_add_line(editor, line))
        {
            free(line);
            fclose(fp);
            return 0;
        }

        free(line);
    }

    fclose(fp);

    return 1;
}