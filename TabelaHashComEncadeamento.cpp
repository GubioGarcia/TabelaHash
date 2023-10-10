/*************************************************************************
Implementação de uma Tabela Hash com encadeamento (lista) para resolver conflitos.
Criação de funções para inserir, buscar e remover elementos.
*************************************************************************/
#include <iostream>
#include <cstring>
#include <clocale>
#include <cstdlib>
#include <conio.h>
#include <cmath>

#define TAMANHO 10

struct elemento {
    char valor[50];
    elemento* prox;
} typedef elemento;

struct TabelaHash {
    elemento* tabela[TAMANHO];
} typedef TabelaHash;

TabelaHash* criarTabela(); // Aloca memória para nova tabela
int valorHash(char *chave);// Calcula o Hash para a chave
void inserir(TabelaHash *th, char* valor); // Insere um valor na tabela
elemento* buscar(TabelaHash* th, char* valor); // Busca um valor na tabela hash e retorna o nó que contém o valor ou NULL se não tiver o valor
void remover(TabelaHash* th, char* valor);

TabelaHash* criarTabela () {
    TabelaHash* th = (TabelaHash*) malloc(sizeof(TabelaHash));
    for (int i = 0; i < TAMANHO; i++) {
        th->tabela[i] = NULL;
    }
    return th;
}

int valorHash (char* chave) {
    int vh = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        vh = (vh*3+chave[i])%10; // Calculo de hash por divisão
    }
    return vh;
}

void inserir (TabelaHash *th, char* valor) {
    int vh = valorHash(valor); // Calculo de hash
    elemento* novo = (elemento*) malloc(sizeof(elemento));
    strcpy(novo->valor, valor);
    novo->prox = th->tabela[vh];
    th->tabela[vh] = novo;
}

elemento* buscar(TabelaHash* th, char* valor) {
    int vh = valorHash(valor); // Calculo de hash
    elemento* atual =  th->tabela[vh];
    while (atual != NULL) {
        if (strcmp (atual->valor, valor) == 0) return atual;
        atual = atual->prox;
    }
    return NULL;
}

void remover(TabelaHash* th, char* valor) {
    int vh = valorHash(valor); // Calculo de hash
    elemento* atual = th->tabela[vh];
    elemento* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->valor, valor) == 0) {
            if (anterior == NULL) th->tabela[vh] = atual->prox;
            else anterior->prox = atual->prox;
            free(atual);
            std::cout << "SUCESSO: Valor removido da tabela" << std::endl; 
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    std::cout << "ERRO: Valor não foi encontrado" << std::endl;
}

void imprimir (TabelaHash* th) {
    if (th == NULL) return;
    for (int i = 0; i < TAMANHO; i++) {
        std::cout << "[" << i << "]: ";
        elemento* atual = th->tabela[i];
        while (atual != NULL) {
            std::cout << atual->valor << " -> ";
            atual = atual->prox;
        }
        std::cout << "NULL" << std::endl;
    }
}

int main () {
    setlocale(LC_ALL, "");
    TabelaHash* th = criarTabela();

    int operacao = 0;
    char texto[50];

    while (operacao != 999) {
        std::cout << "MENU\n";
        std::cout << "1 - Inserir valor" << std::endl;
        std::cout << "2 - Remover valor" << std::endl;
        std::cout << "3 - Buscar valor" << std::endl;
        std::cout << "4 - Visualizar tabela" << std::endl;
        std::cout << "5 - Sair" << std::endl;
        std::cout << ">> ";
        std::cin >> operacao;
        switch (operacao) {
            case 1: 
                std::cout << "Digite o valor a ser inserido: ";
                std::cin >> texto;
                inserir(th, texto);
                break;
            case 2: 
                std::cout << "Digite o valor a ser removido: ";
                std::cin >> texto;
                remover(th, texto);
                break;
            case 3: 
                std::cout << "Digite o valor a ser buscado: ";
                std::cin >> texto;
                std::cout << (buscar(th, texto) == NULL
                                ? "Valor nao encontrado!" : "Valor encontrado!") << std::endl;
                break;
            case 4: 
                imprimir(th);
                break;
            case 5: 
                operacao = 999;
                break;
        default:
            std::cout << "ERRO: Opcao Invalida." << std::endl;
            break;
        }

        std::cout << "PRESSIONE QUALQUER TECLA PARA CONTINUAR!";
        getch();
        system("cls");
    }
}