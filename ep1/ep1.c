#include "funcoesEp1.h"
#include "conversao.h"
#include "criptografa.h"
#include "decriptografa.h"
#include "aleatorioMetodo1.h"
#include "aleatorioMetodo2.h"

/* Funcao que explica o uso do programa
*/
void instrucoesDeUso() {
	printf("INSTRUÇÕES DE USO DO PROGRAMA EP1:\n");
	printf("\"-a\" é opcional e irá deletar o arquivo de entrada!\n\n");
	printf("Modo (1) Para criptografar arquivos:\n\
./ep1 -c -i <arquivo de entrada> -o \
<arquivo de saída> -p <senha> -a\n\n");
	printf("Modo (2) Para decriptografar arquivos:\n\
./ep1 -d -i <arquivo de entrada> -o <arquivo\
de saída> -p <senha> -a\n\n");
	printf("Modo (3) Para calcular aleatoriedade pelo método 1:\n\
./ep1 -1 -i <arquivo de entrada> -p <senha> -a\n\n");
	printf("Modo (4) Para calcular aleatoriedade pelo método 2:\n\
./ep1 -2 -i <arquivo de entrada> -p <senha> -a\n\n");
	return;
}

/* MAIN
*/
int main(int argc, char *argv[]) {
	
	/**************************************************/
	/*         Mostra como utilizar o programa        */
	/**************************************************/
	if (argc < 6) {
		instrucoesDeUso();
		return 0;
	}

	/**************************************************/
	/*            Criptografar                        */
	/**************************************************/
	if (strcmp(argv[1], "-c") == 0) {
		criptografar(argc, argv);
	}

	/**************************************************/
	/*            Decriptografar                      */
	/**************************************************/
	else if (strcmp(argv[1], "-d") == 0) {
		decriptografar(argc, argv);
	}

	/**************************************************/
	/*        Calculo de aleatoriedade metodo 1       */
	/**************************************************/
	else if (strcmp(argv[1], "-1") == 0) {
		aleatorioMetodo1(argc, argv);
	}

	/**************************************************/
	/*        Calculo de aleatoriedade metodo 2       */
	/**************************************************/
	else if (strcmp(argv[1], "-2") == 0) {
		aleatorioMetodo2(argc, argv);
	}

	/**************************************************/
	/*                   Erro                         */
	/**************************************************/
	else {
		instrucoesDeUso();
	}

	return 0;
}