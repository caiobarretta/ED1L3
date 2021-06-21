    #include<stdio.h>
    
    int main(void)
    {
      float v[5] = {7, 8, 9.5, 9.9, 5.2};
      // declarando e inicializando o vetor notas
      
        if(v == &v)
         printf("a ok \n\n");
        if(*v == v[0])
        printf("b ok \n\n");
        if(&v==&v[0])
        printf("c ok \n\n");
        //if(*(v+1)==&v[1])
        //printf("d ok \n\n");

      return 0;
    }