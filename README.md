# Projeto 3 - Grupo 4

## Integrantes:

| Nome|RA|
|---|---|
|André Nogueira Brandão |116130|
|Matheus Pinheiro dos Santos |119920|
|Carlos Gregoreki| 104721|
|Gustavo Rodrigues Basso| 105046|
|Renato Shibata|082674|

## Implementação
O programa escolhido foi: **multiplicação de duas matrizes inteiras tamanho NxN**.
A parte do código que foi acelerada através do periférico foi a multiplicação das matrizes e a parte paralelizada foi o envio das matrizes para o periférico


### Acelerador: *Multiplicação das Matrizes*
O acelerador foi implementado da seguinte maneira:
- Armazenamos as duas matrizes no periférico (adminitndo que ele tem memória o suficiente para armazená-las. 
- Uma vez que o(s) processador(es) terminam de enviar os elementos ao periférico, este realiza a multiplicação das matrizes.
- O resultado só enviado de volta depois que o(s) processador(es)terminam de enviar todos os número e requisitam o resultado final
- O periférico devolve serialmente, 1 a 1, os elementos da matiz resultado

### Paralelização: *Envio das matrizes*
A paralelização do envio das matrizes ocorre da seguinte maneira:
- Cada processador envia 1/(n de processadores) das matrizes para o periférico.
- Os elementos são enviados serialmente, 1 a 1, para o periférico.

O maior desafio da implementação foi garantir que a matriz resultante sairia correta, pois se o periférico e o software não estiverem sincronizados (o que foi feito através de locks) o processador poderia enviar os elementos, para o periférico, de maneira embaralhada, o que comprometeria a integridade do resultado final. 

## Experimentos realizados

Para analisar o desempenho do acelerador e da paralelização, de maneira geral, calculamos o número de ciclos para os seguintes casos:
- Single-core sem aceleração
- Single-core acelerado
- Multi-core não acelerado
- Multi-core acelerado

Além disso estabelecemos peso para cada tipo de instrução da sgeuinte maneira:
- Acesso a memória: Peso 10
- Operações de controle (jump ou branch): Peso 3
- Mult e Div: Peso 2
- Demais: Peso 1



## Resultado obtidos:
### Multi-Core sem aceleração

- 2 Cores

||nº de Intruções|nº ciclos|nº de acessos a Memória|nº Operações de Controle|nº Mult e Div|nº das Demais
|---|---|---|---|---|---|---|
Processador 1|155998|1040094|69772|35192|32558|171682|
Processador 2|157826|1046800|70221|35421|32768|172791|

- 4 Cores

||nº de Intruções|nº ciclos|nº de acessos a Memória|nº Operações de Controle|nº Mult e Div|nº das Demais
|---|---|---|---|---|---|
Processador 1|---|---|---|---|---|
Processador 2|---|---|---|---|---|
Processador 3|---|---|---|---|---|
Processador 4|---|---|---|---|---|

- 8 Cores

||nº de Intruções|nº ciclos|nº de acessos a Memória|nº Operações de Controle|nº Mult e Div|nº das Demais
|---|---|---|---|---|---|
Processador 1|---|---|---|---|---|
Processador 2|---|---|---|---|---|
Processador 3|---|---|---|---|---|
Processador 4|---|---|---|---|---|
Processador 5|---|---|---|---|---|
Processador 6|---|---|---|---|---|
Processador 7|---|---|---|---|---|
Processador 8|---|---|---|---|---|
