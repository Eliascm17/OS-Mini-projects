#include "segments.h"
#include <malloc.h>
#include <string.h>

char* text1() {
    return "text 1";
}

char* text2() {
    return "text 2";
}

char data1[] = "data 1";
char data2[] = "data 2";

char bss1[6];
char bss2[6];

void stack() {
    char stack1[8] = "stack 1";
    char stack2[8] = "stack 2";

    stack_ptr_1 = stack1;
    stack_ptr_2 = stack2;
}


void init_pointers() {

    text_ptr_1 = &text1;
    text_ptr_2 = &text2;

    data_ptr_1 = data1;
    data_ptr_2 = data2;

    bss1[0] = 'b';
    bss1[1] = 's';
    bss1[2] = 's';
    bss1[3] = ' ';
    bss1[4] = '1';
    bss_ptr_1 = bss1;

    bss2[0] = 'b';
    bss2[1] = 's';
    bss2[2] = 's';
    bss2[3] = ' ';
    bss2[4] = '2';
    bss_ptr_2 = bss2;

    heap_ptr_1 = malloc(sizeof(char *));
    strcpy(heap_ptr_1, "heap 1");
    heap_ptr_2 = malloc(sizeof(char *));
    strcpy(heap_ptr_2, "heap 2");

    stack();
}

void free_pointers() {
    
    free(heap_ptr_1);
    free(heap_ptr_2);

}


