# txttobst

## changelog

### 1.2.3
- destroi ABP do relatório a cada operação requisitada, para evitar que o programa fique sem memória.

### 1.2.2
- documentação mais aprofundada do código.

### 1.2.1
- os cálculos do Fator de Balanceamento, Número de Nodos e Altura da árvore entram no cômputo das comparações do relatório.

### 1.2.0
- não cria mais arquivo temporário, dispensando algumas etapas na criação do relatório.

### 1.1.0
- otimização na função CONTADOR_ABP evita que se percorra a árvore em vão quando se busca uma frequência a qual nenhuma palavra na ABP tem.

### 1.0.0
- passa as palavras do texto para uma ABP de strings, efetua as operações passadas e emite um relatório com o resultado das operações.

### 0.2.0-beta
- passa palavras do texto para uma ABP de strings.

### 0.1.0-alpha
- passa palavras do texto para um array.