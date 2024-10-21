#include<stdio.h>

int main(int argc , const char ** argv ){
    printf("\nCó xoá không ?: %s \n", argv[argc-1]);
    int i;
    for( i=1;i <  argc-1; i++){
        printf(" %d. %s\n",i,argv[i]);
    }
    int option;
    do{
        printf("Your Choice: ");
        scanf("%d", &option);   
    }while(option < 1 || option >= argc-1);
    return option;
}
