#include "funcoesEp1.h"
#include "conversao.h"

/* Funcao que confere se o uso do programa para calculo de entropia
// esta correto
*/
bool confereChamadaAleatorio1(int argc, char **argv) {
	if (argc < 6) return false;
	if (strcmp(argv[2], "-i") != 0) return false;
	if (strcmp(argv[4], "-p") != 0) return false;
	return true;
}

/* Funcao que calcula o valor de aleatoriedade (entropia)
// pelo metodo 1 descrito no enunciado
*/
void aleatorioMetodo1(int argc, char **argv) {
	FILE *entrada;
	int *chaveK = NULL;
	int **subChavesK = NULL, **vetEntra = NULL, **vetAlter = NULL,
	**vetEntraC = NULL, **vetAlterC = NULL;
	int i, j, k, numBlocos;
	char *senha = NULL;

	if (!confereChamadaAleatorio1(argc, argv)) { 
		printf("Para calcuo de entropia do arquivo:\n\
programa -1 -i <arquivo de entrada> -p <senha>\n\n");
		return;
	}
	/**************************************************/
	/* Abre e verifica se o arquivo foi aberto        */
	/**************************************************/
	entrada = fopen(argv[3], "r");
	if (!entrada) {
		printf("Problemas ao abrir arquivo a ser calculada a aleatoriedade!\n");
		return;
	}
	/*****************************************************/
	/* Confere se a senha esta de acordo com o enunciado */
	/*****************************************************/
	if (!confereSenha(argv[5], strlen(argv[5]))) {
		printf("A senha deve conter pelo menos 8 caracteres,\n\
com pelo menos 2 letras e 2 algarismos decimais!\n");
		return;
	}
	/*****************************************************/
	/* Completa a senha para que tenha 16 bytes          */
	/*****************************************************/
	senha = completaSenha(argv[7]);
	/*****************************************************/
	/* gera a chaveK a partir da senha fornecida         */
	/*****************************************************/	
	chaveK = geraChaveK(senha);
	/*****************************************************/
	/* gera as subchaves a partir da chaveK              */
	/*****************************************************/		
	subChavesK = geraSubChaves(chaveK, 12);


	return ;
}