#ifndef _H_ALEATORIOMETODO1
#define _H_ALEATORIOMETODO1

#include "funcoesEp1.h"
#include "conversao.h"

/* Funcao que confere se o uso do programa para calculo de entropia
// esta correto
*/
bool confereChamadaAleatorio1(int argc, char **argv);

/* Funcao que realoca uma matriz com n posicoes
// de 128 bits
*/
int **realocaMatriz(int **a, int n);

/* Funcao que calcula a distancia de Hamming entre 2 blocos
// de 128 bits
*/
int hamming(int *a, int *b);

/* Funcao que imprime a tabela dos resultados
*/
void imprimeTabelaDeResultados(int numBlocos, int *maxH, int *minH, int *somaH);

/* Funcao que calcula o valor de aleatoriedade (entropia)
// pelo metodo 1 descrito no enunciado
*/
void aleatorioMetodo1(int argc, char **argv);




#endif