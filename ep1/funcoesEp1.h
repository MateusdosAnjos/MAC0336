#ifndef _H_FUNCOESEP1
#define _H_FUNCOESEP1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

/* Funcao que recebe um numero em hexadecimal na forma
// XX e devolve o valor correspondente em binario
// hex[0] é o mais significativo
*/
int *hexaParaBinario(char *hex);


/* Funcao que recebe uma senha de tamanho n e verifica
// se a senha esta conforme o enunciado pede
*/
bool confereSenha(char *senha, int n);

	
/* Funcao que espera uma senha da entrada conforme
// pedido no enunciado.
*/
char* recebeSenha();


/* Funcao que gera os bits da chave K
*/
int *geraChaveK(char *senha); 


/* Funcao que recebe um numeros a, b em representacao
// binaria e devolve c, tal que c = (a+b)%64
*/
int *somaBinario64(int *a, int *b);

/* Funcao que faz a rotação (deslocamento circular) de
// alpha bits para a esquerda dos 64 bits de beta.
*/
int *deslocaCircular(int *beta, int alpha);

/* Funcao que recebe 8 bytes em hexadecimal e devolve
// os 64 bits correspondentes
*/
int *gera64(char *bytes);

/* Funcao que recebe um binario e devolve sua representacao 
// em base 10
*/
double binarioParaBase10(int *bin);

/* Algoritmo de geracao de subchaves como descrito no
// enunciado
*/
int **geraSubChaves(int *chaveK, int r);

#endif