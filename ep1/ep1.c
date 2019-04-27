#include "funcoesEp1.h"
#include "conversao.h"

/* Funcao que explica o uso do programa
*/
void instrucoesDeUso() {
	printf("Modo (1) Para criptografar arquivos:\n\
programa -c -i <arquivo de entrada> -o \
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
	int i, j, k, tamanhoArquivo = 0;
	char *senha = NULL, *hexaC = NULL;
	unsigned int charC, c;
	printf("");
	X = malloc(128 * sizeof(int));
	/**************************************************/
	/* Verifica se a chamada do programa esta correta */
	/**************************************************/
	if (!confereChamadaCripto(argc, argv)) { 
		printf("Para criptografar arquivos:\n\
programa -c -i <arquivo de entrada> -o \
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
	/* Preenche o bloco X a ser criptografado            */
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
		/* Criptografa o bloco de 128 bits                */
		/**************************************************/		
		blocoCripto = K128(X, subChavesK, 12);
		/**************************************************/
		/* Transforma os bits criptografados em chars     */
		/**************************************************/	
		for (i = 0; i < 16; i++) {
			k = 0;
			for (j = i*8; j < ((i+1)*8); j++) {
				bin[k] = blocoCripto[j];
				k++; 
			}
		hexaC = binarioParaHexa(bin);
		sscanf(hexaC, "%02x", &charC);
		/**************************************************/
		/*Escreve o char criptografado no arquivo de saida*/
		/**************************************************/	
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
	/**************************************************/
	/* Sobrescreve e apaga entrada se necessario      */
	/**************************************************/
	if (argc == 9) {
		if (strcmp(argv[8], "-a") == 0) {
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
    			printf("Arquivo criptografado e removido com sucesso!\n");
  			}
  			else {
      			printf("Erro na remoção do arquivo!.\n");
    		}
		}
	}		
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