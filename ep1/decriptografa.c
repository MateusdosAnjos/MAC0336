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
	FILE *entrada, *saida;
	int *chaveK = NULL, *blocoCripto = NULL, *X = NULL, *bin = NULL;
	int **subChavesK = NULL;
	int i, j, k, tamanhoArquivo = 0;
	unsigned int charC, c;
	char *senha = NULL, *hexaC = NULL;
	printf("\n");
	X = malloc(128 * sizeof(int));
	/**************************************************/
	/* Verifica se a chamada do programa esta correta */
	/**************************************************/
	if (!confereChamadaDecripto(argc, argv)) { 
		printf("Para decriptografar arquivos:\n\
programa -d -i <arquivo de entrada> -o \
<arquivo de saída> -p <senha>\n\n");
		return;
	}
	/**************************************************/
	/* Abre e verifica se o arquivo foi aberto        */
	/**************************************************/
	entrada = fopen(argv[3], "r");
	if (!entrada) {
		printf("Problemas ao abrir arquivo a ser decriptografado!\n");
		return;
	}
	/**************************************************/
	/*     Abre arquivo de saida                      */
	/**************************************************/
	saida = fopen(argv[5], "w");
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
	/* gera a chaveK a partir da senha fornecida         */
	/*****************************************************/	
	chaveK = geraChaveK(senha);
	/*****************************************************/
	/* gera as subchaves a partir da chaveK              */
	/*****************************************************/		
	subChavesK = geraSubChaves(chaveK, 12);
	/*****************************************************/
	/* Preenche o bloco X a ser decriptografado          */
	/*****************************************************/
	hexaC = malloc(2 * sizeof(char));
	bin = malloc(8 * sizeof(int));
	c = fgetc(entrada);
	while (c != EOF) {
		i = 0;
		while(c != EOF && i < 16) {
			tamanhoArquivo++;
			sprintf(hexaC, "%02x", c);
			bin = hexaParaBinario(hexaC);
			for (j = i * 8; j < (i+1)*8; j++) {
				X[j] = bin[j - (8*i)];
			}
			i++;
			c = fgetc(entrada);
		}
		/**************************************************/
		/* Decriptografa o bloco de 128 bits              */
		/**************************************************/		
		
		/* Deve implementar o K128Inv */
		blocoCripto = K128Inv(X, subChavesK, 12);
		
		/**************************************************/
		/* Transforma os bits decriptografados em chars   */
		/**************************************************/	
		for (i = 0; i < 16; i++) {
			k = 0;
			for (j = i*8; j < ((i+1)*8); j++) {
				bin[k] = blocoCripto[j];
				k++; 
			}
		hexaC = binarioParaHexa(bin);
		sscanf(hexaC, "%02x", &charC);
		/*****************************************************/
		/*Escreve o char decriptografado no arquivo de saida */
		/*****************************************************/	
		fprintf(saida, "%c", charC);
		}
		/**************************************************/
		/* Zera o bloco X (necessario para o ultimo bloco */
		/* do arquivo)                                    */
		/**************************************************/			
		for (j = 0; j < 128; j++) {
			X[j] = 0;
		}
	}
	/**************************************************/
	/* Fecha os arquivos que foram abertos            */
	/**************************************************/
	fclose(entrada);
	fclose(saida);
	return;
}