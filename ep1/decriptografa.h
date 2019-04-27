#ifndef _H_DECRIPTOGRAFA
#define _H_DECRIPTOGRAFA

#include "funcoesEp1.h"
#include "conversao.h"

/* Funcao que confere se o uso do programa para decriptografar
// o arquivo está correto
*/
bool confereChamadaDecripto(int argc, char **argv);

/* Funcao que decriptografa o arquivo de entrada
*/
void decriptografar(int argc, char **argv);

#endif