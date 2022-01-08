# Evolutionary Traveling Salesman

## introdução/resumo
  Para o trabalho da disciplina ... devemos solucionar  um problema usando algoritimos evolutivos. Escolhemos para nosso trabalho o problema do caixeiro viajante e para resolve-lo pretendemos usar um algoritimo evolutivo com uso de mutação.
### problema
  **qual problema que vamos atacar, explicação precisa, porque ele é um problema**
  The traveling salesman problem is classic mathematic problen discribed as follow:
  "given a number of cities and the costs of travelling from one to the other, it is required to determine the cheapest route that visits each city once and then returns to the initial city". Find a exact solution for this problem is NP-dificult, meaning for a biger number of cities the time need to solve it make this approach unviable.
  
  
  para achar de forma exata a melhor rota, esse é um problema NP-dificil, ou seja o tempo para solucionalo cresce exponencialmete com o tamonho do problema e fazendo com que a solução por meio de algoritimos nâo heuristicos seja inviavel.
  
### solução proposta
  **qual a nossa solução proposta, porque ela foi escolhida, como esperamos que ela desempenhe contra esse problema.**
  The proposed soluction is a evolutionary algorithm whit usage of mutation, as was studied in class. it was chose because it is expected that a Heuristic process can find a good enough solution, even if is not the best, with less cost. we expect that our algorithm can solve the problem in less time while still find a optimal solution
  
  
  a solução proposta é um um algoritimo evolutivo com uso de mutação que foi estudado em classe. ele foi escolhido pois é esperado que processos heuristicos bem aplicados possam criar soluções eficientes com um custo de processamento menor, mesmo que não seja a melhor resposta possivel. esperamos que ele diminua o tempo de processamento enquanto ainda encontra uma rota com otimização proxima da melhor possivel.
  
### desenvolvimanto da solução (pode ser desnecessario?)
  explicar detalhadamente o funcionamento da solução, explicar o codigo(ou não), qualquer coisa sobre o desenvolvimento vai aqui
  
## Setup
  This section explain what you need to do to properly run the project. It's assumed you are using Linux, and it's not guaranteed this project will properly run in other operating systems.

### Prerequisites
You need to have the `make` tool installed. If you don't you can simply run the following if you are using a Debian-based distro:
```bash
sudo apt update
sudo apt install build-essential
```
If you are using a Linux distro not based on Debian, access the [official page](https://www.gnu.org/software/make/) to download the source.

### Build the Library
Before running the Jupyter Notebook we need to build the C library that will be used. To do that simply run the following commands in the project's root folder:
```bash
chmod 755 setup.sh
./setup.sh
```
The first command gives execution permission to the file `setup.sh`, and the second executes it.
  
### resultados
  resultado da solução, graficos e dados.
  
### considerações finais
  a solução foi uma boa solução? desempenho esperado X desempenho obitido. o problema foi solucionado? há alguma forma de melhorar a solução?
