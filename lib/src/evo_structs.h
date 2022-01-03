#ifndef __EVO_STRUCTS_H
#define __EVO_STRUCTS_H

#define NUM_CITIES     10
#define NUM_INDIVIDUOS 50
#define MAP_SIZE 100 // tamanho do espaco para colocar cidades

// A cidade sao cordenadas x,y da posicao no espaco
struct cities{
    int x[NUM_CITIES];
    int y[NUM_CITIES];
};

// A rota sao indices das cidades em ordem de atravessamento
struct route{
    int cities[NUM_CITIES];
};

// Cada individuo eh uma rota, a geracao eh um conjunto de rotas
struct generation{
   struct route individuos[NUM_INDIVIDUOS];
};

#endif
