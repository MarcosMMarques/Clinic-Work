#include<stdio.h>

int main(){
    char *teste[2];
    char leitura[20];
    scanf("%[^\n]%*c", leitura);
    teste[1] = malloc(strlen(leitura)+1);
    strcpy(teste[1], leitura);
    char outro[20];
    scanf("%[^\n]%*c", outro);
    teste[2] = malloc(strlen(outro)+1);
    strcpy(teste[2], outro);

    printf("\n%s",teste[1]);
    printf("\n%s",teste[2]);
}