# MC723 - Projeto 3 - Roteiro

## Integrantes:

| Nome|RA|
|---|---|
|André Nogueira Brandão |116130|
|Matheus Pinheiro dos Santos |119920|
|Carlos Gregoreki| 104721|
|Gustavo Rodrigues Basso| 105046|

## Programa Escolhido:
O programa escolhido para analisarmos os efeitos da paralelização e aceleração foi o Calculo de Multiplicação de Matrizes NxN.

## Blocos/Funções a serem otimizadas:
- Serão paralelizados as múltiplicações de cada linha da matriz A pelas várias colunas da matriz B.
- A função escolhida para ser acelerada foi a multiplicação de pontos flutuantes, visto que as matrizes devem aceitar números fracionários.

## Estimativa de ganho de Desempenho:
- Observa-se que, em decorrência da simplicidade do algoritmo, podemos admitir que a paralelização terá efeito de dividir o tempo de processamento na quantidade de cores adotados. Ou seja, se tivermos 4 cores, então podemos dizer que a estimativa de tempo será ** tempo inicial / número de cores **.
- Para a aceleração, se tivermos uma matriz completa com apenas números de ponto flutuante, podemos prever que, como as operações de ponto flutuantel levam 4 ciclos a para serem executadas, deveremos ter um ganho de, aproximadamente, 25%.

## Experimentos a serem realizados:
- Configuração serial sem aceleração
- Configuração serial com aceleração
- Configuração Paralela sem aceleração
- Configuração Paralela com aceleração
