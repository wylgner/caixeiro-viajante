#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define TAM 1000


typedef struct{
    int n;
    int x;
    int y;

} Cidade;

typedef struct{
    Cidade individuo[TAM];
    float fitness;
}Populacao;

typedef struct{
    Populacao individuos[TAM];
    float mediaFitnes;
}Geracao;

int numeroDeCidades = 70;
int quantidadePopulacao = 100;
int quantidadeGeracao = 20;
float taxaDeMutacao = 0.20;
int numeroDeGeracoes = 10;
Populacao melhor ;
float mediaFitnesPopulacao[TAM];
int vetorDeControle[TAM];
int vetorDeControleCrossover[TAM];
Cidade cidades[TAM];
Cidade individuo[TAM];// teste
//Cidade populacao[TAM][TAM];
Populacao populacao[TAM];
Populacao filho1;
Populacao filho2;
void criar_cidade(){
    FILE *file = fopen("arquivosTeste/st70.txt","r");
    if(!(file == NULL)){
        for(int i = 0; i < numeroDeCidades; i++){
            fscanf(file,"%i %i %i\n", &cidades[i].n, &cidades[i].x, &cidades[i].y);
        }
    }
    else{
        printf("Arquivo nao encontrado!\n");
    }
}

void print_cidades(){
    printf("------------------------Cidades--------------------------\n");
    for(int i = 0; i < numeroDeCidades; i++){
    printf("%d - %d - %d\n", cidades[i].n, cidades[i].x, cidades[i].y);
    }
    printf("---------------------------------------------------------\n");
}
void print_individuo(){
     printf("------------------------Individuo-----------------------\n");
    for(int i = 0; i < numeroDeCidades; i++){
    printf("%d - %d - %d\n", individuo[i].n, individuo[i].x, individuo[i].y);
    }
    printf("---------------------------------------------------------\n");
}
void print_populacao(){
     printf("------------------------Populacao-----------------------\n");

    for(int i = 0; i < quantidadePopulacao; i++){
        for(int j = 0; j < numeroDeCidades; j ++){
            printf("%d - %d - %d\n", populacao[i].individuo[j].n, populacao[i].individuo[j].x, populacao[i].individuo[j].y);
        }
    printf("---------------------------------------------------------\n");
    }
    printf("---------------------------------------------------------\n");
}

int existe(int tam, int valor){
    for(int i = 0; i < sizeof vetorDeControle; i++){
        if(vetorDeControle[i] == valor)
            return 1;
    }
    return 0;
}
int existe_crossover(int tam, int valor){
    for(int i = 0; i < sizeof vetorDeControleCrossover; i++){
        if(vetorDeControleCrossover[i] == valor)
            return 1;
    }
    return 0;
}

void print_vetor(){
     for(int i =0; i < numeroDeCidades; i++){
     printf("\nVetor: %d ", vetorDeControle[i]);
    }
}

void cria_vetor_sem_repeticao(){
    srand(time(NULL));
    int v;
    for(int i = 0; i < numeroDeCidades -1; i++){
        v = rand() % numeroDeCidades;

        while((existe(i,v)==1)){

            v = rand() % numeroDeCidades;

        }
        vetorDeControle[i] = v;

    }


}

void embaralha_vetor(){
    srand(time(NULL));
    int v1=0, v2=0, aux=0;
    for(int i = 0; i < numeroDeCidades; i++){
        v1 = rand() % numeroDeCidades;
        v2 = rand() % numeroDeCidades;
        aux = vetorDeControle[v1];
        vetorDeControle[v1] = vetorDeControle[v2];
        vetorDeControle[v2] = aux;
    }
}

void cria_individuos(){
    for(int i = 0; i < numeroDeCidades; i++){
         individuo[i].n = cidades[vetorDeControle[i]].n;
       individuo[i].x = cidades[vetorDeControle[i]].x;
       individuo[i].y = cidades[vetorDeControle[i]].y;
    }
    print_individuo();
}

void calculaFitness(int posicao){
 Cidade c1, c2;
        float soma = 0;
        float hipot = 0;

        int i = 1;

        printf("---------------------------------------------------\n");
        for(int i = 0; i <= numeroDeCidades ; i++){
            c1 = populacao[posicao].individuo[i];
            if (i == numeroDeCidades) {
                c2 = populacao[0].individuo[0];
            } else {
                c2 = populacao[posicao].individuo[i+1];
            }
            float x1 = 0, y1 = 0;
            x1 = fabs(c1.x - c2.x);
            y1 = fabs(c1.y - c2.y);
            hipot = (x1 * x1) + (y1 * y1);
            soma += sqrt(hipot);

            printf("%d\n", c1.n);
            printf("%d\n", c2.n);
            printf("%.2f\n", soma);
        }
        populacao[posicao].fitness = soma;
        return 0;
}
void calculaFitnessCrossover(){
 Cidade c1, c2;
        float soma = 0;
        float hipot = 0;

        int i = 1;

        printf("---------------------------------------------------\n");
        for(int i = 0; i <= numeroDeCidades ; i++){
            c1 = filho1.individuo[i];
            if (i == numeroDeCidades) {
                c2 = filho1.individuo[0];
            } else {
                c2 = filho1.individuo[i+1];
            }
            float x1 = 0, y1 = 0;
            x1 = fabs(c1.x - c2.x);
            y1 = fabs(c1.y - c2.y);
            hipot = (x1 * x1) + (y1 * y1);
            soma += sqrt(hipot);

            printf("%d\n", c1.n);
            printf("%d\n", c2.n);
            printf("%.2f\n", soma);
        }
        filho1.fitness = soma;
        return 0;
}

