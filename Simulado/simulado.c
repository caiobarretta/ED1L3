/****************************/
// NOME: Caio Augusto Barretta
// PRONTUÁRIO: CP-300354x
/****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct _vetor {
    int capacidade;
    int tamanho;
    float *data;
} Vetor;

/******** FUNÇÕES JÁ IMPLEMENTADAS ********/
Vetor *cria_vetor(int capacidade);
void destroi_vetor(Vetor **vet_ref);
void imprime_notas(const Vetor *vet_notas);
void imprime_media_turma(const Vetor *vet_notas);
void imprime_desvio_padrao_turma(const Vetor *vet_notas);
/*****************************************/

/******** FUNÇÕES QUE VOCÊ DEVERÁ IMPLEMENTAR ********/
void adiciona_nota(Vetor *vet_notas, float nota);
void adiciona_pontos_extras(Vetor *vet_notas, int indice_aluno,
                            float pontos_extras);
float nota_media_turma(const Vetor *vet_notas);
float desvio_padrao_turma(const Vetor *vet_notas);
/*****************************************************/




int main() {
    int capacidade;
    char comando[64];

    scanf("%d", &capacidade);
    Vetor *vet_notas = cria_vetor(capacidade);

    scanf("%s", comando);
    
    while (strcmp(comando, "para") != 0) {
        if (strcmp(comando, "adiciona_nota") == 0) {
            float nota;
            scanf("%f", &nota);
            adiciona_nota(vet_notas, nota);
        }
        else if (strcmp(comando, "adiciona_pontos_extras") == 0) {
            int indice_aluno;
            float pontos_extras;
            scanf("%d %f", &indice_aluno, &pontos_extras);
            adiciona_pontos_extras(vet_notas, indice_aluno, pontos_extras);
        }
        else if (strcmp(comando, "imprime_notas") == 0) {
            imprime_notas(vet_notas);
        }
        else if (strcmp(comando, "imprime_media_turma") == 0) {
            imprime_media_turma(vet_notas);
        }
        else if (strcmp(comando, "imprime_desvio_padrao_turma") == 0) {
            imprime_desvio_padrao_turma(vet_notas);
        }

        scanf("%s", comando);
    }

    destroi_vetor(&vet_notas);

    return 0;
}
////////////////////////////////////


/*************** FUNÇÕES A SEREM IMPLEMENTADAS *****************/
// (a) Adiciona uma nova nota no final do vetor. Caso o vetor esteja cheio, não faça nada.
void adiciona_nota(Vetor *vet_notas, float nota) {
    // SUA IMPLEMENTAÇÃO
    //Se a nota não estiver no intervalo [0, 10], não faça nada.
    if(nota < 0.0 || nota >10.0)
        return;
    //Caso o vetor esteja cheio, não faça nada.
    if(vet_notas->tamanho >= vet_notas->capacidade)
        return;
    //Adiciona a nota NOTA no final do vetor.
    vet_notas->data[vet_notas->tamanho] = nota;
    vet_notas->tamanho++;
}

// (b) Adiciona um valor de pontos extras (pontos_extras) para o aluno de índice indice_aluno.
void adiciona_pontos_extras(Vetor *vet_notas, int indice_aluno,
                            float pontos_extras) {
    // SUA IMPLEMENTAÇÃO
    if(indice_aluno <0){
        //Caso o índice passado seja menor que zero, os pontos extras são adicio-nados para todos os alunos.
        for (int i = 0; i < vet_notas->tamanho; i++){
            //Adiciona  um valor de pontos extras (pontos_extras) para o aluno de índiceindice_aluno. 
        vet_notas->data[i] += pontos_extras;
            if(vet_notas->data[i] > 10.0){
                //A nota final máxima é 10.0.
                vet_notas->data[i] = 10;
            }
        }
        
    }
    else if(indice_aluno < vet_notas->tamanho){
        //Adiciona  um valor de pontos extras (pontos_extras) para o aluno de índiceindice_aluno. 
        vet_notas->data[indice_aluno] += pontos_extras;
        if(vet_notas->data[indice_aluno] > 10.0){
            //A nota final máxima é 10.0.
            vet_notas->data[indice_aluno] = 10;
        }
    }
    
    
    
    
}

// (c) Retorna a nota média da turma.
float nota_media_turma(const Vetor *vet_notas) {
    // SUA IMPLEMENTAÇÃO
    float soma = 0;
    for (int i = 0; i < vet_notas->tamanho; i++){
        soma += vet_notas->data[i];
    }
    return soma/vet_notas->tamanho;
}


// (d) Retorna o desvio padrão das notas da turma.
float desvio_padrao_turma(const Vetor *vet_notas) {
    // SUA IMPLEMENTAÇÃO
    float soma = 0, variancia=0, desvio_padrao =0;
    float x = nota_media_turma(vet_notas);
    for (int i = 0; i < vet_notas->tamanho; i++){
        soma += pow(vet_notas->data[i] - x, 2);
    }

    variancia = soma/vet_notas->tamanho;
    desvio_padrao = sqrt(variancia);
    return desvio_padrao;
}




/************ FUNÇÕES JÁ IMPLEMENTADAS *************/
Vetor *cria_vetor(int capacidade) {
    Vetor *vet = (Vetor *) calloc(1, sizeof(Vetor));
    vet->tamanho = 0;
    vet->capacidade = capacidade;
    vet->data = (float *) calloc(capacidade, sizeof(float));

    return vet;
}


void destroi_vetor(Vetor **vet_ref) {
    Vetor *vet = *vet_ref;
    free(vet->data);
    free(vet);
    *vet_ref = NULL;
}

void imprime_notas(const Vetor *vet_notas) {
    puts("----");
    printf("Quantidade de Alunos: %d\n\n", vet_notas->tamanho);
    for (int i = 0; i < vet_notas->tamanho; i++) {
        printf("- Aluno %d - nota: %.2f\n", i, vet_notas->data[i]);
    }
    puts("----\n");
}

void imprime_media_turma(const Vetor *vet_notas) {
    float nota_media = nota_media_turma(vet_notas);

    puts("****");
    printf("A nota média da turma é: %.2f\n", nota_media);
    puts("****\n");
}

void imprime_desvio_padrao_turma(const Vetor *vet_notas) {
    float desvio_padrao = desvio_padrao_turma(vet_notas);

    puts("####");
    printf("O desvio padrão das notas da turma é: %.2f\n", desvio_padrao);
    puts("####\n");
}
