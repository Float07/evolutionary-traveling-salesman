#include "evo_structs.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

const int NUM_GENERATIONS = 50;
const int random_seed = 1337;
const float OLD_GENERATION_RATIO = 0.5f;
const float MUTATION_PROB = 0.01f;

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

float distancia_total(const struct route* rota, const struct cities* cidades){
    float distance = 0;

    int x0, y0, x1, y1;
    x1 = cidades->x[0];
    y1 = cidades->y[0];
    for(int i = 1; i < NUM_CITIES; i++){
        x0 = x1;
        y0 = y1;
        x1 = cidades->x[rota->cities[i]];
        y1 = cidades->y[rota->cities[i]];
        distance += sqrt( (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) );
    }

    return distance;
}

struct distancia_individuo{
    float distancia;
    int individuo;
};

int compara_distancias (const struct distancia_individuo* p1, const struct distancia_individuo* p2){
    if ( p1->distancia >   p2->distancia ) return 1;
    if ( p1->distancia ==  p2->distancia ) return 0;
    return -1;
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

    // Calcula distancias e ordena
    struct distancia_individuo distancias[NUM_INDIVIDUOS];
    for(int i = 0; i < NUM_INDIVIDUOS; i++){
        distancias[i].distancia = distancia_total(&geracoes[0].individuos[i], cidades);
        distancias[i].individuo = i;
    }
    qsort(distancias, NUM_INDIVIDUOS, sizeof(struct distancia_individuo), compara_distancias);

    // Loop de evolucao
    const int NUM_PRESERVADOS = ceil(NUM_INDIVIDUOS*OLD_GENERATION_RATIO);
    // Para toda Geracao
    for(int i = 1; i < NUM_GENERATIONS; i++){
        // Copia os NUM_PRESERVADOS com menor distancia para a nova geracao
        for(int j = 0; j < NUM_PRESERVADOS; j++){
            struct route *src, *dst;
            src = &geracoes[i-1].individuos[distancias[j].individuo];
            dst = &geracoes[i].individuos[j];
            memcpy(dst, src, sizeof(struct route));
        }
        // Cria novos individuos com base nos copiados
        for(int j = NUM_PRESERVADOS; j < NUM_INDIVIDUOS; j++){
            struct route *p1, *p2, *dst;
            p1  = &geracoes[i].individuos[rand()%NUM_PRESERVADOS];
            p2  = &geracoes[i].individuos[rand()%NUM_PRESERVADOS];
            dst = &geracoes[i].individuos[j];
            combina_individuos(p1,p2,dst);
        }
        // Ordena a nova geracao de acordo com a menor distancia
        for(int j = 0; j < NUM_INDIVIDUOS; j++){
        distancias[j].distancia = distancia_total(&geracoes[i].individuos[j], cidades);
        distancias[j].individuo = j;
        }
        qsort(distancias, NUM_INDIVIDUOS, sizeof(struct distancia_individuo), compara_distancias);
    }

    free(geracoes);
    free(cidades);
    geracoes = NULL;
    cidades = NULL;
    return 0;
}
