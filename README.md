# 🔫🎒 Desafio Código da Ilha – Edição Free Fire

Bem-vindo ao **Desafio Código da Ilha – Edição Free Fire!**  
Neste desafio, você irá simular o gerenciamento de um **inventário de sobrevivência** em uma ilha misteriosa, utilizando a linguagem **C**.

A empresa **MateCheck** encarregou você de desenvolver o sistema de **mochila virtual** que ajudará os sobreviventes a se prepararem para escapar da ilha.  
O desafio é dividido em três níveis: **Novato**, **Aventureiro** e **Mestre**, cada um com mais complexidade e poder.

## 🧠 Nível Mestre: Ordenação e Busca Binária

### 🆕 Diferenças em relação ao Nível Aventureiro

- Adição do campo **prioridade** aos itens (valores de 1 a 5)
- Possibilidade de **ordenar** a mochila por **nome**, **tipo** ou **prioridade**
- Implementação da **busca binária** por nome com verificação de ordenação

### ⚙️ Funcionalidades

- **Menu de ordenação**: o jogador escolhe o critério desejado
- Contador de **comparações na ordenação** para análise de desempenho
- **Busca binária** com validação de pré-requisito (lista deve estar ordenada por nome)

### 💡 Conceitos Adicionados

- **Enumeração** (`enum`) para critérios de ordenação
- **Ordenação com Insertion Sort**
- **Busca binária** (`binary search`)
- Uso de **bool** para controle de estado
- **Análise de desempenho** com contador de comparações

### 📥 Entrada

O usuário:

1. Adiciona itens com prioridade
2. Ordena os itens
3. Realiza busca binária pelo nome do item

### 📤 Saída

- Mochila **ordenada** com base no critério escolhido
- Exibição dos **dados do item buscado** ou mensagem de erro
- **Quantidade de comparações** realizadas durante a ordenação



## 🏁 Conclusão

Ao completar qualquer nível do **Desafio Código da Ilha – Edição Free Fire**, você terá avançado significativamente na programação em **C**, desenvolvendo habilidades práticas de:

- Manipulação de **estruturas e arrays**
- Criação de **menus interativos**
- Implementação de **buscas e ordenações**
- **Pensamento modular** e boas práticas de software

Cada nível representa uma missão rumo à **sobrevivência total**.  
Escolha seu nível, prepare sua mochila... e **boa sorte na ilha!** 🏝️💼🔍

> Equipe de Ensino – MateCheck

Desafio Código da Ilha – Nível Mestre

Este programa implementa um sistema de gerenciamento de itens em uma mochila virtual, utilizando a linguagem C.
Ele permite adicionar, remover, listar, ordenar e buscar itens armazenados na mochila.
O objetivo é auxiliar o usuário no controle dos objetos coletados durante a simulação.

🧩 Estrutura Geral do Sistema

A mochila pode armazenar até 10 itens, e cada item possui as seguintes informações:

Nome

Tipo (ex.: arma, cura, munição)

Quantidade

Prioridade (1 = mais importante, 5 = menos importante)

O programa funciona por meio de um menu interativo, onde o usuário escolhe as ações desejadas.

📋 Funcionalidades do Sistema
1. Adicionar Item

Permite inserir um novo item na mochila.
O programa solicita:

Nome do item

Tipo do item

Quantidade (valor inteiro positivo)

Prioridade (entre 1 e 5)

Caso a mochila esteja cheia, o usuário é avisado.

2. Remover Item

Remove um item existente pelo nome.
Se o item for encontrado, ele é removido e os demais itens são reorganizados para manter o vetor contínuo.
Caso não exista, o programa informa que o item não foi localizado.

3. Listar Itens

Exibe todos os itens registrados em formato de tabela, mostrando nome, tipo e quantidade.
Se a mochila estiver vazia, uma mensagem adequada é exibida.

4. Busca Sequencial por Nome

Realiza uma verificação item a item até encontrar o nome desejado.
Esse método funciona mesmo se a mochila não estiver ordenada.

5. Ordenar Itens (Insertion Sort)

O usuário escolhe o critério de ordenação:

Por nome

Por tipo

Por prioridade

O algoritmo utilizado é o Insertion Sort, e ao final é exibida a quantidade de comparações realizadas (útil para fins de análise de desempenho).

Ao ordenar por nome, o programa ativa o indicador interno ordenadaPorNome = true, permitindo o uso da busca binária.

6. Busca Binária por Nome

Disponível somente se os itens estiverem ordenados por nome.
O programa verifica essa condição automaticamente.

A busca binária localiza o item de maneira mais rápida, reduzindo o número de comparações.

Se o nome não estiver presente na lista, é mostrada uma mensagem informando que o item não foi encontrado.

7. Sair

Encerra a execução do programa.

🛠️ Como o Programa Opera Internamente

Todos os itens são armazenados em um vetor fixo de 10 posições.

O programa utiliza uma variável global numItens para controlar quantos elementos estão ocupados.

A ordenação modifica diretamente o vetor.

A busca binária só é permitida quando o vetor estiver ordenado por nome.

Para evitar erros de entrada, o código realiza limpeza de buffer sempre que necessário.

🧾 Resumo do Fluxo do Usuário

Abrir o programa

Escolher opções no menu

Adicionar, remover ou visualizar itens

Ordenar a mochila quando desejar

Usar busca binária caso queira localizar itens de forma mais rápida

Encerrar o programa quando terminar