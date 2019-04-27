#include "funcoesEp1.h"
#include "conversao.h"

/* Funcao que confere se o uso do programa para decriptografar
// o arquivo está correto
*/
bool confereChamadaDecripto(int argc, char **argv) {
	if (argc < 8) return false;
	if (strcmp(argv[2], "-i") != 0) return false;
	if (strcmp(argv[4], "-o") != 0) return false;
	if (strcmp(argv[6], "-p") != 0) return false;
	return true;
}

/* Funcao que decriptografa o arquivo de entrada
*/
void decriptografar(int argc, char **argv)  {
	/**************************************************/
	/* Verifica se a chamada do programa esta correta */
	/**************************************************/
	if (!confereChamadaDecripto(argc, argv)) { 
		printf("Para decriptografar arquivos:\n\
programa -d -i <arquivo de entrada> -o \
<arquivo de saída> -p <senha>\n\n");
		return;
	}
	return;
}