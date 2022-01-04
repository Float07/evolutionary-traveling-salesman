#include "evo_structs.h"
#include <stdlib.h>

const int NUM_GENERATIONS = 50;
const int random_seed = 1337;

typedef char bool;

// Gera numeros aleatorios como coordenadas x,y das cidades
void inicializa_cidades(struct cities* cidades){
    srand(random_seed);
    for(int i=0; i<NUM_CITIES; i++){
        cidades->x[i] = rand() % MAP_SIZE;
        cidades->y[i] = rand() % MAP_SIZE;
    }
    return;
}

// Cria uma rota aleatoria a partir de permutacoes da quantidade de cidades
void rota_aleatoria(struct route* rota){
    // Preenche o vetor com numeros de [0, NUM_CITIES)
    for(int i=0; i<NUM_CITIES; i++){
        rota->cities[i] = i;
    }
    // Realiza uma permutacao aleatoria dos valores
    for(int i=NUM_CITIES-1; i>0; i--){
        int aux, rand_idx;
        rand_idx = rand() % (i+1);
        aux = rota->cities[i];
        rota->cities[i] = rota->cities[rand_idx];
        rota->cities[rand_idx] = aux;
    }

    return;
}

// Combina dois individuos tomando a primeira metade como do primeiro individuo
// e a segunda metade com os valores que faltam na ordem do segundo
// Não é comutativa!
void combina_individuos(const struct route* src1, const struct route* src2, struct route* dst){
    // Set booleano com as cidades ja utilizadas
    bool utilizadas[NUM_CITIES] = {0};
    // Preenche primeira metade de src1
    for(int i = 0; i<(NUM_CITIES/2); i++){
        dst->cities[i] = src1->cities[i];
        utilizadas[dst->cities[i]] = 1;
    }
    // Preenche o resto com src2
    int pos = NUM_CITIES/2;
    for(int i = 0; i<NUM_CITIES; i++){
        if( ! utilizadas[ src2->cities[i] ] ){
            utilizadas[src2->cities[i]] = 1;
            dst->cities[pos] = src2->cities[i];
            pos++;
        }
    }
    return;
}

int main(){
    // Guarda espaco para individuos e cidades
    struct generation* geracoes = malloc(NUM_GENERATIONS*sizeof(struct generation));
    struct cities* cidades = malloc(sizeof(struct cities));
    if (geracoes == NULL || cidades == NULL) exit(-1);

    inicializa_cidades(cidades);

    // Cria geracao inicial
    for(int i = 0; i < NUM_INDIVIDUOS; i++){
        rota_aleatoria( &(geracoes[0].individuos[i]) );
    }

    // Loop de evolucao


    free(geracoes);
    free(cidades);
    geracoes = NULL;
    cidades = NULL;
    return 0;
}