print_fitness(){
     printf("------------------------Fitness-----------------------\n");

    for(int i = 0; i < quantidadePopulacao; i++){
       printf("Fitness: %.2f\n", populacao[i].fitness);
    printf("---------------------------------------------------------\n");
    }

}


void calculaMediaFitnessPopulacao(){
    int x=0;
    for(int i = 0; i < quantidadePopulacao; i++){
        x+= populacao[i].fitness;
    }

    x = x/quantidadePopulacao;


    mediaFitnesPopulacao[0]=x;

}


void print_individuo_crossover(){
     printf("------------------------Individuo Crossover 1-----------------------\n");
    for(int i = 0; i < numeroDeCidades; i++){
    printf("%d - %d - %d\n", filho1.individuo[i].n, filho1.individuo[i].x, filho1.individuo[i].y);
    }
    printf("---------------------------------------------------------\n");



}
int torneio(int i){
    int x1, x2;
    x1 = rand() % quantidadePopulacao;
    x2 = rand() % quantidadePopulacao;
    while(x1 == x2){
         x1 = rand() % quantidadePopulacao;
    }
    if(populacao[x1].fitness > populacao[x2].fitness)
        return x1;
    else
        return x2;
}
void crossover(){
     int pontoDec = numeroDeCidades / 2;
     Cidade aux;
        int x1, x2;
        int mutacao = 1 + (rand() % 100);
        for (int x = 0; x < quantidadePopulacao; x++) {
            x1 = torneio(x);
            if(x1 == quantidadePopulacao -1){
                x2 = x1 - 1 ;
            }
            else
            x2 = x1 +1 ;
            Populacao pai1 = populacao[x1];
            Populacao pai2 = populacao[x2];
            for (int i = 0; i < pontoDec; i++) {
                filho1.individuo[i] = pai1.individuo[i];
            }
            for (int j = pontoDec; j < numeroDeCidades; j++) {
               filho1.individuo[j] = pai2.individuo[j];

            }
            x1 = rand() % quantidadePopulacao;
             if(x1 == quantidadePopulacao -2){
                x2 = x1 - 2 ;
            }
            else
            x2 = x1 +2 ;
            if(!(mutacao >= taxaDeMutacao)){
                aux = filho1.individuo[x1];
                filho1.individuo[x1] =  filho1.individuo[x2];
                filho1.individuo[x2] = aux;
            }


        }

}

void melhorFitness(){
    melhor = populacao[0];
    for(int i = 0; i < quantidadePopulacao; i ++){
        if(populacao[i].fitness < melhor.fitness)
            melhor = populacao[i];
    }

}
int main(){

    printf("Numero de cidades:");
    scanf("%d", &numeroDeCidades);
    printf("Quantidade da populacao:");
    scanf("%d", &quantidadePopulacao);
    printf("Quantidade de geracoes: ");
    scanf("%d", &quantidadeGeracao);
    printf("Taxa de mutacao: ");
    scanf("%d", &taxaDeMutacao);
    //Criação de todas as cidades
    criar_cidade();
    print_cidades();
    //cria a população
    for(int i = 0; i < quantidadePopulacao; i++){
            if(i == 0)
            cria_vetor_sem_repeticao();
            else
                embaralha_vetor();
        cria_individuos();
        for(int j = 0; j < numeroDeCidades; j++){
            populacao[i].individuo[j].n = individuo[j].n;
            populacao[i].individuo[j].x = individuo[j].x;
            populacao[i].individuo[j].y = individuo[j].y;
        }
    }

    print_populacao();
    for(int i = 0; i < quantidadePopulacao; i++){
        calculaFitness(i);
    }
     melhorFitness();
    calculaMediaFitnessPopulacao();
    for(int i = 0; i < quantidadeGeracao; i++){
         crossover();
         print_individuo_crossover();
         for(int i = 0; i < quantidadePopulacao; i++){
         calculaFitnessCrossover();
        }
        if(filho1.fitness < melhor.fitness)
            melhor = filho1;
    }
    printf("melhor fitness: %f\n", melhor.fitness);




}
