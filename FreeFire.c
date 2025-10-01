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
// PROJETO: CÓDIGO DA ILHA - EDIÇÃO FREE FIRE
// Autor: Fabrício Vieira de Souza
// Matricula: 202501549322.
// Data: 01/10/2025
// Objetivo: construir um sistema de inventário que simule a mochila de loot inicial do jogador.
//https://github.com/EstruturaDados/free-fire-guitfabweb
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Struct que representa um item na mochila
typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções do sistema
void inserirItem(Item mochila[], int *qtdItens);
void removerItem(Item mochila[], int *qtdItens);
void listarItens(const Item mochila[], int qtdItens);
void buscarItem(const Item mochila[], int qtdItens);

int main()
{
    Item mochila[MAX_ITENS]; // Vetor que armazena os itens
    int qtdItens = 0;        // Contador de itens na mochila
    int opcao;

    do
    {
        printf("\n--- MOCHILA VIRTUAL DO JOGADOR ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado

        switch (opcao)
        {
        case 1:
            inserirItem(mochila, &qtdItens);
            break;
        case 2:
            removerItem(mochila, &qtdItens);
            break;
        case 3:
            listarItens(mochila, qtdItens);
            break;
        case 4:
            buscarItem(mochila, qtdItens);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// Função para inserir um item na mochila
void inserirItem(Item mochila[], int *qtdItens)
{
    if (*qtdItens >= MAX_ITENS)
    {
        printf("Erro: mochila cheia!\n");
        return;
    }

    printf("Nome do item: ");
    fgets(mochila[*qtdItens].nome, 30, stdin);
    mochila[*qtdItens].nome[strcspn(mochila[*qtdItens].nome, "\n")] = '\0'; // remover \n

    printf("Tipo do item: ");
    fgets(mochila[*qtdItens].tipo, 20, stdin);
    mochila[*qtdItens].tipo[strcspn(mochila[*qtdItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*qtdItens].quantidade);
    getchar();

    (*qtdItens)++;
    printf("Item inserido com sucesso!\n");
    listarItens(mochila, *qtdItens);
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *qtdItens)
{
    if (*qtdItens == 0)
    {
        printf("A mochila esta vazia.\n");
        return;
    }

    char nome[30];
    printf("Nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int i, encontrado = 0;
    for (i = 0; i < *qtdItens; i++)
    {
        if (strcmp(mochila[i].nome, nome) == 0)
        {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Item nao encontrado!\n");
        return;
    }

    for (int j = i; j < *qtdItens - 1; j++)
    {
        mochila[j] = mochila[j + 1];
    }
    (*qtdItens)--;
    printf("Item removido com sucesso!\n");
    listarItens(mochila, *qtdItens);
}

// Função para listar todos os itens
void listarItens(const Item mochila[], int qtdItens)
{
    if (qtdItens == 0)
    {
        printf("A mochila esta vazia.\n");
        return;
    }
    printf("Itens na mochila:\n");
    for (int i = 0; i < qtdItens; i++)
    {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função de busca sequencial por nome
void buscarItem(const Item mochila[], int qtdItens)
{
    if (qtdItens == 0)
    {
        printf("A mochila esta vazia.\n");
        return;
    }

    char nome[30];
    printf("Nome do item para buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < qtdItens; i++)
    {
        if (strcmp(mochila[i].nome, nome) == 0)
        {
            printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("Item nao encontrado.\n");
}
