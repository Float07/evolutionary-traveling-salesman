####################################################################################################
# MISC FUNCTIONS
####################################################################################################
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

def cidades(map_size,num_cities,cities):
    arr=np.arange(2*num_cities).reshape(2, num_cities)
    for index in range(num_cities):
        arr[0][index]= cities[index].x
        arr[1][index]= cities[index].y
    
    plt.plot(arr[0],arr[1], 'ro')
    plt.axis([0, map_size, 0,map_size])
    plt.show()

