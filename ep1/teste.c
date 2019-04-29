#include "funcoesEp1.h"
#include "conversao.h"

int main() {
    /*****************Variaveis dos testes gerais de funcoes*************/
    int *bin, *a, *b, *c, *X;
    int *assert, *circular, *exp, *log, *blocoDados, **blocoCripto = NULL;
    int **subChavesK = NULL, **bytes = NULL, *chaveK = NULL, *cripto = NULL;
    int i, j, k, p, alpha;
    char *byte8 = "010203040506AA10", *hexa, *hexaC, *senha;
    unsigned int charC, ce;
    FILE *entrada, *saida;
    /*******************************************************************/
    /*********Variaveis Para criptografar e decriptografar**************/
    /**/int *Xa, *Xb, *ka, *kb, *ke, *kf, *Xe, *Xf;                  /**/
    /**/int *Y1, *Y2, *Z, *XeFINAL, *XfFINAL, *resultado;            /**/
    /**/int *Y1decri, *Y2decri, *Zdecri;                             /**/    
    /**/int *XeLinha, *XfLinha, R = 12;                              /**/
    /*******************************************************************/

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
    subChavesK = geraSubChaves(chaveK, 12);
    printf("\n");
    for (i = 0; i < (4*12 + 2); i++) {
        printf("\n");
        for (j = 0; j < 64; j++) {
            printf("%d ", subChavesK[i][j]);
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
    /*Conferindo decimalParaBinario
    */
    printf("Conferindo decimalParaBinario\n");
    for (i = 0; i < 256; i++) {
        a = decimalParaBinario(i, 8);
        if (i != binarioParaDecimal(a, 8)) {
            printf("Erro em decimalParaBinario!\n");
            return 0;
        }
        /*for (j = 0; j < 8; j++) {
            printf("%d", a[j]);
        }
        printf("\n");*/
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
    /*Conferindo k128
    */
    printf("Conferindo k128\n");
    blocoDados = malloc(128 * sizeof(int));
    for (i = 0; i < 128; i++) {
        blocoDados[i] = (int)rand()%2;
        printf("%d", blocoDados[i]);
    }
    printf("\n");
    cripto = K128(blocoDados, subChavesK, 12);
    printf("\n");
    for (i = 0; i < 128; i++) {
        printf("%d", cripto[i]);
    }
    printf("\n");
    printf("-------------------------------------\n");
    /*Conferindo binarioParaHexa
    */
    printf("Conferindo binarioParaHexa\n");
    assert[0] = 1;
    assert[1] = 1;
    assert[2] = 0;
    assert[3] = 1;
    assert[4] = 0;
    assert[5] = 1;
    assert[6] = 0;
    assert[7] = 0;
    hexa = binarioParaHexa(assert);
    printf("%c", hexa[0]);
    printf("%c\n", hexa[1]);
    sscanf(hexa, "%02x", &charC);
    printf("char = %c\n", charC);
    printf("-------------------------------------\n");
    /*Conferindo se os blocos recebidos do arquivo de saida
    // sao iguais aos blocos que foram gerados na criptografia
    */
    printf("Conferindo Escrita e Leitura\n");
    /* p serve para armazenar os blocos gerados na criptografia
    // para podermos comparar com os blocos gerados na leitura
    // do arquivo de saida*/
    p = 0;
    blocoCripto = malloc(4 * sizeof(int *));
    senha = "senha123senha123";
    chaveK = geraChaveK(senha);
    subChavesK = geraSubChaves(chaveK, 12);
    /**************************************************/
    /* Abre e verifica se o arquivo foi aberto        */
    /**************************************************/
    entrada = fopen("entrada", "r");
    if (!entrada) {
        printf("Problemas ao abrir arquivo a ser criptografado!\n");
        return 0;
    }
    /**************************************************/
    /*     Abre arquivo de saida                      */
    /**************************************************/
    saida = fopen("saida", "w");
    X = malloc(128 * sizeof(int));
    hexaC = malloc(2 * sizeof(char));
    ce = fgetc(entrada);
    while (ce != EOF) {
        i = 0;
        while(ce != EOF && i < 16) {
            sprintf(hexaC, "%02x", ce);
            bin = hexaParaBinario(hexaC);
            for (j = i * 8; j < (i+1)*8; j++) {
                X[j] = bin[j - (8*i)];
            }
            i++;
            ce = fgetc(entrada);
        }
        /**************************************************/
        /* Criptografa o bloco de 128 bits                */
        /**************************************************/        
        blocoCripto[p] = K128(X, subChavesK, 12);
        p++;
        /**************************************************/
        /* Transforma os bits criptografados em chars     */
        /**************************************************/    
        for (i = 0; i < 16; i++) {
            k = 0;
            for (j = i*8; j < ((i+1)*8); j++) {
                bin[k] = blocoCripto[p-1][j];
                k++; 
            }
        hexaC = binarioParaHexa(bin);
        sscanf(hexaC, "%02x", &charC);
        /**************************************************/
        /*Escreve o char criptografado no arquivo de saida*/
        /**************************************************/    
        fprintf(saida, "%c", charC);
        }
        /**************************************************/
        /* Zera o bloco X (necessario para o ultimo bloco */
        /* do arquivo)                                    */
        /**************************************************/            
        for (j = 0; j < 128; j++) {
            X[j] = 0;
        }
    }
    fclose(entrada);
    fclose(saida);
    saida = fopen("saida", "r");
    ce = fgetc(saida);
    p = 0;
    while (ce != EOF) {
        i = 0;
        while(ce != EOF && i < 16) {
            sprintf(hexaC, "%02x", ce);       
            bin = hexaParaBinario(hexaC);
            for (j = i * 8; j < (i+1)*8; j++) {
                X[j] = bin[j - (8*i)];
            }
            i++;
            ce = fgetc(saida);   
        }
        for (i = 0; i < 128; i++) {
            if (X[i] != blocoCripto[p][i]) {
                printf("erro! letra número %d\n", i);
            }
        }
        p++;
        for (j = 0; j < 128; j++) {
            X[j] = 0;
        }        
    }
    fclose(saida);
    printf("-------------------------------------\n");
    /* Conferindo somaBinario64Inv
    */
    printf("Conferindo somaBinario64Inv\n");
    free(a); free(b); free(c); free(assert);
    srand(300);
    a = calloc(64, sizeof(int));
    b = calloc(64, sizeof(int));
    for (i = 0; i < 64; i++) {
        a[i] = (int)rand()%2;
        b[i] = (int)rand()%2;
    }
    c = somaBinario64(a, b);
    assert = somaBinario64Inv(c, b);
    printf("a      = ");
    for (i = 0; i < 64; i++) {
        printf("%d", a[i]);
    }
    printf("\nassert = ");
    for (i = 0; i < 64; i++) {
        printf("%d", assert[i]);
    }
    printf("\n");
    for (i = 0; i < 64; i++) {
        if (assert[i] != a[i]) {
            printf("Erro em somaBinario64Inv\n");
            return 0;
        }
    }

    printf("\n");
    printf("-------------------------------------\n");
    /* Conferindo odotInv
    */
    printf("Conferindo odotInv\n");
    c = odot(a, b);
    assert = odotInv(c, a);
    printf("b      = ");
    for (i = 0; i < 64; i++) {
        printf("%d", b[i]);
    }
    printf("\nassert = ");
    for (i = 0; i < 64; i++) {
        printf("%d", assert[i]);
    }
    printf("\n");
    for (i = 0; i < 64; i++) {
        if (assert[i] != b[i]) {
            printf("Erro em odotInv\n");
            return 0;
        }
    }
    printf("-------------------------------------\n");    
    /* Conferindo Decriptografia
    */
    printf("Conferindo Decriptografia\n");
    /* Começo da criptografia */
    srand(20);
    printf("X = \n");
    for (i = 0; i < 128; i++) {
        X[i] = (int)rand()%2;
        printf("%d", X[i]);
    }
    printf("\n");
    Xa = malloc(64 * sizeof(int));
    Xb = malloc(64 * sizeof(int));

    for (i = 0; i < 64; i++) {
        Xa[i] = X[i];
        Xb[i] = X[i+64];
    }

    i= 0;
    ka = subChavesK[i*4];
    kb = subChavesK[(i*4)+1];
    ke = subChavesK[(i*4)+2];
    kf = subChavesK[(i*4)+3];
    Xe = odot(Xa, ka);
    Xf = somaBinario64(Xb, kb);
    Y1 = xor(Xe, Xf, 64);
    Y2 = odot(somaBinario64((odot(ke, Y1)), Y1), kf);
    Z = somaBinario64(odot(ke, Y1), Y2);
    /*Saida de 1 iteracao eh a entrada da proxima*/
    Xa = xor(Xe, Z, 64);
    Xb = xor(Xf, Z, 64);
    i = R;
    ka = subChavesK[(i*4)];
    kb = subChavesK[(i*4)+1];
    XeFINAL = odot(Xb, ka);
    XfFINAL = somaBinario64(Xa, kb);

    resultado = malloc(128 * sizeof(int));
    for (i = 0; i < 64; i++) {
        resultado[i] = XeFINAL[i];
        resultado[i+64] = XfFINAL[i];
    }
    printf("Resultado da cripto = \n");
    for (i = 0; i < 128; i++) {
        printf("%d", resultado[i]);
    }
    printf("\n");
    /* Fim da criptografia */

    /*Começo da decriptografia */
    XeFINAL = malloc(64 * sizeof(int));
    XfFINAL = malloc(64 * sizeof(int));

    for (i = 0; i < 64; i++) {
        XeFINAL[i] = resultado[i];
        XfFINAL[i] = resultado[i+64];
    }
    XeLinha = somaBinario64Inv(XfFINAL, subChavesK[((4*R) + 1)]);
    XfLinha = odotInv(XeFINAL, subChavesK[4*R]);

    for (i = 0; i < 64; i++) {
        if (Xa[i] != XeLinha[i] || Xb[i] != XfLinha[i]) {
            printf("Erro na primeira inversão!\n");
            return 0;
        }
    }

    i = 0;
    kf = subChavesK[(4*R) - ((4*i) + 1)];
    ke = subChavesK[(4*R) - ((4*i) + 2)];
    Y1decri = xor(XeLinha, XfLinha, 64);
    for (i = 0; i < 64; i++) {
        if (Y1decri[i] != Y1[i]) {
            printf("Erro na inversao de Y1!\n");
            return 0;
        }
    }
    Y2decri = odot(somaBinario64((odot(ke, Y1decri)), Y1decri), kf);
    for (i = 0; i < 64; i++) {
        if (Y2decri[i] != Y2[i]) {
            printf("Erro na inversao de Y2!\n");
            return 0;
        }
    }    
    Zdecri = somaBinario64(odot(ke, Y1decri), Y2decri);
    Xe = xor(XeLinha, Zdecri, 64);
    Xf = xor(XfLinha, Zdecri, 64);
    kb = subChavesK[(4*R) - ((4*i) + 3)];
    ka = subChavesK[(4*R) - ((4*i) + 4)];
    Xa = odotInv(Xe, ka);
    Xb = somaBinario64Inv(Xf, kb);
    XeLinha = Xa;
    XfLinha = Xb;

    resultado = malloc(128 * sizeof(int));
    for (i = 0; i < 64; i++) {
        resultado[i] = XeLinha[i];
        resultado[i+64] = XfLinha[i];
    }
    /* Fim da decriptografia */

    /* Verificando se o resultado da decriptografia é
    // igual ao bloco que entrou para ser criptografado
    */
    for (i = 0; i < 128; i++) {
        if (X[i] != resultado[i]) {
            printf("Erro em decriptografia\n");
            return 0;
        }
    }
    printf("-------------------------------------\n");        
    free(a);
    free(b);
    free(c);
    free(bin);
    free(assert);
    free(circular);
    for (i = 0; i < (4*12 + 2); i++) {
        free(subChavesK[i]);
    }
    free(subChavesK);
    free(exp);
    free(log);
    free(bytes);
    free(blocoDados);
    free(hexa);
    free(X);
    free(hexaC);
    for (i = 0; i < 2; i++) {
        free(blocoCripto[i]);
    }
    free(blocoCripto);
    return 0; 
}