#include "funcoesEp1.h"

int main() {
    int *bin, *a, *b, *c;
    int *assert, *circular, *exp, *log;
    int **subChaves = NULL, **bytes = NULL, *chaveK = NULL;
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
            return 0;
        }
    }
    printf("-------------------------------------\n");
    /*Conferindo somaBinario64
    */
    printf("Conferindo somaBinario64\n");
    a = malloc(8 * sizeof(int));
    b = malloc(8 * sizeof(int));
    c = malloc(8 * sizeof(int));    
    for (i = 0; i < 8; i++) {
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
    }
    a[1] = 1;
    b[1] = 1;
    b[4] = 1;
    c[2] = 1;
    c[4] = 1;
    a = somaBinario64(a, b);
    for (i = 0; i < 8; i++) {
        if (a[i] - c[i] != 0) {
            printf("Erro em somaBinario64\n");
            return 0;
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
            return 0;
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
            return 0;
        }
    }
    printf("-------------------------------------\n");
    /*Conferindo galois257
    */
    printf("Conferindo galois257\n");
    exp = malloc(256 * sizeof(double));
    log = malloc(256 * sizeof(double));
    galois257(exp, log);
    printf("exp = \n");
    for (i = 0; i < 256; i++) {
        printf("%d ", exp[i]);
    }
    printf("\n");
    printf("log = \n");
    for (i = 0; i < 256; i++) {
        printf("%d ", log[i]);
    }
    printf("\n");
    for (i = 0; i < 256; i ++) {
        if (log[exp[i]] != i) {
            printf("Erro em galois257!\n");
            return 0;
        }
    }
    printf("-------------------------------------\n");
    /*Conferindo binarioParaDecimal
    */
    printf("Conferindo binarioParaDecimal\n");
    for (i = 0; i < 8; i++) {
        a[i] = 0;
        b[i] = 0;
    }
    b[0] = 1;
    for (i = 0; i < 256; i++) {
        if (i != binarioParaDecimal(a, 8)) {
            printf("Erro em binarioParaDecimal!\n");
            return 0;
        }
        a = somaBinario64(a, b);
    }
    printf("-------------------------------------\n");
    /*Conferindo divide64BitsEm8Bytes
    */
    printf("Conferindo divide64BitsEm8Bytes\n");
    printf("Gerando vetor de 64 bits:");
    for (i = 0; i < 64; i++) {
        circular[i] = (int)rand()%2;
        if (i%8 == 0) printf(" ");
        printf("%d", circular[i]);
    }
    printf("\n");
    printf("Divisao dos bytes gerada: ");
    bytes = divide64BitsEm8Bytes(circular);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%d", bytes[i][j]);
        }
        printf(" ");
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
    for (i = 0; i < (4*4 + 2); i++) {
        free(subChaves[i]);
    }
    free(subChaves);
    free(exp);
    free(log);
    free(bytes);
    return 0; 
}