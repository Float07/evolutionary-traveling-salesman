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

def plot_route(cities,route):
    num_cities = len(route)
    plot_route = np.arange(2*(num_cities+1)).reshape(2, num_cities+1)
    for index in range(num_cities):
        plot_route[0][index] = cities[route[index]].x
        plot_route[1][index] = cities[route[index]].y
    plot_route[0][num_cities] = cities[route[0]].x
    plot_route[1][num_cities] = cities[route[0]].y
    plt.plot( plot_route[0], plot_route[1], '-o')
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
