/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
*/

//================================================================
//Ponto de partida do projeto.
//================================================================

// ============================================================================
// PROJETO: CÓDIGO DA ILHA - EDIÇÃO FREE FIRE NIVEL MESTRE
// Autor: Fabrício Vieira de Souza
// Data: 03/10/2025
// Matrícula: 202501549322
// Objetivo: Sistema de cadastro, ordenação e busca binária
//           aplicado ao inventário de fuga (componentes da torre).
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; 
} Componente;

// ====================== PROTÓTIPOS ============================
void cadastrarComponentes(Componente lista[], int *n);
void mostrarComponentes(Componente lista[], int n);
void organizarMochila(Componente lista[], int n, int *ordenadoPorNome);

void bubbleSortNome(Componente lista[], int n, int *comparacoes);
void insertionSortTipo(Componente lista[], int n, int *comparacoes);
void selectionSortPrioridade(Componente lista[], int n, int *comparacoes);

int buscaBinariaPorNome(Componente lista[], int n, char chave[], int *comparacoes);

// ====================== MAIN ================================
int main() {
    Componente mochila[MAX_COMPONENTES];
    int n = 0;                        // número atual de componentes
    int opcao;
    int ordenadoPorNome = 0;          // flag: 1 se ordenado por nome
    char chave[30];
    int comparacoes;

    do {
        // Exibição do menu principal
        printf("\n========== PLANO DE FUGA - NIVEL MESTRE ==========\n");
        printf("** Itens na mochila: %d / %d\n", n, MAX_COMPONENTES);
        printf("** Status da ordenacao por nome: %s\n", ordenadoPorNome ? "ordenado por nome" : "nao ordenado");
        printf("1. Cadastrar componentes\n");
        printf("2. Listar inventário\n");
        printf("3. Busca binária por componente-chave (nome)\n");
        printf("4. Organizar mochila (ordenar componentes)\n");
        printf("0. Ativar torre de fuga (sair)\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        comparacoes = 0;

        switch(opcao) {
            case 1:
                cadastrarComponentes(mochila, &n);
                ordenadoPorNome = 0; // nova inserção quebra ordenação
                break;

            case 2:
                mostrarComponentes(mochila, n);
                break;

            case 3:
                if (!ordenadoPorNome) {
                    printf("\nALERTA: A BUSCA BINARIA REQUER QUE A MOCHILA ESTEJA ORDENADA POR NOME.\n");
                    printf("USE A OPCAO 4 PARA ORGANIZAR O INVENTARIO PRIMEIRO.\n");
                    break;
                }
                if (n == 0) {
                    printf("Inventário vazio. Cadastre componentes primeiro.\n");
                    break;
                }
                // Entrada do nome do componente a buscar
                printf("Digite o nome do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';

                // Busca binária
                {
                    int pos = buscaBinariaPorNome(mochila, n, chave, &comparacoes);
                    if (pos != -1) {
                        // Exibição do item encontrado
                        printf("\n--- ITEM ENCONTRADO ---\n");
                        printf("%-15s | %-15s | %-12s | %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
                        printf("---------------------------------------------------------------\n");
                        printf("%-15s | %-15s | %-12d | %-10d\n",
                               mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade, mochila[pos].prioridade);
                        printf("---------------------------------------------------------------\n");
                    } else {
                        printf("Componente '%s' não encontrado.\n", chave);
                    }
                    printf("Comparações realizadas: %d\n", comparacoes);
                }
                break;

            case 4:
                organizarMochila(mochila, n, &ordenadoPorNome);
                break;

            case 0:
                printf("\nAtivando torre de fuga... Boa sorte!\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

// ====================== FUNÇÕES AUXILIARES ====================

// Cadastra um novo componente
void cadastrarComponentes(Componente lista[], int *n) {
    if (*n >= MAX_COMPONENTES) {
        printf("Inventário cheio!\n");
        return;
    }

    printf("\n-- Coletando novo componente --\n");
    printf("Nome: ");
    fgets(lista[*n].nome, sizeof(lista[*n].nome), stdin);
    lista[*n].nome[strcspn(lista[*n].nome, "\n")] = '\0';

    printf("Tipo (estrutural, eletronico, energia, etc): ");
    fgets(lista[*n].tipo, sizeof(lista[*n].tipo), stdin);
    lista[*n].tipo[strcspn(lista[*n].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &lista[*n].quantidade);
    getchar();

    printf("Prioridade (1-10): ");
    scanf("%d", &lista[*n].prioridade);
    getchar();

    (*n)++;
    printf("Componente adicionado com sucesso!\n");
}

// Mostra todos os componentes em tabela
void mostrarComponentes(Componente lista[], int n) {
    if (n == 0) {
        printf("Inventário vazio!\n");
        return;
    }
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", n, MAX_COMPONENTES);
    printf("%-15s | %-15s | %-12s | %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("---------------------------------------------------------------\n");
    for (int i=0; i<n; i++) {
        printf("%-15s | %-15s | %-12d | %-10d\n",
               lista[i].nome, lista[i].tipo, lista[i].quantidade, lista[i].prioridade);
    }
    printf("---------------------------------------------------------------\n");
}

// Menu de ordenação com estratégias diferentes
void organizarMochila(Componente lista[], int n, int *ordenadoPorNome) {
    if (n == 0) {
        printf("Inventário vazio! Cadastre antes de organizar.\n");
        return;
    }

    int escolha, comparacoes = 0;
    clock_t inicio, fim;
    double tempoExec;

    printf("\n--- Estratégia de Organização ---\n");
    printf("1. Ordenar por nome (Bubble Sort)\n");
    printf("2. Ordenar por tipo (Insertion Sort)\n");
    printf("3. Ordenar por prioridade (Selection Sort)\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    getchar();

    inicio = clock();
    switch(escolha) {
        case 1:
            bubbleSortNome(lista, n, &comparacoes);
            *ordenadoPorNome = 1;  // flag para busca binária
            printf("\nInventário ordenado por NOME.\n");
            break;
        case 2:
            insertionSortTipo(lista, n, &comparacoes);
            *ordenadoPorNome = 0;
            printf("\nInventário ordenado por TIPO.\n");
            break;
        case 3:
            selectionSortPrioridade(lista, n, &comparacoes);
            *ordenadoPorNome = 0;
            printf("\nInventário ordenado por PRIORIDADE (maior para menor).\n");
            break;
        default:
            printf("Opção inválida.\n");
            return;
    }
    fim = clock();
    tempoExec = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Comparações: %d | Tempo: %.6f seg\n", comparacoes, tempoExec);

    mostrarComponentes(lista, n);
}

// ====================== ORDENAÇÕES =========================

// Bubble Sort: ordena por nome
void bubbleSortNome(Componente lista[], int n, int *comparacoes) {
    Componente temp;
    int i,j,trocou;
    for(i=0;i<n-1;i++) {
        trocou = 0;
        for(j=0;j<n-i-1;j++) {
            (*comparacoes)++;
            if(strcmp(lista[j].nome, lista[j+1].nome)>0) {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
                trocou=1;
            }
        }
        if(!trocou) break;
    }
}

// Insertion Sort: ordena por tipo
void insertionSortTipo(Componente lista[], int n, int *comparacoes) {
    int i,j;
    Componente chave;
    for(i=1;i<n;i++) {
        chave = lista[i];
        j=i-1;
        while(j>=0 && strcmp(lista[j].tipo,chave.tipo)>0) {
            (*comparacoes)++;
            lista[j+1]=lista[j];
            j--;
        }
        if(j>=0)(*comparacoes)++;
        lista[j+1]=chave;
    }
}

// Selection Sort: ordena por prioridade (maior para menor)
void selectionSortPrioridade(Componente lista[], int n, int *comparacoes) {
    int i,j,max;
    Componente temp;
    for(i=0;i<n-1;i++) {
        max=i;
        for(j=i+1;j<n;j++) {
            (*comparacoes)++;
            if(lista[j].prioridade>lista[max].prioridade)
                max=j;
        }
        if(max!=i) {
            temp=lista[i];
            lista[i]=lista[max];
            lista[max]=temp;
        }
    }
}

// ====================== BUSCA BINÁRIA ======================

// Busca binária por nome (requer lista ordenada por nome)
int buscaBinariaPorNome(Componente lista[], int n, char chave[], int *comparacoes) {
    int ini=0, fim=n-1, meio;
    while(ini<=fim) {
        meio=(ini+fim)/2;
        (*comparacoes)++;
        int cmp=strcmp(lista[meio].nome,chave);
        if(cmp==0) return meio;
        else if(cmp<0) ini=meio+1;
        else fim=meio-1;
    }
    return -1;
}
