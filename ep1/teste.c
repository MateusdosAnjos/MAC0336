#include "funcoesEp1.h"

int main() {
    int *bin, *a, *b, *c;
    int *assert, *circular;
    int **subChaves = NULL, *chaveK = NULL;
    int i, j, alpha;
    char *byte8 = "010203040506AA10";

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
    /*Conferindo gera64
    */
    printf("Conferindo gera64\n");
        a = realloc(a, 64*sizeof(int));
        a = gera64(byte8);
        for (i = 0; i < 64; ++i) {
            if (i%8 == 0) printf(" ");
            printf("%d", a[i]);
        }
    printf("\n");
    printf("-------------------------------------\n");
    /*Conferindo mod64
    */
    printf("Conferindo mod64\n");
    for (i = 0; i < 64; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 64; i++) {
        a[i] = rand()%2;
        printf("%d", a[i]);
    }
    printf("\n");
    printf("mod64 = %d\n", mod64(a));
    printf("-------------------------------------\n");
    /*Conferindo geraSubChaves
    */
    printf("Conferindo geraSubChaves\n");
    chaveK = malloc(128 * sizeof(int));
    printf("chaveK = \n");
    for (i = 0; i < 128; i++) {
        chaveK[i] = (int)rand()%2;
        printf("%d", chaveK[i]);
    }
    printf("\n");
    subChaves = geraSubChaves(chaveK, 4);
    printf("\n");
    for (i = 0; i < (4*4 + 2); i++) {
        printf("\n");
        for (j = 0; j < 64; j++) {
            printf("%d ", subChaves[i][j]);
        }
    }
    printf("\n");
    printf("-------------------------------------\n");
    /*Conferindo xor
    */
    printf("Conferindo xor\n");
    a[0] = 1;
    a[1] = 0;
    a[2] = 0;
    a[3] = 1;
    a[4] = 1;
    a[5] = 1;
    a[6] = 0;
    a[7] = 1;
    b[0] = 1;
    b[1] = 0;
    b[2] = 0;
    b[3] = 1;
    b[4] = 0;
    b[5] = 1;
    b[6] = 1;
    b[7] = 1;
    assert[0] = 0;
    assert[1] = 0;
    assert[2] = 0;
    assert[3] = 0;
    assert[4] = 1;
    assert[5] = 0;
    assert[6] = 1;
    assert[7] = 0;    
    c = xor(a, b, 8);
    for(i = 0; i < 8; i++) {
        if (c[i] - assert[i] != 0) {
            printf("Erro em xor!\n");
        }
    }
    printf("-------------------------------------\n");

    
    free(a);
    free(b);
    free(c);
    free(bin);
    free(assert);
    free(circular);
    free(chaveK);
    for (i = 0; i < (4*4 + 2); i++) {
        free(subChaves[i]);
    }
    free(subChaves);
    return 0; 
}