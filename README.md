# Lista 1 - AEDSII

Este repositório tem relação com as questões 1, 2 e 3 da primeira lista avaliativa da matéria de AEDSII.

## Execução dos códigos

Para a questão 2:

```bash
cd quest2
make clean
make
make run
```

Para a questão 3:

```bash
cd quest3
make clean
make
make run
```

## Explicação da questão 1

Ela está presente no PDF dentro da pasta quest1.

## Explicação da questão 2

Com os resultados obtidos ao compilar o código, é possível notar que, para árvores balanceadas, a profundidade de uma árvore binária, no pior caso (onde ela se torna praticamente uma lista encadeada), tem uma diferença discrepante em relação à árvore balanceada. Isso afeta tanto as funções de inserção quanto, principalmente, as de busca, onde o tempo de busca para a árvore binária balanceada é consideravelmente menor que o da árvore não balanceada. E, no contexto deste código, onde realmente não existe nenhum tipo de balanceamento, fica ainda mais evidente essa relação de eficiência entre a árvore e sua profundidade, como demonstrado em literatura.

Quanto ao código em si, ele tem todas as funções básicas desejadas pela questão. Apenas ressalto o fato de que o desenho da árvore neste código ocorre no sentido da esquerda para a direita, e não de cima para baixo, por conta de uma melhor visualização em terminal.

## Explicação da questão 3

O código realiza todas as funções desejadas pela questão. Quanto à decisão de implementação, foi necessário o uso de um `unordered_map` para a melhoria na pesquisa dos dados, pois em relação a um vetor ou uma lista o tempo de busca dessa hash é superiormente mais rápido. Cada chave nela seria a letra inicial de cada palavra inserida, e, em seguida, uma árvore AVL é inserida como conteúdo, devido à garantia mais forte de balanceamento que tem como custo operacional *O(log n)*, o que refletiria no tempo de busca de palavras em grandes quantidades de dados. Pois, como visto no exemplo da questão anterior, quanto melhor for o balanceamento de uma árvore, melhor será sua eficiência durante as operações. E, para otimizar ainda mais a pesquisa, seguindo a função de autocompletar, essa árvore AVL presente em cada chave do hash é baseada na ordem dos prefixos, associando cada palavra a cada prefixo até chegar em uma folha específica que contém somente a palavra.

Sendo possível ver tal eficiência ao realizar a compilação do código onde um teste de busca consegue retornar rapidamente a quantidade total de elementos com mesmo prefixo em uma árvore.

## Contato

Quais quer dúvidas relativas as soluções, entrar em contato pelo email.

email: <rafael.ferreira11.98@gmail.com>
