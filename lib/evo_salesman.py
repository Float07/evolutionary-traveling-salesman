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
        str = ''
        for city in self.route:
            str += str(city) + ' '
        return str.rstrip()


# A generation is defined by an array of individuals
class Generation:
    def __init__(self, individuals) -> None:
        self.individuals = individuals

    def __str__(self) -> str:
        str = ''
        for index, individual in enumerate(self.individuals):
            str += 'Individual #' + str(index) + ': ' + str(individual) + '\n'
        return str

# Child class that interfaces with the C struct "cities"
class CitiesStruct(ctypes.Structure):
    _fields_ = [('x', POINTER(ctypes.c_int)),
                ('y', POINTER(ctypes.c_int))]

# A city is defined by its x and y coordinates
class City:
    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y



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



####################################################################################################
# WRAPPER FUNCTIONS
####################################################################################################

# Creates a random set of cities and runs the evolutionary algorithm
# Returns an array of generations
def run_simulation():
    # Run the simulation and get the result
    LIBEVO.realiza_simulacao()
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


# Clears the data allocated by the C program
def clear_data():
    LIBEVO.limpa_memoria()


####################################################################################################
# UTILITIES FUNCTIONS
####################################################################################################


