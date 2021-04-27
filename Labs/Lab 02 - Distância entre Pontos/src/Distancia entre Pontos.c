#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void carregaVetorPonteiro(int qtd, int *vetor){
    for(int i=0; i<qtd; i++){
        scanf("%d", &vetor[i]);
    }
}

double calculaDistanciaEuclideana(int qtdPontos, int *p, int *q){
    double somaAoQuadrado = 0;
    for(int i=0; i<qtdPontos; i++){
        somaAoQuadrado +=  pow(q[i] - p[i], 2);
    }
    return sqrt(somaAoQuadrado);
}

int main(){
    int n;
    double d;
    scanf("%d", &n);
    if(n <= 0)
        return 0;

    int *p = NULL, *q = NULL;
    p = (int *)calloc(n, sizeof(int));
    carregaVetorPonteiro(n, p);

    q = (int *)calloc(n, sizeof(int));
    carregaVetorPonteiro(n, q);

    d = calculaDistanciaEuclideana(n, p, q);
    printf("A distancia Euclideana entre os pontos eh: %.2lf\n", d);

    free(p);
    p = NULL;
    free(q);
    q = NULL;

    return 0;
}