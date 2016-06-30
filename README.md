# Projeto 3 - Multicore e Aceleração em Hardware - Grupo 4

## Integrantes:

| Nome|RA|
|---|---|
|André Nogueira Brandão |116130|
|Matheus Pinheiro dos Santos |119920|
|Carlos Gregoreki| 104721|
|Gustavo Rodrigues Basso| 105046|
|Renato Shibata|082674|

## Introdução e Objetivos

Ao longo do tempo, processadores e computadores têm se tornado cada vez mais complexos. Supercomputadores dotados de centenas de GPU's tomaram parte na cena da tecnologia e superprocessamento. Isso foi possível graças ao estudo de arquitetura de computadores e das técnicas de projeto como paralelização de processamento e aceleração em hardware.

Neste projeto, objetivamos observar o comportamento da execução de um algoritmo simples em várias simulações de paralelismo e aceleração, conjuntas ou não, podendo mostrar o impacto da adoção desses detalhes em um processador.

## Metodologia

Para atingir nossos objetivos, escolhemos adotar para execução um software simples de ***multiplicação de matrizes inteiras de tamanho NxN***. Esse algoritmo nos permite trabalhar tanto com a aceleração quanto com a sua paralelização.

As simulações das execuções do algoritmo foram feitas para os seguintes processadores:

* Single Core
* Single Core Acelerado
* Multicore 2 
* Multicore 4
* Multicore 8
* Multicore 2 Acelerado
* Multicore 4 Acelerado
* Multicore 8 Acelerado 

Para a contagem dos ciclos utilizados por cada processador foi utilizada uma implementação do arquivo *mips_isa.cpp* utilizada no projeto anterior, que conta os ciclos de acordo seguindo as seguintes especificações:

| Tipo de Instrução|Peso|
|---|---|
|Acesso à memória |10|
|Operações de Controle |3|
|Multiplicação e Divisão| 2|
|Instruções NOP| 0|
|Demais|1|

Após a coleta da quantidade de ciclos para cada processador, construímos uma tabela que amostra todas as informações das execuções, e construímos gráficos que estão colocados nas seções seguintes para melhor visualização dos dados.

## Implementação
A seguir, explicamos como se dá a paralelização e a aceleração em hardware.

### Acelerador: *Multiplicação das Matrizes*
A parte do código que foi acelerada através do periférico foi a multiplicação das matrizes. À priori, uma outra escolha tinha sido tomada, que foi acelerar apenas operações de multiplicação. Entretanto, observamos as execuções que a quantidade de ciclos gastos para enviar os dados para o periférico (penalidade) eram superiores que os ciclos que uma operação de multiplicação direta gastaria. Desta forma, a aceleração não surtiria efeito positivo. Portanto, escolhemos acelerar a multplicação completa das matrizes, de forma que o nosso acelerador fosse complexo o suficiente para mostrar resultados significativos.

Para o acelerador, sua implementação é simples. Ele recebe via TLM (protocolo) as duas matrizes declaradas no software, elemento por elemento, e guarda uma cópia dessas duas matrizes dentro dele mesmo. Claramente, admitimos que o periférico teria quantidade de memória o suficiente para operar dessa forma. 

Depois de armazenar essas matrizes, o periférico executa a operação de multiplicação das matrizes e guarda o resultado em uma matriz separada. Esse resultado é retornado para o software de maneira serial, elemento por elemento à medida que o software vai requisitando leituras do endereço de memória do periférico. 

### Paralelização: *Envio das matrizes*
A parte paralelizada foi o envio das matrizes para o periférico. Isto é, por exemplo, para um processador multicore de 2 cores, o primeiro envia para o periférico metade da primeira e segunda matriz, e o segundo core envia a outra metade. 
Para receber o resultado, o processador consulta o endereço de memória do elemento do periférico (fazendo que este execute a operação de multiplicação das matrizes) e recebe o resultado de forma serial.

O maior desafio da implementação foi garantir que a matriz resultante sairia correta, pois se o periférico e o software não estiverem sincronizados (o que foi feito através de locks) o processador poderia enviar os elementos para o periférico de maneira embaralhada, o que comprometeria a integridade do resultado final. 

## Experimentos realizados

