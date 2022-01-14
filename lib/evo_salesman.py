####################################################################################################
# IMPORTS
####################################################################################################

import ctypes
import numpy as np
from ctypes import POINTER
import pathlib
import random



####################################################################################################
# CLASSES DEFINITIONS
####################################################################################################

# A city is defined by its x and y coordinates
class City:
    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y
    
    def __str__(self) -> str:
        return '(x,y) = (' + str(self.x) + ',' + str(self.y) + ')'

# An individual is defined by a route between the cities
# And a route is a list of integers that indicates in which order the individual went through the cities
# Each city is represented by an integer
# Each individual belongs to a generation
class Individual:
    def __init__(self, route) -> None:
        self.route = route
    
    def __str__(self) -> str:
        individual_string = ''
        for city in self.route:
            individual_string += str(city) + ' '
        return individual_string.rstrip()

    # The total distance of the route this individual takes
    @property
    def total_distance(self):
        cities = get_cities()
        distance = 0

        for index, _ in enumerate(cities):
            city1Index = self.route[index]
            city2Index = None
            # If city 1 is the last in the route, connects to the first city in the route
            if index == len(cities) - 1:
                city2Index = self.route[0]
            else:
                city2Index = self.route[index + 1] 
            city1 = cities[city1Index]
            city2 = cities[city2Index]

            city1Array = np.array((city1.x, city1.y))
            city2Array = np.array((city2.x, city2.y))
            distance += np.linalg.norm(city1Array - city2Array)
        
        return distance
        
            


# A generation is defined by a list of individuals
class Generation:
    def __init__(self, individuals) -> None:
        self.individuals = individuals

    def __str__(self) -> str:
        generation_string = ''
        for index, individual in enumerate(self.individuals):
            generation_string += 'Individual #' + str(index) + ': ' + str(individual) + '\n'
        return generation_string

# Child class that interfaces with the C struct "cities"
class CitiesStruct(ctypes.Structure):
    _fields_ = [('x', POINTER(ctypes.c_int)),
                ('y', POINTER(ctypes.c_int))]



####################################################################################################
# GLOBAL VARIABLES
####################################################################################################
NUM_CITIES = -1
NUM_GENERATIONS = -1
NUM_INDIVIDUALS = -1
MAP_SIZE = -1

# Load the C library
LIBEVO = ctypes.CDLL(str(pathlib.Path(__file__).parent.resolve()) + "/src/libevo.so")
# Set the return type as void
LIBEVO.define_parametros.restype = None
LIBEVO.realiza_simulacao.restype = None
LIBEVO.limpa_memoria.restype = None
LIBEVO.cria_cidades.restype = None
# Set the return type as a 3d int array
LIBEVO.get_generations.restype = POINTER(POINTER(POINTER(ctypes.c_int)))
# Set the return type as a pointer to CitiesSctruct
LIBEVO.get_city_coordinates.restype = POINTER(CitiesStruct)



####################################################################################################
# WRAPPER FUNCTIONS
####################################################################################################

# Sets the parameters used for city generation and simulation
# If this function is not run before create_cities() or run_simulation(), the default parameters
# will be used
def set_parameters(num_cities=10, num_generations=10, num_individuals=10, mutation_prob=0, 
old_generation_ratio=0.5, map_size=100, rand_seed=-1):
    # Set the global variables so they can be recovered later
    global NUM_CITIES
    global NUM_GENERATIONS
    global NUM_INDIVIDUALS
    global MAP_SIZE
    NUM_CITIES = num_cities
    NUM_GENERATIONS = num_generations
    NUM_INDIVIDUALS = num_individuals
    MAP_SIZE = map_size

    # If received a negative rand_seed, generate a random number
    if rand_seed < 0:
        rand_seed = random.randint(1, 100000000)

    # Set the parameters
    num_cities_c = ctypes.c_int(num_cities)
    num_generations_c = ctypes.c_int(num_generations)
    num_individuals_c = ctypes.c_int(num_individuals)
    mutation_prob_c = ctypes.c_float(mutation_prob)
    old_generation_ratio_c = ctypes.c_float(old_generation_ratio)
    map_size_c = ctypes.c_int(map_size)
    rand_seed_c = ctypes.c_int(rand_seed)
    LIBEVO.define_parametros(num_cities_c, num_generations_c, num_individuals_c, mutation_prob_c,
    old_generation_ratio_c, map_size_c, rand_seed_c)

# Generates a set of cities to be used during simulation
# The same cities will be used in multiple simulations if this function is not run between them
# If this function is not run before run_simulation(), a set of cities will be automatically created
def create_cities():
    LIBEVO.cria_cidades() 

# Creates cities with random coordinates and runs the evolutionary simulation using the parameters
# defined with set_parameters()
# This will set the data for cities and generations, which then can be copied using get_cities() and
# get_generations(), or freed using clear_data()
def run_simulation():
    # Run the simulation and get the result
    LIBEVO.realiza_simulacao()

# Returns a list containing the generations resulted from the simulation
def get_generations():
    result = LIBEVO.get_generations()

    # Get the result to a list of generations
    generations = [] 
    for i in range(NUM_GENERATIONS):
        individuals = [] # Each generation is an array of individuals
        for j in range(NUM_INDIVIDUALS):
            individual = [] # Each individual is represented by an array of integers (which represents a route between cities)
            for k in range(NUM_CITIES):
                individual.append(result[i][j][k])
            individuals.append(Individual(individual))
        generations.append(Generation(individuals))

    return generations

#Returns a list containing the cities used in the simulation
def get_cities():
    cities_struct = LIBEVO.get_city_coordinates().contents
    cities = []
    for index in range(NUM_CITIES):
        cities.append(City(cities_struct.x[index], cities_struct.y[index]))
    return cities


# Clears the data allocated by the C library, freeing memory
def clear_data():
    LIBEVO.limpa_memoria()


####################################################################################################
# UTILITIES FUNCTIONS (for debugging purposes)
####################################################################################################

# Prints the paths taken by each individual in each generation in an array of generations
def print_generations(generations):
    for index, generation in enumerate(generations):
        print('Generation #' + str(index) + ':\n' + str(generation))

# Prints the coordinates of each city in an array of cities
def print_cities(cities):
    for index, city in enumerate(cities):
        print('City #' + str(index) + ': ' + str(city))



####################################################################################################
# IF RUN AS THE MAIN PROGRAM (for debugging purposes)
####################################################################################################

if __name__ == '__main__':
    set_parameters()
    create_cities()
    run_simulation()
    generations = get_generations() 
    cities = get_cities()
    clear_data()
    
    print('GENERATIONS:')
    print_generations(generations)

    print('CITIES:')
    print_cities(cities)

    
