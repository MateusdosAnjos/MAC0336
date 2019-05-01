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

/* Funcao que recebe um bloco X de n bits (128) e verifica
// se este bloco tem todas as posicoes iguais a zero (0)
// sinalizando que este eh o bloco que marca o termino
// do arquivo
*/
bool blocoFinal(int *X, int n) {
	int i;

	for (i = 0; i < n; i++) {
		if (X[i] != 1) return false;
	}

	return true;
}

/* Funcao que decriptografa o arquivo de entrada
*/
void decriptografar(int argc, char **argv)  {
	FILE *entrada, *saida;
	int *chaveK = NULL, *blocoDecripto = NULL, *X = NULL, *bin = NULL,
	*blocoTeste = NULL, *Y = NULL;
	int **subChavesK = NULL;
	int i, j, k, tamanhoAtual = 0, tamanhoOriginal;
	unsigned int charC, c;
	char *senha = NULL, *hexaC = NULL, *buffer = NULL;
	printf("\n");
	X = malloc(128 * sizeof(int));
	blocoTeste = malloc(128 * sizeof(int));
	Y = malloc(128 * sizeof(int));
	/**************************************************/
	/* Inicializa Y(V1) para o xor inicial            */
	/**************************************************/
	for (i = 0; i < 128; i++) {
		Y[i] = 1;
	}
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
	buffer = malloc(16 * sizeof(char));
	/*****************************************************/
	/* Le o primeiro bloco do arquivo                    */
	/*****************************************************/	
	c = fgetc(entrada);
	for (i = 0; c != EOF && i < 16; i++) {
		sprintf(hexaC, "%02x", c);
		bin = hexaParaBinario(hexaC);
		for (j = i * 8; j < (i+1)*8; j++) {
			X[j] = bin[j - (8*i)];
		}
		c = fgetc(entrada);
	}
	while (c != EOF) {
		/*****************************************************/
		/* Le o bloco que dira se o arquivo acabou ou nao    */
		/*****************************************************/		
		for (i = 0; c != EOF && i < 16; i++) {
			sprintf(hexaC, "%02x", c);
			bin = hexaParaBinario(hexaC);
			for (j = i * 8; j < (i+1)*8; j++) {
				blocoTeste[j] = bin[j - (8*i)];
			}
			c = fgetc(entrada);
		}
		/*****************************************************/
		/* Testa se o bloco de teste eh o bloco que marca o  */
		/* termino do arquivo a ser decriptografado          */
		/*****************************************************/		
		if (!blocoFinal(blocoTeste, 128)) {
			/*NAO EH O BLOCO DE TERMINO*/
			/**************************************************/
			/* Decriptografa o bloco de 128 bits              */
			/**************************************************/		
			blocoDecripto = K128Inv(X, subChavesK, 12);
			blocoDecripto = xor(blocoDecripto, Y, 128);
			/**************************************************/
			/* preenche Y para proxima iteracao              */
			/**************************************************/			
			for (i = 0; i < 128; i++) {
				Y[i] = X[i];
			}
			/**************************************************/
			/* Transforma os bits decriptografados em chars   */
			/**************************************************/	
			for (i = 0; i < 16; i++) {
				k = 0;
				for (j = i*8; j < ((i+1)*8); j++) {
					bin[k] = blocoDecripto[j];
					k++; 
				}
				hexaC = binarioParaHexa(bin);
				sscanf(hexaC, "%02x", &charC);
				/*****************************************************/
				/*Coloca o char decriptografado no buffer            */
				/*****************************************************/	
				buffer[i] = charC;
			}
			/*****************************************************/
			/*Escreve o buffer no arquivo de saida               */
			/*****************************************************/			
			fwrite(buffer, 16, sizeof(char), saida);
			tamanhoAtual += 16;
			/*OBS: Se o bloco de teste NAO era o bloco final, entao*/
			/*podemos escrever os 16 caracteres no arquivo de saida*/
			/*******************************************************/
			/*Agora copiamos o bloco de teste anterior para o X    */
			/*ja que sempre decriptografamos o bloco que esta em X */
			/*******************************************************/
			for (i = 0; i < 128; i++) {
				X[i] = blocoTeste[i];
			}
		}
		else {
			/*EH O BLOCO DE TERMINO*/
			/********************************************************/
			/*Devemos ler agora o bloco que guarda o tamanho do     */
			/*arquivo original, para termos uma saida sem restos    */
			/*(lixo) no final do arquivo de saida.                  */			
			/********************************************************/						
			for (i = 0; c != EOF && i < 16; i++) {
				sprintf(hexaC, "%02x", c);
				bin = hexaParaBinario(hexaC);
				for (j = i * 8; j < (i+1)*8; j++) {
					blocoTeste[j] = bin[j - (8*i)];
				}
				c = fgetc(entrada);
			}
			/********************************************************/
			/* Recuperamos o tamanho do arquivo original            */
			/********************************************************/
			blocoDecripto = K128Inv(blocoTeste, subChavesK, 12);
			tamanhoOriginal = binarioParaDecimal(blocoDecripto, 64);
			/********************************************************/
			/* Decriptografamos o ultimo bloco real do arquivo      */
			/********************************************************/
			blocoDecripto = K128Inv(X, subChavesK, 12);
			blocoDecripto = xor(blocoDecripto, Y, 128);
			for (i = 0; i < 16; i++) {
				k = 0;
				for (j = i*8; j < ((i+1)*8); j++) {
					bin[k] = blocoDecripto[j];
					k++; 
				}
				hexaC = binarioParaHexa(bin);
				sscanf(hexaC, "%02x", &charC);
				/*****************************************************/
				/*Coloca o char decriptografado no buffer            */
				/*****************************************************/	
				buffer[i] = charC;
			}
			/*****************************************************/
			/*Escreve apenas os caracteres restantes que compoem */
			/*o arquivo original no arquivo de saida             */
			/*****************************************************/		
			fwrite(buffer, tamanhoOriginal - tamanhoAtual, sizeof(char), saida);
		}
	}
	/**************************************************/
	/* Fecha os arquivos que foram abertos            */
	/**************************************************/
	fclose(entrada);
	fclose(saida);
	/**************************************************/
	/* Libera memoria                                 */
	/**************************************************/
	free(chaveK);	
	free(blocoDecripto);	
	free(X);	
	free(bin);	
	free(blocoTeste);	
	free(senha);	
	free(hexaC);
	free(buffer);
	for (i = 0; i < (4*12) + 2; i++) {
		free(subChavesK[i]);
	}
	free(subChavesK);
	
	return;
}