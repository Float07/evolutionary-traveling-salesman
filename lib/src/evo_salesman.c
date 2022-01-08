extern struct generation* geracoes;
extern struct cities* cidades;

extern int NUM_CITIES;
extern int NUM_GENERATIONS;
extern int NUM_INDIVIDUOS;
extern float MUTATION_PROB;
extern float OLD_GENERATION_RATIO;
extern int MAP_SIZE;
extern int random_seed;

extern void gera_dados(void);
extern void limpa_dados(void);

void define_parametros(int num_cities, int num_generations, int num_individuos, float mutation_prob, float old_generation_ratio, int map_size, int rand_seed){
    NUM_CITIES = num_cities;
    NUM_GENERATIONS = num_generations;
    NUM_INDIVIDUOS = num_individuos;
    MUTATION_PROB = mutation_prob;
    OLD_GENERATION_RATIO = old_generation_ratio;
    MAP_SIZE = map_size;
    random_seed = rand_seed;
    return;
}

void realiza_simulacao(){
    gera_dados();
}

void limpa_memoria(){
    limpa_dados();
}

struct generation* get_generations(){
    return (int***) geracoes;
}

struct cities* get_city_coordinates(){
    return cidades;
}
