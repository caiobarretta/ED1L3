#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

struct data{
    int index;
    float notaMediaNaEscola; 
    float horasDeEstudosSemanais;
    int aprovado;
    float distanciaEuclideanaTreinoVsAmostra;
};

struct dadoFiltrado{
    int index;
    float d;
};

float calculaDistanciaEuclideana(float p1, float q1, float p2, float q2);

int classificacao(int qtdTreino, int k, struct data *dadosTreino, struct data dadosTeste);

void carregaAmostrasTreino(int qtd, struct data *dadosTreino);

void carregaAmostrasTeste(int qtd, struct data *dadosTeste);

int verificaSeIndexJaFoiFiltrado(int index, int qtdFiltrados, int *lstIndexFiltrados);

float retornaValorDistanciaEuclideanaPeloIndex(int qtd, struct data *dados, int index);

int RetornaIndexPorLista(int qtd, float valorComparacao, struct data *dados, int qtdFiltrados, int *lstIndexFiltrados);

int retornaAprovacaoPeloIndex(int qtd, struct data *dados, int index);

void Sort(int qtd, struct dadoFiltrado *dado);

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

float calculaDistanciaEuclideana(float p1, float q1, float p2, float q2){
    float somaAoQuadrado = 0;
    somaAoQuadrado =  pow(q1 - p1, 2) + pow(q2 - p2, 2);
    float resultado = sqrt(somaAoQuadrado);
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
    for(int i=0; i<qtd; i++){
        dadosTreino[i].index = i;
        scanf("%f %f %d", &dadosTreino[i].notaMediaNaEscola, &dadosTreino[i].horasDeEstudosSemanais, &dadosTreino[i].aprovado);
    }
}

void carregaAmostrasTeste(int qtd, struct data *dadosTeste){
    for(int i=0; i<qtd; i++){
        dadosTeste[i].index = i;
        scanf("%f %f", &dadosTeste[i].notaMediaNaEscola, &dadosTeste[i].horasDeEstudosSemanais);
    }
}

int classificacao(int qtdTreino, int k, struct data *dadosTreino, struct data dadoTeste){
    for(int i=0; i<qtdTreino; i++){
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
        //float d = calculaDistanciaEuclideanaListaDeVetores(qtdPontos, p, q);
        float d = calculaDistanciaEuclideana(p1, p2, q1, q2);

        //printf("p1: %.2f p2: %.2f q1: %.2f q2: %.2f d: %f\n", p1, p2, q1, q2, d);

        dadosTreino[i].distanciaEuclideanaTreinoVsAmostra = d;
    }
    
    int qtdFiltrados = 0;
    int *lstIndexFiltrados = (int *)calloc(k, sizeof(int));
    struct dadoFiltrado *filtrado = (struct dadoFiltrado*) calloc(k, sizeof(struct dadoFiltrado));

    float auxMenorValorDistanciaEuclideana = DBL_MAX;
    for(int i=0; i<k; i++){
        int index = RetornaIndexPorLista(qtdTreino, auxMenorValorDistanciaEuclideana, dadosTreino, qtdFiltrados, lstIndexFiltrados);
        auxMenorValorDistanciaEuclideana = retornaValorDistanciaEuclideanaPeloIndex(qtdTreino, dadosTreino, index);
        lstIndexFiltrados[i] = index;
        filtrado[i].index = index;
        filtrado[i].d =  auxMenorValorDistanciaEuclideana;
        qtdFiltrados++;
    }
    
    //for(int i=0; i<k; i++){
    //    printf("index: %d; d: %f\n", filtrado[i].index, filtrado[i].d);
    //}

    //bubble Sorting
    Sort(k, filtrado);
    //printf("\n-----------------------------SORT------------------------\n");
    //
    //for(int i=0; i<k; i++){
    //    printf("index: %d; d: %f\n", filtrado[i].index, filtrado[i].d);
    //}

    free(lstIndexFiltrados);
    lstIndexFiltrados = NULL;
    
    int quantidadeAprovado = 0;
    int quantidadeReprovado = 0;
    for(int i=0; i<k; i++){
        int aprovacao = retornaAprovacaoPeloIndex(qtdTreino, dadosTreino, filtrado[i].index);
        if(aprovacao == 1)
            quantidadeAprovado++;
        else
            quantidadeReprovado++;
    }

    free(filtrado);
    filtrado = NULL;
    

    if(quantidadeAprovado > quantidadeReprovado)
        return 1;
    return 0;
}

int verificaSeIndexJaFoiFiltrado(int index, int qtdFiltrados, int *lstIndexFiltrados){
    for(int i=0; i<qtdFiltrados; i++){
        if(index == lstIndexFiltrados[i])
            return 1;
    }
    return 0;
}

int RetornaIndexPorLista(int qtd, float valorComparacao, struct data *dados, int qtdFiltrados, int *lstIndexFiltrados){
    int index = 0;
    for(int i=0; i<qtd; i++){
        int foiFiltrado = verificaSeIndexJaFoiFiltrado(dados[i].index, qtdFiltrados, lstIndexFiltrados);
        if(foiFiltrado == 0){
            if(dados[i].distanciaEuclideanaTreinoVsAmostra < valorComparacao){
                index = dados[i].index;
                valorComparacao = dados[i].distanciaEuclideanaTreinoVsAmostra;
            }
        }
    }
    return index;
}

float retornaValorDistanciaEuclideanaPeloIndex(int qtd, struct data *dados, int index){
    for(int i=0; i<qtd; i++){
        if(dados[i].index == index)
            return dados[i].distanciaEuclideanaTreinoVsAmostra;
    }
    return 0;
}

int retornaAprovacaoPeloIndex(int qtd, struct data *dados, int index){
    for(int i=0; i<qtd; i++){
        if(dados[i].index == index)
            return dados[i].aprovado;
    }
    return -1;
}


void Sort(int qtd, struct dadoFiltrado *dado){
    //for(int i=0; i<qtd; i++){
    //    printf("index: %d; d: %f\n", dado[i].index, dado[i].d);
    //}
//
    //printf("\n-----------------------------sort-----------------------------\n");
    for (int i = 0; i < qtd; i++){
        for (int j = 0; j < qtd -i; j++){
            if(dado[j].d < dado[j+1].d){
                //Troca
                int index = dado[j].index;
                float d = dado[j].d;

                dado[j] = dado[j+1];

                dado[j+1].index = index;
                dado[j+1].d = d;
            
            }
        }
    }
    int j = (qtd-1);
    for (int i = 0; i < qtd; i++){
        //Troca
        int index = dado[i].index;
        float d = dado[i].d;

        dado[i] = dado[j];

        dado[j].index = index;
        dado[j].d = d;
        j--;
    }

    //for(int i=0; i<qtd; i++){
    //    printf("index: %d; d: %f\n", dado[i].index, dado[i].d);
    //}
//
    //printf("\n\n");

}