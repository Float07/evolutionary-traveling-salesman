extern struct generation* geracoes;
extern struct cities* cidades;

void gera_dados(void);
void limpa_dados(void);

void realiza_simulacao(){
    gera_dados();
}

void limpa_memoria(){
    limpa_dados();
}

struct generation* get_simulation(){
    return geracoes;
}

struct cities* get_city_coordinates(){
    return cidades;
}

int* test_simulation(){
    return (int*) geracoes;
}

int*** test_simulation3d(){
    return (int***) geracoes;
}

int* test_cities(){
    return (int*) cidades;
}

int** test_cities2d(){
    return (int**) cidades;
}
