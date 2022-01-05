#include <stdlib.h>
#include <math.h>
#include <string.h>

int NUM_CITIES = 10;                // quantidade de cidades (tamanho do problema)
int NUM_GENERATIONS = 50;           // numero de geracoes utilizadas
int NUM_INDIVIDUOS = 50;            // individuos em cada geracao
float MUTATION_PROB = 0.01f;        // probabilidade de mutacao
float OLD_GENERATION_RATIO = 0.5f;  // fracao da ultima geracao preservada
int MAP_SIZE = 100;                 // tamanho do espaco para colocar cidades
int random_seed = 1337;             // semente de numeros aleatorios

// Variaveis globais com os resultados
struct generation* geracoes = NULL;
struct cities* cidades = NULL;

typedef char bool;

// A cidade sao cordenadas x,y da posicao no espaco
struct cities{
    int* x;
    int* y;
};

// A rota sao indices das cidades em ordem de atravessamento
struct route{
    int *cities;
};

// Cada individuo eh uma rota, a geracao eh um conjunto de rotas
struct generation{
   struct route* individuos;
};

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
    bool *utilizadas;
    utilizadas = calloc(NUM_CITIES, sizeof(bool));
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
    free(utilizadas);
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

int compara_distancias (const void* arg1, const void* arg2){
    const struct distancia_individuo* p1 = (struct distancia_individuo*)arg1;
    const struct distancia_individuo* p2 = (struct distancia_individuo*)arg2;
    if ( p1->distancia >   p2->distancia ) return 1;
    if ( p1->distancia ==  p2->distancia ) return 0;
    return -1;
}

void limpa_dados(){
    if(geracoes == NULL) return;
    free(geracoes[0].individuos[0].cities);
    free(geracoes[0].individuos);
    free(geracoes);
    free(cidades->x);
    free(cidades);
    geracoes = NULL;
    cidades = NULL;
    return;
}

void aloca_memoria(){
    // Limpa memoria se tiver sido usado antes
    limpa_dados();

    // Guarda espaco para individuos e cidades
    geracoes = malloc(NUM_GENERATIONS*sizeof(struct generation));
    cidades = malloc(sizeof(struct cities));
    if (geracoes == NULL || cidades == NULL) exit(-1);

    // Inicializa vetores do geracoes
    geracoes[0].individuos = malloc(NUM_GENERATIONS*NUM_INDIVIDUOS*sizeof(struct route));
    if(geracoes[0].individuos == NULL) exit(-1);
    for(int i = 0; i < NUM_GENERATIONS; i++){
        geracoes[i].individuos = geracoes[0].individuos + i*NUM_INDIVIDUOS;
    }

    // Inicializa vetores de cada individuo
    geracoes[0].individuos[0].cities = malloc(NUM_GENERATIONS*NUM_INDIVIDUOS*NUM_CITIES*sizeof(int));
    if(geracoes[0].individuos[0].cities == NULL) exit(-1);
    for(int i = 0; i < NUM_GENERATIONS; i++){
        for(int j = 0; j < NUM_INDIVIDUOS; j++){
        geracoes[i].individuos[j].cities = geracoes[0].individuos[0].cities + (i*NUM_INDIVIDUOS+j)*NUM_CITIES;
        }
    }

    // Inicializa vetores da cidade
    cidades->x = malloc(2*NUM_CITIES*sizeof(int));
    if(cidades->x == NULL) exit(-1);
    cidades->y = cidades->x + NUM_CITIES;

    return;
}

void gera_dados(){

    aloca_memoria();
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
    return;
}
