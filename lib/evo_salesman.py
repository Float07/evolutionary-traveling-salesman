####################################################################################################
# IMPORTS
####################################################################################################

import ctypes
from ctypes import POINTER
import pathlib



####################################################################################################
# CLASSES DEFINITIONS
####################################################################################################

# An individual is defined by a route between the cities
# And a route is an array of integers that indicates in which order the individual went through the cities
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


# A generation is defined by an array of individuals
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

# A city is defined by its x and y coordinates
class City:
    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y
    
    def __str__(self) -> str:
        return '(x,y) = (' + str(self.x) + ',' + str(self.y) + ')'



####################################################################################################
# GLOBAL VARIABLES
####################################################################################################
NUM_CITIES = 10
NUM_GENERATIONS = 50
NUM_INDIVIDUALS = 50

# Load the C library
LIBEVO = ctypes.CDLL(str(pathlib.Path(__file__).parent.resolve()) + "/src/libevo.so")
# Set the return type as a 3d int array
LIBEVO.test_simulation3d.restype = POINTER(POINTER(POINTER(ctypes.c_int)))
# Set the return type as a pointer to CitiesSctruct
LIBEVO.get_city_coordinates.restype = POINTER(CitiesStruct)
# Set the return type as void
LIBEVO.limpa_memoria.restype = None



####################################################################################################
# WRAPPER FUNCTIONS
####################################################################################################

# Creates cities with random coordinates and runs the evolutionary algorithm
# This will set the data for cities and generations, which then can be copied using get_cities() and
# get_generations(), or freed using clear_data()
def run_simulation():
    # Run the simulation and get the result
    LIBEVO.realiza_simulacao()

# Gets the generations resulted from the simulation
# Returns an array of generations
def get_generations():
    result = LIBEVO.test_simulation3d()

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

#Returns an array containing the cities used in the simulation
def get_cities():
    cities_struct = LIBEVO.get_city_coordinates().contents
    cities = []
    for index in range(NUM_CITIES):
        cities.append(City(cities_struct.x[index], cities_struct.y[index]))
    return cities


# Clears the data allocated by the C program (e.g. cities and generations), freeing memory
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
    run_simulation()
    generations = get_generations() 
    cities = get_cities()
    clear_data()
    
    print('GENERATIONS:')
    print_generations(generations)

    print('CITIES:')
    print_cities(cities)

    
