#include "funcoesEp1.h"

int main() {
    int *bin, *a, *b, *c;
    int *assert, *circular;
    int **subChaves = NULL, *chaveK;
    int i, alpha;

    /*Conferindo hexaParaBinario
    */
    printf("Conferindo hexaParaBinario\n");
    bin = malloc(8 * sizeof(int));
    assert = malloc(8 * sizeof(int));
    assert[0] = 1;
    assert[1] = 0;
    assert[2] = 0;
    assert[3] = 0;
    assert[4] = 0;
    assert[5] = 0;
    assert[6] = 0;
    assert[7] = 0;

    bin = hexaParaBinario("01");
    for(i = 0; i < 8; i++) {
        if (bin[i] - assert[i] != 0) {
            printf("Erro em hexaParaBinario!\n");
        }
    }
    printf("-------------------------------------\n");
    /*Conferindo somaBinario64
    */
    printf("Conferindo somaBinario64\n");
    a = malloc(8 * sizeof(int));
    b = malloc(8 * sizeof(int));
    c = malloc(8 * sizeof(int));    
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    a[4] = 0;
    a[5] = 0;
    a[6] = 0;
    a[7] = 1;
    b[0] = 1;
    b[1] = 0;
    b[2] = 0;
    b[3] = 0;
    b[4] = 0;
    b[5] = 0;
    b[6] = 0;
    b[7] = 1;
    assert[0] = 1;
    assert[1] = 0;
    assert[2] = 0;
    assert[3] = 0;
    assert[4] = 0;
    assert[5] = 0;
    assert[6] = 0;
    assert[7] = 0;    
    c = somaBinario64(a, b);
    for(i = 0; i < 8; i++) {
        if (c[i] - assert[i] != 0) {
            printf("Erro em somaBinario64!\n");
        }
    }
    printf("-------------------------------------\n");
    /*Conferindo deslocaCircular
    */
    printf("Conferindo deslocaCircular\n");
    circular = malloc(64 * sizeof(int));
    assert = realloc(assert, 64 * sizeof(int));
    alpha = 8;
    for (i = 0; i < 64; i++) {
        circular[i] = i; 
    }
    for (i = 0; i < 64; i++) {
        assert[i] = (i+alpha)%64; 
    }
    circular = deslocaCircular(circular, alpha);
    for(i = 0; i < 64; i++) {
        /*printf("%d %d\n", circular[i], assert[i]);*/
        if (circular[i] - assert[i] != 0) {
            printf("%d - %d\n", circular[i], assert[i]);
            printf("Erro em deslocaCircular!\n");
        }
    }
    printf("-------------------------------------\n");
    /*Conferindo geraSubChaves
    */
    printf("Conferindo geraSubChaves\n");
    subChaves = malloc(2 * sizeof(int *));
    chaveK = malloc(128 * sizeof(int));
    for (i = 0; i < 128; i++) {
        chaveK[i] = i;
    }
    subChaves = geraSubChaves(chaveK, 1);
    for (i = 0; i < 64; i++) {
        printf("%d ", subChaves[0][i]);
    }
    printf("\n\n\n\n\n");
    for (i = 0; i < 64; i++) {
        printf("%d ", subChaves[1][i]);
    }
    printf("\n");
    printf("-------------------------------------\n");



    free(a);
    free(b);
    free(c);
    free(bin);
    free(assert);
    free(circular);
    free(chaveK);
    for (i = 0; i < 2; i++) {
        free(subChaves[i]);
    }
    free(subChaves);
    return 0; 
}