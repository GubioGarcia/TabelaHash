/*************************************************************************
Implementação de uma Tabela Hash com Sondagem Linear para resolver conflitos.
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
    int colisao = 0;
} typedef elemento;

struct TabelaHash {
    elemento* tabela[TAMANHO];
} typedef TabelaHash;

TabelaHash* criarTabela(); // Aloca memória para nova tabela
int valorHash(char *chave);// Calcula o Hash para a chave
void inserir(TabelaHash *th, TabelaHash* arrayColisao, char* valor); // Insere um valor na tabela
elemento* buscar(TabelaHash* th, TabelaHash* arrayColisao, char* valor); // Busca um valor na tabela hash e retorna o nó que contém o valor ou NULL se não tiver o valor
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

void inserir (TabelaHash *th, TabelaHash* arrayColisao, char* valor) {
    int vh = valorHash(valor); // Calculo de hash
    elemento* novo = (elemento*) malloc(sizeof(elemento));
    std::cout << valor << vh << std::endl; // TESTE
    strcpy(novo->valor, valor);
    if (th->tabela[vh]->valor != NULL) {
        arrayColisao->tabela[vh] = novo;
        while (th->tabela[vh]->valor != NULL) {
            novo->colisao++;
            vh++;
        }
        th->tabela[vh] = novo;

    } else {
        th->tabela[vh] = novo;
    }
}

elemento* buscar(TabelaHash* th, TabelaHash* arrayColisao, char* valor) {
    int vh = valorHash(valor); // Calculo de hash
    if (th->tabela[vh] != NULL) {
        if (strcmp (th->tabela[vh]->valor, valor) == 0) return th->tabela[vh];
        else {
            if (strcmp (arrayColisao->tabela[vh]->valor, valor) == 0) return arrayColisao->tabela[vh];
        }
    }
    return NULL;
}

void remover(TabelaHash* th, char* valor) {
    int vh = valorHash(valor); // Calculo de hash
    elemento* atual = th->tabela[vh];

    while (th->tabela[vh]->valor != valor) {
        vh++;        
    }
    free(atual);
    std::cout << "SUCESSO: Valor removido da tabela" << std::endl; 
}

void imprimir (TabelaHash* th) {
    if (th == NULL) return;
    for (int i = 0; i < TAMANHO; i++) {
        std::cout << "[" << i << "]: ";
        elemento* atual = th->tabela[i];
        if (atual != NULL) {
            std::cout << atual->valor << std::endl;
        } else {
            std::cout << "NULL" << std::endl;
        }
    }
}

int main () {
    setlocale(LC_ALL, "");
    TabelaHash* th = criarTabela();
    TabelaHash* arrayColisao = criarTabela();

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
                inserir(th, arrayColisao, texto);
                break;
            case 2: 
                std::cout << "Digite o valor a ser removido: ";
                std::cin >> texto;
                remover(th, texto);
                break;
            case 3: 
                std::cout << "Digite o valor a ser buscado: ";
                std::cin >> texto;
                std::cout << (buscar(th, arrayColisao, texto) == NULL
                                ? "Valor nao encontrado!" : "Valor encontrado!") << std::endl;
                break;
            case 4: 
                imprimir(th);
                break;
            case 5:
                operacao = 999;
                return 0;
        default:
            std::cout << "ERRO: Opcao Invalida.";
            break;
        }

        std::cout << "PRESSIONE QUALQUER TECLA PARA CONTINUAR!";
        getch();
        system("cls");
    }
}