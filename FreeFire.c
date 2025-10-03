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
// PROJETO: CÓDIGO DA ILHA - EDIÇÃO FREE FIRE AVENTUREIRO
// Autor: Fabrício Vieira de Souza
// Data: 02/10/2025
// Matrícula: 202501549322
// Objetivo: comparar vetor e lista encadeada para mochila de loot
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// ---------- STRUCTS ----------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ---------- CONTADORES ----------
int compVetor = 0;
int compLista = 0;
clock_t tempoVetor = 0;
clock_t tempoLista = 0;

// ---------- FUNÇÕES VETOR ----------
void inserirItemVetor(Item mochila[], int *qtdItens){
    if(*qtdItens >= MAX_ITENS){ printf("Mochila cheia (vetor)!\n"); return; }
    clock_t inicio = clock();

    printf("Nome do item: "); fgets(mochila[*qtdItens].nome, 30, stdin);
    mochila[*qtdItens].nome[strcspn(mochila[*qtdItens].nome,"\n")] = 0;
    printf("Tipo do item: "); fgets(mochila[*qtdItens].tipo, 20, stdin);
    mochila[*qtdItens].tipo[strcspn(mochila[*qtdItens].tipo,"\n")] = 0;
    printf("Quantidade: "); scanf("%d", &mochila[*qtdItens].quantidade); getchar();

    (*qtdItens)++;
    tempoVetor += clock() - inicio;
    printf("Item adicionado (vetor)!\n");
}

void removerItemVetor(Item mochila[], int *qtdItens){
    if(*qtdItens == 0){ printf("Mochila vazia (vetor)!\n"); return; }
    char nome[30]; printf("Nome do item para remover: "); fgets(nome, 30, stdin); nome[strcspn(nome,"\n")] = 0;
    clock_t inicio = clock();

    int i, encontrado=0;
    for(i=0; i<*qtdItens; i++){ compVetor++; if(strcmp(mochila[i].nome, nome)==0){ encontrado=1; break; } }
    if(!encontrado){ printf("Item não encontrado (vetor)!\n"); return; }
    for(int j=i; j<*qtdItens-1; j++) mochila[j]=mochila[j+1];
    (*qtdItens)--;
    tempoVetor += clock() - inicio;
    printf("Item removido (vetor)!\n");
}

void listarItensVetor(const Item mochila[], int qtdItens){
    if(qtdItens == 0){ printf("Mochila vazia (vetor)!\n"); return; }
    printf("Itens (vetor):\n");
    for(int i=0;i<qtdItens;i++)
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
}

