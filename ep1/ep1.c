#include "funcoesEp1.h"

/* Funcao que explica o uso do programa
*/
void instrucoesDeUso() {
	printf("Modo (1) Para criptografar arquivos:\n\
programa -c -i <arquivo de entrada> -o\
<arquivo de saída> -p <senha> -a\n\n");
	printf("Modo (2) Para decriptografar arquivos:\n\
programa -d -i <arquivo de entrada> -o <arquivo\
de saída> -p <senha>\n\n");
	printf("Modo (3) Para calcular aleatoriedade pelo método 1:\n\
programa -1 -i <arquivo de entrada> -p <senha>\n\n");
	printf("Modo (4) Para calcular aleatoriedade pelo método 2:\n\
programa -2 -i <arquivo de entrada> -p <senha>\n\n");
	return;
}

/* Funcao que confere se o uso do programa para criptografar
// o arquivo está correto
*/
bool confereChamadaCripto(int argc, char **argv) {
	if (argc < 8) return false;
	if (strcmp(argv[2], "-i") != 0) return false;
	if (strcmp(argv[4], "-o") != 0) return false;
	if (strcmp(argv[6], "-p") != 0) return false;
	return true;
}

/* Funcao que criptografa o arquivo de entrada
*/
void criptografar(int argc, char **argv)  {
	FILE *entrada, *saida;
	int *chaveK = NULL;
	int **subChavesK = NULL;
	int *blocoCripto = NULL;
	int *X = NULL, *bin = NULL;
	int i, j;
	char *senha = NULL, *hexaC = NULL;
	char c;
	printf("");
	X = malloc(128 * sizeof(int));
	/**************************************************/
	/* Verifica se a chamada do programa esta correta */
	/**************************************************/
	if (!confereChamadaCripto(argc, argv)) { 
		printf("Para criptografar arquivos:\n\
programa -c -i <arquivo de entrada> -o\
<arquivo de saída> -p <senha> -a\n\n");
		return;
	}
	/**************************************************/
	/* Abre e verifica se o arquivo foi aberto        */
	/**************************************************/
	entrada = fopen(argv[3], "r");
	if (!entrada) {
		printf("Problemas ao abrir arquivo a ser criptografado!\n");
		return;
	}
	/*****************************************************/
	/* Confere se a senha esta de acordo com o enunciado */
	/*****************************************************/
	if (!confereSenha(argv[7], strlen(argv[7]))) {
		printf("A senha deve conter pelo menos 8 caracteres,\n\
com pelo menos 2 letras e 2 algarismos decimais!\n");
		return;
	}
	/*****************************************************/
	/* Completa a senha para que tenha 16 bytes          */
	/*****************************************************/
	senha = completaSenha(argv[7]);
	/*****************************************************/
	/* Preenche o bloco X a ser criptografado            */
	/*****************************************************/
	hexaC = malloc(2 * sizeof(char));
	bin = malloc(8 * sizeof(int));
	i = 0;
	while((c = fgetc(entrada)) != EOF && i < 16) {
		sprintf(hexaC, "%02x", c);
		bin = hexaParaBinario(hexaC);
		for (j = i * 8; j < (i+1)*8; j++) {
			X[j] = bin[j - (8*i)];
		}
		i++;
	}
	chaveK = geraChaveK(senha);
	subChavesK = geraSubChaves(chaveK, 12);
	blocoCripto = K128(X, subChavesK, 12);
	for (i = 0; i < 128; i++) {
		printf("%d ", blocoCripto[i]);
	}
	printf("\n");
	/**************************************************/
	/*     Abre arquivo de saida                      */
	/**************************************************/
	saida = fopen(argv[5], "w");


	fclose(entrada);
	fclose(saida);
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
		printf("Falta fazer Decriptografar!\n");
	}

	/**************************************************/
	/*        Calculo de aleatoriedade metodo 1       */
	/**************************************************/
	else if (strcmp(argv[1], "-1") == 0) {
		printf("Falta fazer aleatoriedade pelo método 1!\n");
	}

	/**************************************************/
	/*        Calculo de aleatoriedade metodo 2       */
	/**************************************************/
	else if (strcmp(argv[1], "-2") == 0) {
		printf("Falta fazer aleatoriedade pelo método 2!\n");
	}

	/**************************************************/
	/*                   Erro                         */
	/**************************************************/
	else {
		instrucoesDeUso();
	}

	return 0;
}