#include <stdio.h>
#include <stdlib.h>     /* atoi */
#include <pthread.h>

/* This data is shared by the thread (s) */
/* The thread will begin control in this function */

int matrixA[10][10];
int matrixB[10][10];

int matrixC[10][10];

int M, K, N;

struct XY{
    int x;
    int y;
};

void *runner(void *param){

    int i = ((struct XY*) param) -> x;
	int j = ((struct XY*) param) -> y;
    //printf(" i = %d\nj = %d\n", i, j);
    int sum = 0;
        
    for (int k = 0; k < K; k++) {
        sum = sum + matrixA[i][k] * matrixB[k][j];
    }
    matrixC[i][j] = sum;

    pthread_exit(0);

}

 /* the thread */
int main(int argc, char *argv[]) {

    

    

    

    // read file
    FILE *file;
    file = fopen("data.txt", "r");
    if (file) {
        fscanf(file, "%d", &M);
        fscanf(file, "%d", &K);
        fscanf(file, "%d", &N);

        printf("M = %d\nK = %d\nN = %d\n", M, K, N);

    
        int tmp;
        //Read file in matrix A
        for(int i = 0; i < M; i++){
            for(int k = 0; k < K; k++){
                fscanf(file, "%d", &matrixA[i][k]);
            }
        }
        //Read file in matrix B
        for(int i = 0; i < K; i++){
            for(int k = 0; k < N; k++){
                fscanf(file, "%d", &matrixB[i][k]);
            }
        }
        //Print matrix A
        printf("\nMatrix A:\n");

        for(int i = 0; i < M; i++){
            for(int k = 0; k < K; k++){
                printf("%d ", matrixA[i][k]);
            }
            printf("\n");
        }
        printf("\nMatrix B:\n");

        //Print matrix B
        for(int i = 0; i < K; i++){
            for(int k = 0; k < N; k++){
                printf("%d ", matrixB[i][k]);
            }
            printf("\n");
        }

    }else{
        printf("Error file\n");
    }

    int sum;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
        // sum = 0;
        
        //     for (int k = 0; k < K; k++) {
        //         sum = sum + matrixA[i][k] * matrixB[k][j];
        //     }
        //     matrixC[i][j] = sum;
            struct XY *xy = (struct XY*)malloc(sizeof(struct  XY));
            xy -> x = i;
            xy -> y = j;

            pthread_t tid; /* the thread id */
            pthread_attr_t attr; /* set of thread attributes */
            
            /* get the default attributes */
            pthread_attr_init(&attr);
            /* create the thread */
            pthread_create(&tid, &attr, runner, (void*)xy);
            /* wait for the thread to exit */
            pthread_join(tid, NULL);
        }
    }

    //Print matrix C
    printf("\n");

    for(int i = 0; i < M; i++){
        for(int k = 0; k < N; k++){
               printf("%d ", matrixC[i][k]);
        }
        printf("\n");
    }




    
}
