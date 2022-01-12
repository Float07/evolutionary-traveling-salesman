# Evolutionary Traveling Salesman

## Introdução
  Para o trabalho da disciplina *SSC0713 - Sistemas Evolutivos Aplicados a Robotica* devemos solucionar um problema usando algoritimos evolutivos. Escolhemos para nosso trabalho o problema do caixeiro viajante e para resolve-lo pretendemos usar um algoritimo evolutivo com uso de mutação.
### Problema
  **qual problema que vamos atacar, explicação precisa, porque ele é um problema**
  O problema do caixeiro viajante é um problema clásico da mátematica descrito a seguir:
  "dado um número de cidades e o custo de viajar de uma para a outra, requer-se a determinação da rota mais barata que visita cada cidade e então retorna para a primeira cidade".
  
  Para achar de forma exata a melhor rota, esse é um problema NP-dificil, ou seja o tempo para solucionalo cresce exponencialmete com o tamanho do problema e fazendo com que a solução por meio de algoritimos nâo heuristicos seja inviavel.
  
### Solução Proposta
  **qual a nossa solução proposta, porque ela foi escolhida, como esperamos que ela desempenhe contra esse problema.**
  A solução proposta é um um algoritimo evolutivo com uso de mutação que foi estudado em classe. ele foi escolhido pois é esperado que processos heuristicos bem aplicados possam criar soluções eficientes com um custo de processamento menor, mesmo que não seja a melhor resposta possivel. esperamos que ele diminua o tempo de processamento enquanto ainda encontra uma rota com otimização proxima da melhor possivel.

## O Algoritmo

### Organização dos dados

No nosso algorítmo cada cidade é representada como uma tupla (x,y) que representa a posição da cidade em uma malha 2D. As cidades estão organizadas em um structure of arrays com as coordenadas x e y e são identificadas por seu índice nesse vetor.

Os indivíduos, que representam uma solução do problema, são um vetor com alguma permutação de todas as cidades da lista. Essa permutação representa a ordem que as cidades são visitadas considerando um circuito fechado.

### Combinação

A combinação de dois indivíduos toma a primeira metade da rota do primeiro indivíduo e preenche as cidades que estão faltando na ordem do segundo, como mostra o esquema.

Rota 1: [**4, 6, 3, 2, 8**, 1, 9, 5, 7, 0]

Rota 2: [**0**, **1**, **9**, 3, **5**, 6, 2, 4, **7**, 8]

Filho : [4, 6, 3, 2, 8, 0, 1, 9, 5, 7]

Após essa combinação ainda existe uma probabilidade configurável de que realize-se permutações aleatórias, representando uma **mutação**.

### Evolução

A geração inicial do algorítmo é gerada a partir de rotas aleatórias com o algoritmo de *Fisher-Yates*.

A geração então é ordenada em ordem crescente de distância total percorrida pela sua rota, sendo que uma fração configurável dessa lista ordenada é selecionada para a geração seguinte.

Uma vez com os melhores indivíduos da geração anterior copiados, o resto do vetor é preenchido com combinações aleatórios desses melhores indivíduos.

A ordenção dos melhores e geração de novos indivíduos se repete até que obtenha-se o número de gerações escolhido

## Setup
  Essa sessãp explica o que você precisa para executar corretamente o projeto. Supões-se o uso de Linux, e não é garantido que esse projeto funcionará corretamente em outros sistemas operacionais.

### Pré-Requisitos
Você precisa ter a ferramenta `make` instalada. Se você não tem pode simplesmente executar o seguinte se você está usando uma distribuição baseada em Debian:
```bash
sudo apt update
sudo apt install build-essential
```
Se você está usando uma distribuição linux que não é baseada em Debian, acesse a [página oficial](https://www.gnu.org/software/make/) para baixar o código fonte.

### Build da bibilioteca
Antes de rodar o Jupyter Notebook nós precisamos fazer a build da biblioteca em C que será utilizada. Para fazer isso simplesmente rode os seguintes comandos na pasta raíz do projeto:
```bash
chmod 755 setup.sh
./setup.sh
```
O primeiro comando dá permissão de execução para o arquivo `setup.sh`, e o segundo a executa.
  
### Resultados
  Resultado da solução, graficos e dados.
  
### Considerações Finais
  A solução foi uma boa solução? desempenho esperado X desempenho obitido. o problema foi solucionado? há alguma forma de melhorar a solução?
