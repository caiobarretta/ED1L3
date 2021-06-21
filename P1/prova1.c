/****************************/
// NOME: CAIO AUGUSTO BARRETTA
// PRONTUÁRIO: CP300354X
/****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _aluno {
    int RA;
    char nome[64];
    float nota_final;
} Aluno;

/******** FUNÇÕES JÁ IMPLEMENTADAS ********/
Aluno *cria_aluno(int RA, const char *nome, float nota_final);
void destroi_aluno(Aluno **aluno_ref);
Aluno **cria_vetor_alunos(int n);
void destroi_vetor_alunos(Aluno ***vet_ref, int n);
void imprime_aluno(const Aluno *aluno);
void imprime_alunos(Aluno **vet, int n);
void imprime_aluno_maior_nota(Aluno **vet, int n);
/*****************************************/

/******** FUNÇÕES QUE VOCÊ DEVERÁ IMPLEMENTAR ********/
void adiciona_pontos_extras(Aluno **vet, int n, int indice_aluno, float pontos_extras);
Aluno *aluno_com_maior_nota(Aluno **vet, int n);
void inverte_alunos(Aluno **vet, int n);
/*****************************************************/


int main() {
    int n;
    scanf("%d", &n);

    Aluno **vet = cria_vetor_alunos(n);

    // lendo e armazenando os alunos no vetor
    for (int i = 0; i < n; i++) {
        int RA;
        char nome[64];
        float nota_final;
        scanf("%d %s %f", &RA, nome, &nota_final);
        vet[i] = cria_aluno(RA, nome, nota_final);
    }

    char comando[64];
    scanf("%s", comando);
    while (strcmp(comando, "para") != 0) {
        if (strcmp(comando, "adiciona_pontos_extras") == 0) {
            int indice_aluno;
            float pontos_extras;
            scanf("%d %f", &indice_aluno, &pontos_extras);
            adiciona_pontos_extras(vet, n, indice_aluno, pontos_extras);
        }
        else if (strcmp(comando, "inverte_alunos") == 0) {
            inverte_alunos(vet, n);
        }
        else if (strcmp(comando, "imprime_alunos") == 0) {
            imprime_alunos(vet, n);
        }
        else if (strcmp(comando, "imprime_aluno_maior_nota") == 0) {
            imprime_aluno_maior_nota(vet, n);
        }

        puts("");
        scanf("%s", comando);
    }

    destroi_vetor_alunos(&vet, n);


    return 0;
}



/*************** FUNÇÕES A SEREM IMPLEMENTADAS *****************/
// (a) Adiciona um valor de pontos extras (pontos_extras) para o aluno de índi-ce indice_aluno;
void adiciona_pontos_extras(Aluno **vet, int n, int indice_aluno, float pontos_extras) {
    // SUA IMPLEMENTACAO
    //Assuma que o vetor possui exatamente n alunos inseridos;
    //Se o índice for negativo, os pontos extras são adicionados para todos os alunos;
    if(indice_aluno <0){
        for (int i = 0; i < n; i++){
            vet[i]->nota_final += pontos_extras;
            //Os pontos extras também podem ser negativos;
            //A nota final mínima é 0.0 e a máxima é 10.0;
            if(vet[i]->nota_final > 10)
                vet[i]->nota_final = 10;
            else if(vet[i]->nota_final < 0)
                vet[i]->nota_final = 0;
        }
    }
    //Se o índice for inválido, não faça nada;
    else if(indice_aluno < n){
        //Adiciona um valor de pontos extras (pontos_extras) para o aluno de índice indice_aluno;
         vet[indice_aluno]->nota_final += pontos_extras;
         //Os pontos extras também podem ser negativos;
        //A nota final mínima é 0.0 e a máxima é 10.0;
         if(vet[indice_aluno]->nota_final > 10)
                vet[indice_aluno]->nota_final = 10;
            else if(vet[indice_aluno]->nota_final < 0)
                vet[indice_aluno]->nota_final = 0;
    }
}

