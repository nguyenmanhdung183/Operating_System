#include<stdio.h>

int main(int argc, const char** argv) {
    printf("Menu: \n");
    int i;
    //printf("argc = %d\n", argc);
    for (i = 1; i < argc; i++) {
        printf(" %d. %s\n", i, argv[i]);
    }
    int option;
    do {
        printf("Your Choice: ");
        scanf("%d", &option);


    } while (option < 1 || option >= argc);


    return option;
}