#include <stdio.h>
#include <stdlib.h>

int main(int x); // ok
void programa(); // ok
void inicializar(); // ok
void finalizar(); // ok
int menu(); // ok
void cadastrarTurma(); 
void registrarPresenca();
void apurarFrequencia();
int contarQtdAulas();

int main(int m) {
    // trata os argumentos na linha de comando
    // chama o programa principal
    programa();
    return 0;
}

void programa() {
    inicializar();
    int opcao = 0;
    do {
        opcao = menu();
        switch (opcao) {
            case 1: cadastrarTurma();
                    break;
            case 2: registrarPresenca();
                    break;
            case 3: apurarFrequencia();
                    break;
            default: printf("Opcao invalida\n");
        }
    } while (opcao != 0);
    finalizar();
}
typedef struct Estudante {
    int matricula;
    char nome[80];
    char frequencias[100];
} Estudante;

typedef struct Aula {
    char dia;
    char mes;
    short ano;
    char descricao[100];
} Aula;

Estudante* estudantes[100];
Aula* aulas[100];

void inicializar() {
    // libera todas as áreas de memória com dados de estudantes
    // de execuções anteriores
    for (int i = 0; i < 100; i++) {
        if (estudantes[i] != 0) {
            free(estudantes[i]);
        }
    }
    // libera todas as áreas de memória com dados de frequencia
    // de execuções anteriores
    for (int i = 0; i < 100; i++) {
        if (aulas[i] != 0) {
            free(aulas[i]);
        }
    }
}

void finalizar() {
    printf("Ateh logo mais, espero que tenha gostado!!");
}

int leInteiro() {
    char buffer[3];
    int opcao = 0;
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            opcao = atoi(buffer);
            return opcao;
        } 
    }
}

char buffer[100];
char * leNome() {
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            return buffer;
        } 
    }
}

int menu() {
    printf("\n=================================\n");
    printf("Programa de gestao de frequencias\n");
    printf("Autor: Jorge Fernandes\n");
    printf("Escolha a opcao\n");
    printf("1 - Cadastrar Turma\n");
    printf("2 - Registrar Presenca\n");
    printf("3 - Apurar Frequencia\n");
    printf("\n");
    return leInteiro();
}

void cadastrarTurma() {
    printf("Bem vinda a funcao Cadastrar turma\n");
    printf("Informe matricula e nome do estudante\n");
    printf("Informe zero na matricula para terminar o cadastro\n");
    while (1) {
        int matricula = leInteiro();
        if (matricula == 0) break;
        char* nome = leNome();
        Estudante* novoEstudante = 
           (Estudante*) malloc(sizeof(Estudante));
        novoEstudante->matricula = matricula;
        strcpy(&novoEstudante->nome, nome);
        for (int i = 0; i < sizeof(estudantes); i++) {
            if (estudantes[i]==0) {
                estudantes[i] = novoEstudante;
            }
        }
    }
}

void registrarPresenca() {
    printf("Stub: Registrar frequência\n");
}
void apurarFrequencia() {
    printf("Stub: Apurar frequência\n");
}

int contarQtdAulas() {
    return 0;
}
