#ifndef _H_FUNCOESEP1
#define _H_FUNCOESEP1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "conversao.h"

/* Funcao que recebe uma senha de tamanho n e verifica
// se a senha esta conforme o enunciado pede
*/
bool confereSenha(char *senha, int n);

	
/* Funcao que completa a senha da entrada conforme
// pedido no enunciado.
*/
char *completaSenha(char *senha);


/* Funcao que gera os bits da chave K
*/
int *geraChaveK(char *senha); 


/* Funcao que recebe um numeros a, b em representacao
// binaria e devolve c, tal que c = (a+b)%(2^64)
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

/* Funcao que recebe um vetor bin de 64 bits
// e devolve um intero resp tal que:
// bin%64 = resp
*/
int mod64(int *bin);

/* Algoritmo de geracao de subchaves como descrito no
// enunciado
*/
int **geraSubChaves(int *chaveK, int r);

/* Funcao que recebe 2 vetores com n bits e
// calcula c fazendo XOR de a com b
*/ 
int *xor(int *a, int *b, int n);

/* Funcao que preenche os vetores exp e log
// referente ao corpo de Galois(257)
*/
void galois257(int *exp, int *log);

/* Funcao que divide os 64 bits de A em 8 bytes
// de 8 bits
*/
int **divide64BitsEm8Bytes(int *A);

/* Funcao que implementa a operacao basica numero 3
// (em LaTeX \odot)
*/
int *odot(int *B, int *C);

/* Funcao que implementa o K 128 como descrito no enunciado
*/
int *K128(int *X, int **subChavesK, int R);

#endif