Os experimentos, como colocados na metodologia, consistiram da execução do algoritmo para cada um dos processadores listados anteriormente. 

## Resultados obtidos e Análise:
Os dados obtidos pelas execuções podem ser encontrados [nesta tabela](https://docs.google.com/spreadsheets/d/1V_iAIqIIxuZ95ZEGT3PGLqeaKyPh6qDj9ujG_5Aptxs/edit?usp=sharing).

Primeiramente, observando a primeira aba, podemos ver claramente um ganho muito grande de performance aplicando a aceleração para um processador single core: a quantidade de ciclos do não acelerado é 13 vezes maior que o acelerado. Um detalhe que chama a atenção é a quantidade de instruções de multiplicação e divisão que foram reduzidas a zero com a aceleração. Isso era esperado, pois o periférico é que faz todas as operações dessa natureza.

Agora, visualizando a segunda aba que contém os dados para os processadores multicore sem aceleração, observamos que a quantidade de ciclos médio por core do multicore-2 é aproximadamente o dobro do multicore-4, que por sua vez é o dobro do multicore-8. Isso também era bem esperado para esse algoritmo de multiplicação de matrizes. Também podemos notar que a quantidade de total de instruções dos 3 processadores são semelhantes, entretanto, cada core executa apenas uma parte dessas instruções.

![](http://raw.githubusercontent.com/gbasso06/mc723_proj3/master/charts/01%20-%20All%20vs%20Single.png)

O gráfico acima traduz a relação da quantidade de ciclos de todos os processadores em relação ao single core. Aqui, podemos notar que a quantidade de ciclos do single core é a maior de todos os outros processadores e que a aceleração desse processador tem um ganho de performance evidente, pois a quantidade de ciclos do não acelerado é 13 vezes maior que o acelerado. Podemos observar também a relação da divisão da quantidade de ciclos à medida que comparamos o single core não acelerado com os multicores não acelerados.

![](http://raw.githubusercontent.com/gbasso06/mc723_proj3/master/charts/02%20-%20All%20vs%20Single%20Acc.png)

O gráfico da imagem anterior mostra a relação de todos os processadores com o processador single core acelerado. Comparando com os multicores, podemos notar uma performance melhor que os não acelerados: cerca de 7 vezes menor que o multicore 2 e duas vezes menor que multicore 8.

Para comparar os multicores acelerados, podemos dizer que, de acordo com o gráfico a seguir, os acelerados possuem melhor desempenho visível. Comparando o multicore 2 com o multicore 2 acelerado, vemos que o número de instruções é 1100% maior que no acelerado. 

![](http://raw.githubusercontent.com/gbasso06/mc723_proj3/master/charts/09%20-%20All%20Mult%20vs%20Mult%202.png)

A seguir temos o gráfico comparativo entre os multicores acelerados.

![](http://raw.githubusercontent.com/gbasso06/mc723_proj3/master/charts/10%20-%20All%20Multi%20Acc%20vs%20Multi%202%20Acc.png)

Vemos na imagem que a performance do multicore 4 acc é aproximadamente 35% melhor que a do multicore 2 acc, e que multicore 8 acc é 68% melhor.

## Conclusões

Com esse projeto de estudo de paralelização e aceleração em hardware, pudemos verificar claramente o impacto que a aplicação desses detalhes em um processador causam. 

Pudemos ver que, para o software adotado - multiplicação de matrizes NxN inteiras - o desempenho de processadores não acelerados e não paralelizados pode chegar a ser 45 vezes pior que os processadores multicore 8 acelerados. Isto é, processadores multicore 8 acelerados tiveram apenas cerca de 2% do número de ciclos que o single core não acelerado. Também deve-se expôr que o processador single core acelerado teve performance melhor que os multi core não acelerados, concluindo que aceleração, dependendo do seu propósito, pode ser uma técnica de projeto extremamente eficiente. 

Finalmente, podemos afirmar, com os dados obtidos, que podemos classificar, para o software em questão, os processadores em uma ordem progressiva de performance coloca à seguir:

* Single Core
* Multicore 2
* Multicore 4
* Multicore 8
* Single Core acelerado
* Multicore 2 acelerado
* Multicore 4 acelerado
* Multicore 8 acelerado
