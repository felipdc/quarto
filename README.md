# C Quarto!

C Quarto! é uma implementação escrita em C do jogo Quarto!, criado por Blaise Müller.
O game pode ser jogado no modo multiplayer e também contra uma IA.

## Início

### Pré-requisitos
GCC ou outro compilador de C instalado.

### Compilando
Com o GCC instalado e adicionado ao $PATH, utilize:
```
gcc -o main main.c play.c board.c ai.c
```
Também é possível utilizar o Code:Blocks para compilar. Apenas
tenha certeza de que todos os arquivos estão no mesmo projeto
ao compilar.

### Executando

Usuários Linux:
```
./main -argumento1 -argumento2
```

Usuários Windows:

```
main -argumento1 -argumento2
```
Também é possível executar utilizando o Code:Blocks. 
Para inserir argumentos ao executar no Code:Blocks siga:
```
Project > Set programs' arguments...
```
É possível executar o programa com uma entrada de tesde. Para isso, basta utilizar:

```
./main -test
```

## Autor
Felipe Tiago De Carli - https://github.com/felipdc/
