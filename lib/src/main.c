#include "evo_structs.h"
#include <stdlib.h>

const int NUM_GENERATIONS = 50;
const int random_seed = 1337;

int main(){
    // Guarda espaco para individuos e cidades
    struct generation* geracoes = malloc(NUM_GENERATIONS*sizeof(struct generation));
    struct cities* cidades = malloc(sizeof(struct cities));

    // Inicializa cidades
    srand(random_seed);
    for(int i=0; i<NUM_CITIES; i++){
        cidades->x[i] = rand() % MAP_SIZE;
        cidades->y[i] = rand() % MAP_SIZE;
    }

    // Cria geracao inicial
    

    // Loop de evolucao


    free(geracoes);
    free(cidades);
    geracoes = NULL;
    cidades = NULL;
    return 0;
}
