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

/* Funcao que realoca uma matriz com n posicoes
// de 128 bits
*/
int **realocaMatriz(int **a, int n) {
	int **realoc = NULL;
	int i, j;

	realoc = calloc(n, sizeof(int *));
	for (i = 0; i < n; i++) {
		realoc[i] = calloc(128, sizeof(int));
	}
	for (i = 0; i < n/2; i++) {
		for (j = 0; j < 128; j++) {
			realoc[i][j] = a[i][j];
		}
	}
	for (i = 0; i < n/2; i++) {
		free(a[i]);
	}

	return realoc;	
}

/* Funcao que calcula a distancia de Hamming entre 2 blocos
// de 128 bits
*/
int hamming(int *a, int *b) {
	int i, dist;

	dist = 0;

	for (i = 0; i < 128; i++) {
		if (a[i] != b[i]) dist++;
	}

	return dist;
}

/* Funcao que calcula o valor de aleatoriedade (entropia)
// pelo metodo 1 descrito no enunciado
*/
void aleatorioMetodo1(int argc, char **argv) {
	FILE *entrada;
	int *chaveK = NULL, *bin = NULL, *X = NULL, *Y = NULL;
	int **subChavesK = NULL, **vetEntra = NULL, **vetAlter = NULL,
	**vetEntraC = NULL, **vetAlterC = NULL;
	int i, j, k, numBlocos;
	unsigned int c;
	char *senha = NULL, *hexaC = NULL;

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
	/******************************************************/
	/* Inicializa o bloco que guarda os valores da        */
	/* entrada, o numero de blocos e o tamanho do vetor de*/
	/* entrada.                                           */
	/******************************************************/		
	numBlocos = 0;
	k = 2;
	vetEntra = calloc(k, sizeof(int *));
	for (i = 0; i < k; i++) {
		vetEntra[i] = calloc(128, sizeof(int));
	}
	/*****************************************************/
	/* Preenche os blocos de entrada                     */
	/*****************************************************/		
	hexaC = malloc(2 * sizeof(char));
	bin = malloc(8 * sizeof(int));
	c = fgetc(entrada);
	while (c != EOF) {
		for(i = 0; c != EOF && i < 16; i++) {
			sprintf(hexaC, "%02x", c);
			bin = hexaParaBinario(hexaC);
			for (j = i * 8; j < (i+1)*8; j++) {
				if (k == numBlocos) {
					vetEntra = realocaMatriz(vetEntra, 2*k);
					k = k * 2;
				}
				vetEntra[numBlocos][j] = bin[j - (8*i)];
			}
			c = fgetc(entrada);
		}
		numBlocos++;
	}
	/*****************************************************/
	/* Copia para vetAlter os valores da entrada         */
	/*****************************************************/		
	vetAlter = calloc(numBlocos, sizeof(int *));
	for (i = 0; i < numBlocos; i++) {
		vetAlter[i] = calloc(128, sizeof(int));
		for (j = 0; j < 128; j++) {
			vetAlter[i][j] = vetEntra[i][j];
		}
	}
	/*****************************************************/
	/* Aloca espaço para os blocos criptografados        */
	/*****************************************************/		
	vetEntraC = calloc(numBlocos, sizeof(int *));
	vetAlterC = calloc(numBlocos, sizeof(int *));
	/**************************************************/
	/* Inicializa Y(V1) para o xor inicial            */
	/**************************************************/	
	Y = malloc(128 * sizeof(int));
	for (i = 0; i < 128; i++) {
		Y[i] = 1;
	}
	/*****************************************************/
	/* Criptografa vetEntra e armazena em vetEntraC      */
	/*****************************************************/
	for (i = 0; i < numBlocos; i++) {		
		X = xor(vetEntra[i], Y, 128);	
		vetEntraC[i] = K128(X, subChavesK, 12);
		Y = vetEntraC[i];
	}			
	/*****************************************************/
	/* Modifica bit a bit de vetAlter                    */
	/*****************************************************/	
	for (i = 0; i < numBlocos; i++) {
		for (j = 0; j < 128; j++) {
				for (k = 0; k < 128; k++) {
					Y[k] = 1;
				}
			/* Bit modificado */
			vetAlter[i][j] = (vetAlter[i][j] + 1) % 2;
			/*****************************************************/
			/* Criptografa vetAlter e armazena em vetAlterC      */
			/*****************************************************/
			for (k = 0; k < numBlocos; k++) {		
				X = xor(vetAlter[i], Y, 128);	
				vetAlterC[i] = K128(X, subChavesK, 12);
				Y = vetAlterC[i];
			}				





			vetAlter[i][j] = (vetAlter[i][j] + 1) % 2;
		}
	}
	return ;
}