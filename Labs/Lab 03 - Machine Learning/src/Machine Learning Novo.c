#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

struct data{
    float notaMediaNaEscola; 
    float horasDeEstudosSemanais;
    int aprovado;
};

struct dadoResumido{
    int index;
    int value;
    double dist;
};

double calculaDistanciaEuclideana(float p1, float q1, float p2, float q2);

void carregaAmostrasTreino(int qtd, struct data *dadosTreino);

void carregaAmostrasTeste(int qtd, struct data *dadosTeste);

int classificacao(int qtdTreino, int k, struct data *dadosTreino, struct data dadosTeste);

void sortDadoResumido(int qtd, struct dadoResumido *dado);

float calculaDistanciaEuclideanaListaDeVetores(int qtdPontos, float *p, float *q);

int main(){
    //A primeira linha corresponderá a 3 valores: o número de amostras de treinamento m,
    // o númerode amostras de teste n a serem classificadas eo valor de k.
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    if(n <= 0 || n ==0 || k == 0)
        return 0;

    if(k > m)// valor de k tem que ser menor ou igual ao de m, para não quebrar o filtro
        k = m;

    struct data *dadosTreino = (struct data*)calloc(m, sizeof(struct data));
    carregaAmostrasTreino(m, dadosTreino);

    struct data *dadosTeste = (struct data*)calloc(m, sizeof(struct data));
    carregaAmostrasTeste(n, dadosTeste);

    for(int i=0; i<n; i++){
        int resultado = classificacao(m, k, dadosTreino, dadosTeste[i]);
        if(resultado > 0)
            printf("Aluno %d: (%.2f, %.2f) = Aprovado\n", i, dadosTeste[i].notaMediaNaEscola, dadosTeste[i].horasDeEstudosSemanais);
        else
            printf("Aluno %d: (%.2f, %.2f) = Reprovado\n", i, dadosTeste[i].notaMediaNaEscola, dadosTeste[i].horasDeEstudosSemanais);
    }

    free(dadosTreino);
    dadosTreino = NULL;
    
    free(dadosTeste);
    dadosTeste = NULL;

    return 0;
}

double calculaDistanciaEuclideana(float p1, float q1, float p2, float q2){
    double somaAoQuadrado = 0;
    somaAoQuadrado =  pow(q1 - p1, 2) + pow(q2 - p2, 2);
    double resultado = sqrt(somaAoQuadrado);
    return resultado;
}

float calculaDistanciaEuclideanaListaDeVetores(int qtdPontos, float *p, float *q){
    float somaAoQuadrado = 0;
    for(int i=0; i<qtdPontos; i++){
        somaAoQuadrado +=  pow(q[i] - p[i], 2);
    }
    return sqrt(somaAoQuadrado);
}

void carregaAmostrasTreino(int qtd, struct data *dadosTreino){
    float notaMediaNaEscola = 0, horasDeEstudosSemanais = 0;
    int aprovado = 0;
    for(int i=0; i<qtd; i++){
        scanf("%f %f %d", &notaMediaNaEscola, &horasDeEstudosSemanais, &aprovado);
        dadosTreino[i].notaMediaNaEscola = notaMediaNaEscola;
        dadosTreino[i].horasDeEstudosSemanais = horasDeEstudosSemanais;
        dadosTreino[i].aprovado = aprovado;
    }
}

void carregaAmostrasTeste(int qtd, struct data *dadosTeste){
    float notaMediaNaEscola = 0, horasDeEstudosSemanais = 0;
    for(int i=0; i<qtd; i++){
        scanf("%f %f",&notaMediaNaEscola, &horasDeEstudosSemanais);
         dadosTeste[i].notaMediaNaEscola = notaMediaNaEscola; 
         dadosTeste[i].horasDeEstudosSemanais = horasDeEstudosSemanais;
    }
}

int classificacao(int qtdTreino, int k, struct data *dadosTreino, struct data dadoTeste){

    struct dadoResumido *vet = (struct dadoResumido*) calloc(qtdTreino, sizeof(struct dadoResumido));
    struct dadoResumido *vetK = (struct dadoResumido*) calloc(k, sizeof(struct dadoResumido));
    for(int i=0; i<qtdTreino; i++){
        vet[i].index = i;
        float p1 = dadosTreino[i].notaMediaNaEscola;
        float p2 = dadoTeste.notaMediaNaEscola;
        
        float q1 = dadosTreino[i].horasDeEstudosSemanais;
        float q2 = dadoTeste.horasDeEstudosSemanais;

        int qtdPontos = 2;
        float *p = (float *)calloc(qtdPontos, sizeof(float));
        p[0] = p1; 
        p[1] = p2;
        
        float *q = (float *)calloc(qtdPontos, sizeof(float));
        q[0] = q1;
        q[1] = q2;

        float d = calculaDistanciaEuclideana(p1, p2, q1, q2);
        vet[i].dist = d;
        vet[i].value = dadosTreino[i].aprovado;
    }

    //printf("antes:\n");
    //for(int i=0; i<qtdTreino; i++){
    //    printf("d: %f j: %d \n", vet[i].dist, vet[i].index);
    //}

    sortDadoResumido(qtdTreino, vet);

    //printf("depois:\n");
    //for(int i=0; i<qtdTreino; i++){
    //    printf("d: %f j: %d \n", vet[i].dist, vet[i].index);
    //}

    for(int i=0; i<k; i++){
        vetK[i].index = vet[i].index;
        vetK[i].dist = vet[i].dist;
        vetK[i].value = vet[i].value;
    }
    free(vet);
    vet = NULL;
    //printf("com k:\n");
    //for(int i=0; i<k; i++){
    //    printf("d: %f j: %d \n", vetK[i].dist, vetK[i].index);
    //}

    //printf("value k:\n");
    int qtdAprovada, qtdReprovada = 0;
    for(int i=0; i<k; i++){
        //printf("v: %d j: %d \n", vetK[i].value, vetK[i].index);
        if(vetK[i].value == 1){
            qtdAprovada++;
        }
        else{
            qtdReprovada++;
        }
    }

    free(vetK);
    vetK = NULL;
    if(qtdAprovada > qtdReprovada)
        return 1;
    if(qtdAprovada == qtdReprovada)
        return -1;
    return 0;
}

void sortDadoResumido(int qtd, struct dadoResumido *v){
   
    int auxIndex, auxValue, min = 0;
    double auxDist = 0;
    for (int i = 0; i < qtd; i++){
        min = i;
        for(int j = i+1; j < qtd; j++){
            if(v[j].dist < v[min].dist)
                min = j;
        }
        auxIndex = v[i].index;
        auxDist = v[i].dist;
        auxValue = v[i].value;
        

        v[i].index = v[min].index;
        v[i].dist = v[min].dist;
        v[i].value = v[min].value;

        v[min].index = auxIndex;
        v[min].dist = auxDist;
        v[min].value = auxValue;
    }
}