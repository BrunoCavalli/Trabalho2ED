# Trabalho2ED

Projeto em C++ que implementa um livro de ordens (order book) com três listas principais: ordens de compra, ordens de venda e transações. Quando uma nova ordem chega, o sistema procura uma contraparte compatível, executa a transação e registra o resultado no histórico. Também é possível cancelar ordens e consultar o estado atual do livro.

## Funcionalidades

- Inserção de ordens de compra e venda.
- Casamento automático entre ordens compatíveis.
- Cancelamento de ordens por identificador.
- Listagem das ordens de compra, venda e transações realizadas.

## Compilação

Este projeto pode ser compilado com `g++` com o seguinte comando:

```powershell
g++ -std=c++17 main.cpp OrderBook.cpp Order.cpp Transaction.cpp -o order_book.exe
```

Se você estiver usando o compilador do Visual Studio, o equivalente é compilar todos os arquivos `.cpp` do projeto em um único executável.

## Execução

Depois de compilar, execute o programa com:

```powershell
.\order_book.exe
```

O arquivo `main.cpp` contém uma sequência de testes que mostra o comportamento do sistema: inserção de ordens, execução de transações, cancelamento e consulta dos dados armazenados.


## Organização interna dos dados

O sistema utiliza três listas encadeadas implementadas manualmente (sem STL):

- **Ordens de compra**: lista encadeada de nós contendo objetos `Order`
- **Ordens de venda**: lista encadeada de nós contendo objetos `Order`
- **Transações**: lista encadeada de nós contendo objetos `Transaction`

A busca pela melhor contraparte é feita percorrendo a lista inteira — 
menor preço para ordens de compra, maior preço para ordens de venda, 
desempatando pelo timestamp. A remoção é feita redirecionando ponteiros, 
sem deslocar elementos.