#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct{
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; 
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
typedef enum {
    POR_NOME = 1,
    POR_TIPO = 2,
    POR_PRIORIDADE = 3
} CriterioOrdenacao;

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
#define MAX_ITENS 10
Item mochila[10];
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

// Protótipos das funções

// Menu
void exibirMenu();
void menuDeOrdenacao();
void escolhasDoMenu(int opcao); 

// Gerenciamento de itens
void buscaSequencialPorNome();
void buscaBinariaPorNome();

void insertionSort(CriterioOrdenacao criterio);

void inserirItem();
void removerItem();
void listarItens();

// Funções auxiliares
void limparTela();
void limparBuffer();

int main() {
    // Menu principal com opções:
    int opcao;

    do {
        // 🛡️ Exibição do Menu
        exibirMenu();

        // Leitura da opção
        if (scanf("%d", &opcao) != 1) {
            // Trata entrada não numérica
            opcao = -1; 
            while (getchar() != '\n'); 
        }

        limparTela();

        escolhasDoMenu(opcao);

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            limparBuffer();
        }
    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    } while (opcao != 0);

    return 0;
}

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.]
void limparTela(){
    for(int i = 0 ; i < 10; i++){
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu(){
    printf("==================================================\n");
    printf("         🏝️ Desafio Código da Ilha - Mestre 🎒     \n");
    printf("==================================================\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item por Nome\n");
    printf("3. Listar Itens\n");
    printf("4. Buscar Item (Busca Sequencial)\n");
    printf("5. Ordenar Mochila (Insertion Sort) [%s]\n", ordenadaPorNome ? "ORDENADA POR NOME" : "DESORDENADA");
    printf("6. Buscar Item (Busca Binária)\n");
    printf("0. Sair e Escapar da Ilha\n");
    printf("--------------------------------------------------\n");
    printf("Escolha uma opção: ");
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem(){
    if(numItens >= MAX_ITENS){
        printf("Você não tem mais espaço na mochila!\n");
        return;
    }

    printf("\n--- ADICIONAR ITEM ---\n");

    // PASSO 1: Limpar o buffer APÓS a leitura de opção no main, 
    //            ou se alguma função anterior tiver lido um número.
    //            Aqui, fazemos a limpeza antes do primeiro fgets.
    limparBuffer(); 
    
    // Leitura do Nome (Usando fgets)
    printf("Nome do Item (max 49 caracteres): ");
    // Lê até o tamanho - 1 (para o \0), lendo do teclado (stdin)
    if (fgets(mochila[numItens].nome, 50, stdin) == NULL) return; 
    // Remove a quebra de linha (\n) que o fgets adiciona
    mochila[numItens].nome[strcspn(mochila[numItens].nome, "\n")] = '\0';

    // Leitura do Tipo (Usando fgets)
    printf("Tipo do Item (ex: Arma, Cura, Municao - max 29 caracteres): ");
    if (fgets(mochila[numItens].tipo, 30, stdin) == NULL) return;
    mochila[numItens].tipo[strcspn(mochila[numItens].tipo, "\n")] = '\0';

    // Leitura da Quantidade (Ainda usa scanf para números)
    printf("Quantidade: ");
    while (scanf("%d", &mochila[numItens].quantidade) != 1 || mochila[numItens].quantidade <= 0) {
        printf("Entrada inválida. Digite uma quantidade válida (número positivo): ");
        // Limpa o buffer após a leitura falhar
        limparBuffer(); 
    }
    
    // Leitura da Prioridade (Nível Mestre - Mantenha por enquanto)
    printf("Prioridade (1-Mais Alta, 5-Mais Baixa): ");
    while (scanf("%d", &mochila[numItens].prioridade) != 1 || mochila[numItens].prioridade < 1 || mochila[numItens].prioridade > 5) {
        printf("Entrada inválida. Digite uma prioridade entre 1 e 5: ");
        // Limpa o buffer após a leitura falhar
        limparBuffer(); 
    }

    numItens++; // Incrementa o contador de itens
    ordenadaPorNome = false;
    printf("\nItem '%s' (Prioridade %d) adicionado com sucesso! %d itens na mochila.\n", 
        mochila[numItens - 1].nome, mochila[numItens - 1].prioridade, numItens);
}

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
// Remove um item da mochila pelo nome.
void removerItem() {
    if (numItens == 0) {
        printf("\nMochila vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o NOME do item a ser removido: ");
    if (scanf("%29s", nomeBusca) != 1) return;

    int i, j;
    int encontrado = 0;

    for (i = 0; i < numItens; i++) {
        // Compara o nome digitado com o nome do item na mochila
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Item encontrado!
            encontrado = 1;

            // Loop para realocar os itens (remove o item na posição i)
            for (j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1]; // Move o próximo item para a posição atual
            }

            numItens--; // Decrementa o contador
            ordenadaPorNome = false;
            printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
            break; // Sai do loop após remover o item
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
// Lista todos os itens presentes na mochila em formato de tabela.
void listarItens() {
    if (numItens == 0) {
        printf("\nMochila vazia. Comece a coletar recursos!\n");
        return;
    }

    printf("\n--- INVENTÁRIO ATUAL (%d/%d) ---\n", numItens, MAX_ITENS);
    printf("| %-29s | %-19s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("+-------------------------------+---------------------+------------+\n");

    for (int i = 0; i < numItens; i++) {
        printf("| %-29s | %-19s | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("+-------------------------------+---------------------+------------+\n");

    limparBuffer();
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao(){
    printf("==================================================\n");
    printf("         ESCOLHA O TIPO DE ORDENAÇÃO \n");
    printf("1. Ordenar por nome\n");
    printf("2. Ordenar por tipo\n");
    printf("3. Ordenar por prioridade\n");
    printf("--------------------------------------------------\n");
    printf("Escolha uma opção: ");

    CriterioOrdenacao escolha; 
    int temp_escolha;
    
    if (scanf("%d", &temp_escolha) != 1 || temp_escolha < 1 || temp_escolha > 3) {
        printf("\nOpção inválida para ordenação.\n");
        limparBuffer();
        return;
    }
    limparBuffer();
    
    escolha = (CriterioOrdenacao)temp_escolha; 

    comparacoes = 0;

    insertionSort(escolha);

    ordenadaPorNome = (escolha == POR_NOME); 
    
    printf("\nOrdenação Concluída. Total de %d comparações realizadas.\n", comparacoes);
}

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void insertionSort(CriterioOrdenacao criterio){

    // varíaveis para representar o item e fazer referencia a eles
    Item chave;
    int item, item_sublista;

    switch (criterio)
    {
        // - Por nome (ordem alfabética)
        case POR_NOME:
            // Passa por todos os itens na mochila
            for(item = 1; item < numItens; item++){
                chave = mochila[item];
                item_sublista = item - 1;
                
                // Verifica se o item da sublista é maior e o desloca para a direita
                while(item_sublista >= 0 && strcmp(mochila[item_sublista].nome, chave.nome) > 0){
                    comparacoes++; 
                    mochila[item_sublista + 1] = mochila[item_sublista];
                    item_sublista--; 
                }
                
                // Insere o item chave na posição correta
                mochila[item_sublista + 1] = chave;
            }
            break;
        // - Por tipo (ordem alfabética)
        case POR_TIPO:
            for(item = 1; item < numItens; item++){
                chave = mochila[item];
                item_sublista = item - 1;
                
                // Verifica se o item da sublista é maior e o desloca para a direita
                while(item_sublista >= 0 && strcmp(mochila[item_sublista].tipo, chave.tipo) > 0){
                    comparacoes++; 
                    mochila[item_sublista + 1] = mochila[item_sublista];
                    item_sublista--; 
                }
                
                // Insere o item chave na posição correta
                mochila[item_sublista + 1] = chave;
            }
            break;

        // - Por prioridade (da mais alta para a mais baixa)
        case POR_PRIORIDADE:
            for(item = 1; item < numItens; item++){
                chave = mochila[item];
                item_sublista = item - 1;
                
                // Verifica se o item da sublista é maior e o desloca para a direita
                while(item_sublista >= 0 && chave.prioridade < mochila[item_sublista].prioridade){
                    comparacoes++; 
                    mochila[item_sublista + 1] = mochila[item_sublista];
                    item_sublista--; 
                }
                
                // Insere o item chave na posição correta
                mochila[item_sublista + 1] = chave;
            }
            break;
        default:
            break;
    }
}

void buscaSequencialPorNome() {
    if (numItens == 0) {
        printf("\nMochila vazia. Nada para buscar.\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o NOME do item a ser buscado: ");
    
    limparBuffer(); 
    if (fgets(nomeBusca, 50, stdin) == NULL) return;
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove o \n

    for (int item = 0; item < numItens; item++) {
        // Usa strcmp para comparação
        if (strcmp(mochila[item].nome, nomeBusca) == 0) {
            printf("\nItem ENCONTRADO (Posicao %d):\n", item + 1);
            printf("---------------------------------------\n");
            printf("Nome:       %s\n", mochila[item].nome);
            printf("Tipo:       %s\n", mochila[item].tipo);
            printf("Quantidade: %d\n", mochila[item].quantidade);
            printf("Prioridade: %d\n", mochila[item].prioridade);
            printf("---------------------------------------\n");
            return; // Item encontrado, sai da função
        }
    }

    // Se o loop terminar sem encontrar nada
    printf("\nItem '%s' não encontrado na mochila.\n", nomeBusca);
    limparBuffer();
}

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("\nERRO: A mochila precisa estar ordenada por NOME para Busca Binária (Opcao 6).\n");
        return;
    }
    if (numItens == 0) {
        printf("\nMochila vazia. Nada para buscar.\n");
        return;
    }

    // 1. Definições Iniciais
    int inicio = 0;
    int fim = numItens - 1; // O último índice do array
    int meio;
    int comparacao;
    
    char nomeBusca[50];
    printf("Digite o NOME do item a ser buscado: ");
    
    limparBuffer(); 
    if (fgets(nomeBusca, 50, stdin) == NULL) return;
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    comparacoes = 0;

    // 2. Loop principal: Encontra o meio e compara
    while (inicio <= fim) {

        meio = inicio + (fim - inicio) / 2;
        
        comparacoes++;
        comparacao = strcmp(mochila[meio].nome, nomeBusca);

        if (comparacao == 0) {
            // Item encontrado
            printf("\nItem ENCONTRADO (Posicao %d) em %d comparacoes:\n", meio + 1, comparacoes);
            printf("---------------------------------------\n");
            printf("Nome:       %s\n", mochila[meio].nome);
            printf("Tipo:       %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            printf("---------------------------------------\n");
            return;
            
        } else if (comparacao < 0) {
            // Descarta a metade esquerda. O NOVO INÍCIO é depois do meio.
            inicio = meio + 1;
            
        } else { // comparacao > 0
            // Descarta a metade direita. O NOVO FIM é antes do meio.
            fim = meio - 1;
        }
    }
    
    // Se o loop terminar sem encontrar nada
    printf("\nItem '%s' não encontrado na mochila em %d comparacoes.\n", nomeBusca, comparacoes);
    limparBuffer();
}

void escolhasDoMenu(int opcao){
    switch (opcao) {
        // 1. Adicionar um item
        case 1: 
            inserirItem();
            break;

        // 2. Remover um item
        case 2:
            removerItem();
            break;

        // 3. Listar todos os itens
        case 3:
            listarItens();
            break;
            
        // 4. Busca Sequencial
        case 4:
            buscaSequencialPorNome();
            break;
            
        // 5. Ordenar os itens por critério
        case 5:
            menuDeOrdenacao();
            break;

        // 6. Realizar busca binária por nome
        case 6:
            buscaBinariaPorNome();
            break;

        // 0. Sair
        case 0:
            printf("\nBoa sorte na fuga! Salvamento encerrado.\n");
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            break;
    }
}

// Limpa o buffer de entrada (stdin) para garantir que o próximo fgets() ou scanf() leia corretamente.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}