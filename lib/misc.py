####################################################################################################
# IMPORTS
####################################################################################################
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

####################################################################################################
# MISC FUNCTIONS
####################################################################################################
def plot_cities(cities, map_size):
    num_cities = len(cities)
    arr=np.arange(2*num_cities).reshape(2, num_cities)
    for index in range(num_cities):
        arr[0][index]= cities[index].x
        arr[1][index]= cities[index].y
    
    plt.plot(arr[0],arr[1], 'ro')
    plt.axis([0, map_size, 0,map_size])
    plt.show()

def plot_best_distance_per_generation(generations):
    best_distances = []
    x = list(range(len(generations)))
    for generation in generations:
        generation_distances = []
        for individual in generation.individuals:
            generation_distances.append(individual.total_distance)
        best_distances.append(min(generation_distances))
    plt.bar(x, best_distances)
