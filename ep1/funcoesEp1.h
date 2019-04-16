#ifndef _H_FUNCOESEP1
#define _H_FUNCOESEP1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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

#endif