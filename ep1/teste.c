#include "funcoesEp1.h"

int main() {
    int *bin, *a, *b, *c;
    int *assert;
    int i;

    /*Conferindo hexaParaBinario
    */
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



    /*Conferindo somaBinario64
    */
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

    free(bin);
    free(a);
    free(b);
    free(c);
    free(assert);
    return 0; 
}