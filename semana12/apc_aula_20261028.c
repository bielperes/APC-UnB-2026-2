#include <stdio.h>
#define MAX 100000

void remover_nl(char *nome){
    int i = 0;
    for(i;nome[i] != '\0';i++){
        if(nome[i] == '\n'){
            nome[i] = '\0';
        }
    }
}

void print_ascii_hx(char *str){
    int i = 0;
    for(i;str[i] != '\0';i++){
        printf("0x%x,", (unsigned char)str[i]);
    }
}
void print_ascii_dec(char *str){
    int i = 0;
    for(i;str[i] != '\0';i++){
        printf("%d,", (unsigned char)str[i]);

    }
}

void ler_strings(){

/* Faça uma função que lê uma sequência de strings no formato "%d %f %s", onde:
    - O decimal corresponde a idade;
    - O float corresponde a altura;
    - A string corresponde ao nome de uma pessoa, a sequência de strings é terminada quando se inseri uma string vazia
    - Após o término da sequência imprima:
        - A média das idades;
        - Altura da pessoa mais velha;
        - Nome da pessoa mais idosa
*/

}

int main(){
   char str[] = "10 1.71 Gustavo Franco";
    int indice;
    double altura;
    char nome[MAX];
    char sobrenome[MAX];
    sscanf(str,"%d %lf %[^\n]",&indice, &altura, nome);
    printf("indice: %d\naltura: %lf\nnome: %s\n", indice,altura,nome);

    return 0;
}