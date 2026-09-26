#include <stdio.h>


int test_editor_init();


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


    printf("\n%d passed, %d failed\n", passed, failed);


    return 0;
}