// (b) Retorna uma cópia do aluno com a maior nota.
Aluno *aluno_com_maior_nota(Aluno **vet, int n) {
    //Assuma que o vetor possui exatamente n alunos inseridos;
    Aluno *aluno = NULL;
    float maior_nota = 0;
    int counter_maiores_notas = 0;
    for (int i = 0; i < n; i++){
        
        if(maior_nota < vet[i]->nota_final){
            aluno = vet[i];
            maior_nota = vet[i]->nota_final;
        }
    }
    for (int i = 0; i < n; i++){
        if(maior_nota == vet[i]->nota_final)
            counter_maiores_notas++;
    }

    //Em caso de empate, retorne o aluno com menor RA;
    if(counter_maiores_notas > 1){
         Aluno **vet_aux = cria_vetor_alunos(counter_maiores_notas);
         int counter_aux = 0;
         
         for (int i = 0; i < n; i++){
            if(maior_nota == vet[i]->nota_final){
            vet_aux[counter_aux] = cria_aluno(vet[i]->RA, vet[i]->nome, vet[i]->nota_final);
            counter_aux++;
            }
         }
        int menor_ra, min = 0;
        for (int i = 0; i < counter_maiores_notas; i++){
            min = i;
            for(int j = i+1; j < counter_maiores_notas; j++){
                if(vet_aux[j]->RA < vet_aux[min]->RA)
                    min = j;
            }
        }
        aluno = vet[min];
    }

    //Retorna uma cópia do aluno com a maior nota;
    return aluno;
}

// (c) Inverte o vetor de alunos
void inverte_alunos(Aluno **vet, int n) {

    int c = n-1;
    Aluno **vet_aux = cria_vetor_alunos(n);
    for (int i = 0; i < n; i++){
        vet_aux[i] = cria_aluno(vet[c]->RA, vet[c]->nome, vet[c]->nota_final);
        c--;
    }
    
    for (int i = 0; i < n; i++){
        vet[i]->RA = vet_aux[i]->RA;
        strcpy(vet[i]->nome, vet_aux[i]->nome);
        vet[i]->nota_final = vet_aux[i]->nota_final;
    }
}



/************ FUNÇÕES JÁ IMPLEMENTADAS *************/
Aluno *cria_aluno(int RA, const char *nome, float nota_final) {
    Aluno *aluno = (Aluno *) calloc(1, sizeof(Aluno));

    aluno->RA = RA;
    strcpy(aluno->nome, nome);
    aluno->nota_final = nota_final;

    return aluno;
}

void destroi_aluno(Aluno **aluno_ref) {
    if (aluno_ref != NULL) {
        free(*aluno_ref);
        *aluno_ref = NULL;
    }
}

Aluno **cria_vetor_alunos(int n) {
    return (Aluno**) calloc(n, sizeof(Aluno*));
}

void destroi_vetor_alunos(Aluno ***vet_ref, int n) {
    Aluno **vet = *vet_ref;
    
    for (int i = 0; i < n; i++) {
        destroi_aluno(&vet[i]);
    }
    free(vet);

    *vet_ref = NULL;
}

void imprime_aluno(const Aluno *aluno) {
    if (aluno == NULL) {
        printf("===> ERRO em `imprime_aluno`: aluno is NULL\n\n");
    }
    else {
        printf("%s (RA: %d): %.2f\n", aluno->nome, aluno->RA, aluno->nota_final);
    }
}

void imprime_alunos(Aluno **vet, int n) {
    puts("------------");
    printf("Quantidade de alunos: %d\n\n", n);
    for (int i = 0; i < n; i++) {
        printf("[%d] ", i);
        imprime_aluno(vet[i]);
    }
    puts("------------");
}

void imprime_aluno_maior_nota(Aluno **vet, int n) {
    Aluno *aluno = aluno_com_maior_nota(vet, n);

    puts("####");
    printf("- Aluno com a maior nota: ");
    imprime_aluno(aluno);
    puts("####");

    destroi_aluno(&aluno);
}
