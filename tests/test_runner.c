#include <stdio.h>


int test_editor_init();
int test_insert_char();
int test_delete_char();
int test_delete_forward_char();
int test_insert_newline();
int test_save_load();

int main()
{
    int passed = 0;
    int failed = 0;


    printf("=== dedit test ===\n\n");


    if(test_editor_init())
    {
        printf("[PASS] editor_init\n");
        passed++;
    }
    else
    {
        printf("[FAIL] editor_init\n");
        failed++;
    }

    if(test_insert_char())
    {
        printf("[PASS] editor_insert\n");
        passed++;
    }
    else
    {
        printf("[FAIL] editor_insert\n");
        failed++;
    }

    if(test_delete_char())
    {
        printf("[PASS] editor_delete\n");
        passed++;
    }
    else
    {
        printf("[FAILED] editor_delete\n");
        failed++;
    }

    if(test_delete_forward_char())
    {
        printf("[PASS] editor_delete_forward\n");
        passed++;
    }
    else
    {
        printf("[FAILED] editor_delete_forward\n");
        failed++;
    }

    if(test_insert_newline())
    {
        printf("[PASS] editor_insert\n");
        passed++;
    }
    else
    {
        printf("[FAILED] editor_insert\n");
        failed++;
    }

    if(test_save_load())
    {
        printf("[PASS] editor_save_load\n");
        passed++;
    }
    else
    {
        printf("[FAILED] editor_save_load\n");
        failed++;
    }


    printf("\n%d passed, %d failed\n", passed, failed);


    return 0;
}