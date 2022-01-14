# Evolutionary Traveling Salesman

Uma versão em portugês desse README está disponível [aqui](README_PT.md)

## Introduction
  For the *SSC0713 - Sistemas Evolutivos Aplicados a Robotica* coursework, we shall solve a problem using evolutional algorithms. We have chosen for our coursework the Traveling Salesman Problem and to solve it we intend to use an evolutional algorithm with mutation.
### Problem
  The traveling salesman problem is classic mathematic problen discribed as follow:
  "given a number of cities and the costs of travelling from one to the other, it is required to determine the cheapest route that visits each city once and then returns to the initial city". Find a exact solution for this problem is NP-dificult, meaning for a biger number of cities the time need to solve it make this approach unviable.
  
  To find the best route, this is a NP-Hard problem, that is the time to solve it grows exponentially with the size of the problem and that makes the solution with non-heuristic algorithms unviable.
  
### Proposed Solution
  The proposed soluction is a evolutionary algorithm whit usage of mutation, as was studied in class. it was chose because it is expected that a Heuristic process can find a good enough solution, even if is not the best, with less cost. we expect that our algorithm can solve the problem in less time while still find a optimal solution
  
  The proposed solution is an evolutionary algorithm with use of mutation that was studied in class. It was chosen because it is expected that well applied heuristic processes can create efficient solutions with a lower processing cost, even if it may not be the best possible response.

## The Algorithm

### Data Organization

In our algorithm, every city is represented by a tuple (x,y), that represents the position of the city in a 2D grid. The cities are organized with a structure of arrays with the x and y coordinates and are identified by their index in these vectors.

The individuals, who are a solution to the problem, are a vector with some permutation of all the other cities in the list. This permutation represents the order in withc the cities are visited assuming a closed circuit.

### Combination

The combination of two individuals takes the first half of the route from the first indivudual and fills the missing cities at the order from the second, as the diagram shows:

Route 1: [**4, 6, 3, 2, 8**, 1, 9, 5, 7, 0]

Route 2: [**0**, **1**, **9**, 3, **5**, 6, 2, 4, **7**, 8]

Child: [4, 6, 3, 2, 8, 0, 1, 9, 5, 7]

After this combination, there is a adjustable probability of random swaps, which represents a **mutation**.

### Evolution

The starting generation for the algorithm is created from random routes with the *Fisher-Yates* algorithm.

The generation is then ordered in ascending order of total traveled distance of that route, being the fraction of the initial generation that is copied selected for the next generation adjustable.

Once the best individuals from the previous generations are copied, the rest of the vector is filled with random combinations of these best individuals.

The ordering of the best and the creation of new individuals repeats untill we get the selected number of generations.

### Implementation

The implementation of the evolutionary algorithm was made in C and the source code is located in [lib/src](lib/src). Ctypes is used so we can import this C library into Python to easily treat and show the data. 

The `evo_salesman.py` module exports several wrapper functions to the C library, allowing for high-level access without worrying with low-level details. For more information on how to use it read the [documentation](lib/docs.md) or see our experiments in the [Jupyter Notebook](notebook.ipynb).

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

### Run the algorithm
After this you can create your own Python script using the `evo_salesman.py` module. Follow along [the Documentation](lib/docs.md) to learn how to do this, or just run the [Jupyter Notebook](notebook.ipynb) in this project.
