#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao que recebe um numero em hexadecimal na forma
// XX e devolve o valor correspondente em binario
// hex[0] é o mais significativo
*/
int *hexaParaBinario(char *hex) {
    int *binario = NULL;
    int i;


    /*printf("Em hexaParaBinario temos = %s\n", hex);*/
    binario = malloc(8 * sizeof(int));

    for (i = 0; i < 2; i++) {
        switch(hex[(i+1)%2]) {
            case '0':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 0;
                break;
            case '1':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 0;
                break;
            case '2':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 0;
                break;
            case '3':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 0;
                break;
            case '4':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 0;
                break;
            case '5':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 0;
                break;
            case '6':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 0;
                break;
            case '7':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 0;
                break;
            case '8':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 1;
                break;
            case '9':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 1;
                break;
            case 'a':
            case 'A':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 1;
                break;
            case 'b':
            case 'B':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 1;
                break;
            case 'c':
            case 'C':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 1;
                break;
            case 'd':
            case 'D':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 1;
                break;
            case 'e':
            case 'E':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 1;
                break;
            case 'f':
            case 'F':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 1;
                break;
            default:
                printf("Invalid hexadecimal input.");
            } 
        }
    
    return binario;
}

/* Funcao que recebe um numero em binario e faz a conversao
// para hexadecimal
*/
char *binarioParaHexa(int *bin) {
    int i, j, k, soma;
    char *hexa = NULL;

    hexa = malloc(2 * sizeof(char));
    for (k = 0; k < 2; k++) {
        soma = 0;
        j = 1;
        for (i = (k*4); i < ((k+1)*4); i++) {
            if (bin[i] == 1) {
                soma += j;
            }
            j *= 2;
        }
        if (soma < 10) {
            hexa[(k+1)%2] = soma + '0';
        }
        else if (soma == 10) {
            hexa[(k+1)%2] = 'A';
        }
        else if (soma == 11) {
            hexa[(k+1)%2] = 'B';
        }
        else if (soma == 12) {
            hexa[(k+1)%2] = 'C';
        }
        else if (soma == 13) {
            hexa[(k+1)%2] = 'D';
        }
        else if (soma == 14) {
            hexa[(k+1)%2] = 'E';
        }
        else if (soma == 15) {
            hexa[(k+1)%2] = 'F';
        }
    }
    return hexa;  
}

/* Funcao que recebe um numero binario de n bits em um vetor
// bin e devolve sua representacao em base 10
*/
int binarioParaDecimal(int *bin, int n) {
        int resultado, i, potencia;

        resultado = 0;
        potencia = 1;

        for (i = 0; i < n; i++) {
                if (bin[i] == 1) {
                        resultado = resultado + potencia; 
                }
                potencia *= 2;
        }
        return resultado;
}

/* Funcao que recebe um numero n (0 < n < 256) em base 10 e
// devolve um byte (vetor de 8 bits) com sua representacao em binario
*/
int *decimalParaBinario(int n) {
        int *resultado, i, divisor = 128;

        resultado = malloc(8 * sizeof(int));

        for (i = 7; i >= 0; i--) {
                resultado[i] = n/divisor;
                n = n%divisor;
                divisor = divisor/2;
        }

        return resultado;
}
