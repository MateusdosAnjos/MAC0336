#ifndef _H_CONVERSAO
#define _H_CONVERSAO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao que recebe um numero em hexadecimal na forma
// XX e devolve o valor correspondente em binario
// hex[0] é o mais significativo
*/
int *hexaParaBinario(char *hex);

/* Funcao que recebe um numero em binario e faz a conversao
// para hexadecimal
*/
char *binarioParaHexa(int *bin);

/* Funcao que recebe um numero binario de n bits em um vetor
// bin e devolve sua representacao em base 10
*/
int binarioParaDecimal(int *bin, int n);

/* Funcao que recebe um numero n (0 < n < 256) em base 10 e
// devolve um byte (vetor de 8 bits) com sua representacao em binario
*/
int *decimalParaBinario(int n);

#endif