void buscarItemVetor(const Item mochila[], int qtdItens){
    if(qtdItens == 0){ printf("Mochila vazia (vetor)!\n"); return; }
    char nome[30]; printf("Nome do item para buscar: "); fgets(nome, 30, stdin); nome[strcspn(nome,"\n")]=0;
    clock_t inicio = clock();
    for(int i=0;i<qtdItens;i++){ compVetor++; if(strcmp(mochila[i].nome,nome)==0){
        printf("Item encontrado (vetor): Nome: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        tempoVetor += clock() - inicio; return;
    } }
    printf("Item não encontrado (vetor)!\n");
    tempoVetor += clock() - inicio;
}

// ---------- FUNÇÕES LISTA ----------
No* inserirItemLista(No *inicio){
    clock_t inicioTempo = clock();
    No *novo = (No*)malloc(sizeof(No));
    if(!novo){ printf("Erro de alocação!\n"); return inicio; }

    printf("Nome do item: "); fgets(novo->dados.nome,30,stdin); novo->dados.nome[strcspn(novo->dados.nome,"\n")]=0;
    printf("Tipo do item: "); fgets(novo->dados.tipo,20,stdin); novo->dados.tipo[strcspn(novo->dados.tipo,"\n")]=0;
    printf("Quantidade: "); scanf("%d",&novo->dados.quantidade); getchar();

    novo->proximo = inicio;
    inicio = novo;
    tempoLista += clock()-inicioTempo;
    printf("Item adicionado (lista)!\n");
    return inicio;
}

No* removerItemLista(No *inicio){
    if(!inicio){ printf("Mochila vazia (lista)!\n"); return inicio; }
    char nome[30]; printf("Nome do item para remover: "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    clock_t inicioTempo = clock();

    No *atual = inicio, *ant = NULL; int encontrado=0;
    while(atual){ compLista++; if(strcmp(atual->dados.nome,nome)==0){ encontrado=1; break; } ant=atual; atual=atual->proximo; }
    if(!encontrado){ printf("Item não encontrado (lista)!\n"); return inicio; }

    if(ant) ant->proximo = atual->proximo;
    else inicio = atual->proximo;

    free(atual);
    tempoLista += clock()-inicioTempo;
    printf("Item removido (lista)!\n");
    return inicio;
}

void listarItensLista(const No *inicio){
    if(!inicio){ printf("Mochila vazia (lista)!\n"); return; }
    printf("Itens (lista):\n");
    int i=1;
    while(inicio){ printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i, inicio->dados.nome, inicio->dados.tipo, inicio->dados.quantidade); i++; inicio=inicio->proximo; }
}

void buscarItemLista(const No *inicio){
    if(!inicio){ printf("Mochila vazia (lista)!\n"); return; }
    char nome[30]; printf("Nome do item para buscar: "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    clock_t inicioTempo = clock();
    while(inicio){ compLista++; if(strcmp(inicio->dados.nome,nome)==0){
        printf("Item encontrado (lista): Nome: %s | Tipo: %s | Quantidade: %d\n", inicio->dados.nome, inicio->dados.tipo, inicio->dados.quantidade);
        tempoLista += clock()-inicioTempo; return;
    } inicio = inicio->proximo; }
    printf("Item não encontrado (lista)!\n");
    tempoLista += clock()-inicioTempo;
}

// ---------- LIBERAR MEMÓRIA ----------
No* liberarLista(No *inicio){
    No *atual = inicio;
    while(atual){ No *tmp = atual; atual = atual->proximo; free(tmp); }
    return NULL;
}

// ---------- MAIN ----------
int main(){
    Item mochilaVetor[MAX_ITENS]; int qtdItensVetor=0;
    No *mochilaLista=NULL;
    int opcao;

    do{
        printf("\n-- MOCHILA DE SOBREVIVÊNCIA -- Itens da mochila: %d/%d\n", qtdItensVetor, MAX_ITENS);
        printf("1 - Adicionar item (loot)\n2 - Remover item\n3 - Listar itens na mochila\n4 - Buscar item por nome\n0 - SAIR\nEscolha uma opcao: ");
        scanf("%d",&opcao); getchar();

        switch(opcao){
            case 1: inserirItemVetor(mochilaVetor,&qtdItensVetor); mochilaLista = inserirItemLista(mochilaLista); break;
            case 2: removerItemVetor(mochilaVetor,&qtdItensVetor); mochilaLista = removerItemLista(mochilaLista); break;
            case 3: listarItensVetor(mochilaVetor,qtdItensVetor); listarItensLista(mochilaLista); break;
            case 4: buscarItemVetor(mochilaVetor,qtdItensVetor); buscarItemLista(mochilaLista); break;
            case 0:
                printf("\n--- RESULTADO DA COMPARAÇÃO ---\n");
                printf("Vetor: %d comparações, tempo total: %.2f ms\n", compVetor, ((double)tempoVetor/CLOCKS_PER_SEC)*1000);
                printf("Lista Encadeada: %d comparações, tempo total: %.2f ms\n", compLista, ((double)tempoLista/CLOCKS_PER_SEC)*1000);
                printf("\nDigite 0 para encerrar o programa e liberar memória: ");
                int final; scanf("%d",&final);
                mochilaLista = liberarLista(mochilaLista);
                printf("Programa encerrado com segurança!\n");
                return 0;
            default: printf("Opção inválida!\n");
        }
    }while(opcao!=0);

    return 0;
}
