#ifndef _H_CRIPTOGRAFA
#define _H_CRIPTOGRAFA

#include "funcoesEp1.h"
#include "conversao.h"

/* Funcao que confere se o uso do programa para criptografar
// o arquivo está correto
*/
bool confereChamadaCripto(int argc, char **argv);

/* Funcao que criptografa o arquivo de entrada
*/
void criptografar(int argc, char **argv);

#endif