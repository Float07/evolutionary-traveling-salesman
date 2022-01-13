####################################################################################################
# IMPORTS
####################################################################################################
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

def plot_path(num_cities,cities,indice):
    path= np.arange(2*(num_cities+1)).reshape(2, num_cities+1)
    for index in range(num_cities):
        path[0][index]= cities[indice[index]].x
        path[1][index]= cities[indice[index]].y
    path[0][num_cities]= cities[indice[0]].x
    path[1][num_cities]= cities[indice[0]].y
    plt.plot( path[0], path[1], '-0')
    plt.show()

def plot_best_distance_per_generation(generations):
    best_distances = []
    x = list(range(len(generations) - 1))
    for generation in generations[1:]:
        best_distances.append(generation.individuals[0].total_distance)
    plt.ylim(best_distances[-1] - 0.02 * best_distances[-1], best_distances[0] + 0.02 * best_distances[0])
    plt.xlabel('Generation')
    plt.ylabel('Minimum Distance')
    plt.plot(x, best_distances)
