#include "funcoesEp1.h"
#include "conversao.h"
#include "aleatorioMetodo1.h"

/* Funcao que confere se o uso do programa para calculo de entropia
// esta correto
*/
bool confereChamadaAleatorio2(int argc, char **argv) {
	if (argc < 6) return false;
	if (strcmp(argv[2], "-i") != 0) return false;
	if (strcmp(argv[4], "-p") != 0) return false;
	return true;
}

/* Funcao que calcula o valor de aleatoriedade (entropia)
// pelo metodo 2 descrito no enunciado
*/
void aleatorioMetodo2(int argc, char **argv) {
	FILE *entrada;
	int *chaveK = NULL, *bin = NULL, *X = NULL, *Y = NULL, *somaH = NULL,
	*maxH = NULL, *minH = NULL;
	int **subChavesK = NULL, **vetEntra = NULL, **vetAlter = NULL,
	**vetEntraC = NULL, **vetAlterC = NULL;
	int i, j, k, l, dist, numBlocos, tamanhoArquivo = 0;
	unsigned int c;
	char *senha = NULL, *hexaC = NULL;

	if (!confereChamadaAleatorio2(argc, argv)) { 
		printf("Para calcuo de entropia do arquivo:\n\
programa -2 -i <arquivo de entrada> -p <senha>\n\n");
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
			tamanhoArquivo++;
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
	/* Aloca espaco para as somas acumuladas das         */
	/* distancias de Hamming (somaH) bem como valor      */
	/* maximo e minimo das distancias entre 2 blocos     */
	/*****************************************************/
	somaH = calloc(numBlocos, sizeof(int));
	maxH = calloc(numBlocos, sizeof(int));
	minH = calloc(numBlocos, sizeof(int));
	/* 128 eh a distancia maxima entre 2 blocos */
	for (i = 0; i < numBlocos; i++) {
		minH[i] = 128;
	}			
	/*****************************************************/
	/* Modifica bit a bit de vetAlter e criptografa o    */
	/* novo bloco armazenando em vetAlterC               */
	/*****************************************************/	
	/*Para cada bloco i*/
	for (i = 0; i < numBlocos; i++) {
		/*Altera o bit j*/
		for (j = 0; j < 128; j++) {
			/*reconstroi Y inicial, para primeiro xor */
			for (k = 0; k < 128; k++) {
				Y[k] = 1;
			}
			/* Bits modificados */
			vetAlter[i][j] = (vetAlter[i][j] + 1) % 2;
			/* Alteracao de consecutivos no mesmo bloco*/
			if (j < 120)
				vetAlter[i][j+8] = (vetAlter[i][j+8] + 1) % 2;
			/* Alteracao em blocos diferentes, desde que nao seja
			// o ultimo bloco*/
			else if (i < numBlocos - 1)
				vetAlter[i+1][j-120] = (vetAlter[i+1][j-120] + 1) % 2;
			/* "Else" seria apenas para o ultimo bloco, porem o CBC nao
			// tera efeito, portanto sem correlacao */
			/*****************************************************/
			/* Criptografa vetAlter e armazena em vetAlterC      */
			/*****************************************************/
			for (k = 0; k < numBlocos; k++) {		
				X = xor(vetAlter[k], Y, 128);	
				vetAlterC[k] = K128(X, subChavesK, 12);
				Y = vetAlterC[k];
			}
			/*****************************************************/
			/* Para cada bloco (Bl) calcula a distancia de       */
			/* hamming entre o original criptografado e o bloco  */
			/* com a alteracao de 1 bit criptografado e acumula  */
			/* em somaH. Guarda o maximo e minimo de cada bloco. */
			/* guarda cada valor calculado em desvio para calculo*/
			/* do desvio padrao                                  */
			/*****************************************************/			
			for (l = i; l < numBlocos; l++) {
				dist = hamming(vetEntraC[l], vetAlterC[l]);
				somaH[l] += dist;
				if (dist > maxH[l]) maxH[l] = dist;
				else if (dist < minH[l]) minH[l] = dist;
			}				
			/*Retorna os bits modificados para os originais*/
			vetAlter[i][j] = (vetAlter[i][j] + 1) % 2;
			/* Retorno de consecutivos no mesmo bloco*/
			if (j < 120)
				vetAlter[i][j+8] = (vetAlter[i][j+8] + 1) % 2;
			/* Retorno em blocos diferentes, desde que nao seja
			// o ultimo bloco*/
			else if (i < numBlocos - 1)
				vetAlter[i+1][j-120] = (vetAlter[i+1][j-120] + 1) % 2;
		}
	}

	imprimeTabelaDeResultados(numBlocos, maxH, minH, somaH);
	/**************************************************/
	/* Sobrescreve e apaga entrada se necessario      */
	/**************************************************/
	if (argc == 7) {
		if (strcmp(argv[6], "-a") == 0) {
			entrada = fopen(argv[3], "w");
			if (!entrada) {
				printf("Problemas ao deletar arquivo de entrada!\n");
				return;
			}
			else {
				for (i = 0; i < tamanhoArquivo; i++) {
					fwrite(" ", sizeof(char), 1, entrada);
				}
			}
			if (remove(argv[3]) == 0){
    			printf("Arquivo de entrada removido com sucesso!\n");
  			}
  			else {
      			printf("Erro na remoção do arquivo!.\n");
    		}
		}
	}	
	fclose(entrada);
	free(chaveK);
	free(bin);
	free(X);
	free(Y);
	free(somaH);
	free(maxH);
	free(minH);
	free(senha);
	free(hexaC);
	for (i = 0; i < (4*12) + 2; i++) {
		free(subChavesK[i]);
	}
	free(subChavesK);	
	for (i = 0; i < numBlocos; i++) {
		free(vetEntra[i]);
		free(vetAlter[i]);
		free(vetEntraC[i]);
		free(vetAlterC[i]);
	}
	free(vetEntra);
	free(vetAlter);
	free(vetEntraC);
	free(vetAlterC);

	return ;
}