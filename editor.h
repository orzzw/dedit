#ifndef EDITOR_H
#define EDITOR_H

#include <stddef.h>

struct Editor
{
    char **lines;
    size_t size;
    size_t capacity;
    int modified;
};

void editor_init(struct Editor *editor);

size_t editor_strlen(const char *src);

void editor_strcpy(char *dest, char *src);

char *editor_strdup(const char *src);

void editor_print_lines(const struct Editor *editor);

int editor_expand(struct Editor *editor);

int editor_delete_line(struct Editor *editor, size_t index);

int editor_delete_forward_char(struct Editor *editor, size_t row, size_t col);

int editor_insert_line(struct Editor *editor, size_t index, const char *text);

int editor_add_line(struct Editor *editor, const char *text);

void editor_destroy(struct Editor *editor);

int editor_save(struct Editor *editor, const char *filename);

int editor_load(struct Editor *editor, const char *filename);

int editor_insert_char(struct Editor *editor, size_t row, size_t col, char ch);

int editor_delete_char(struct Editor *editor, size_t row, size_t col);

int editor_insert_newline(struct Editor *editor, size_t row, size_t col);

#endif