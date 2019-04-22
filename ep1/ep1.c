#include "funcoesEp1.h"

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

int main(int argc, char *argv[]) {
	char* senha = NULL;
	int* chaveK = NULL;
	int i;
	
	if (argc < 6) {
		instrucoesDeUso();
		return 0;
	}
	while (senha == NULL) {
		printf("Entre com uma senha\n");
		senha = recebeSenha();
	}

	chaveK = geraChaveK(senha);
	for (i = 0; i < 128; i++) {
		if(i%8 == 0)
			printf("\n");
		printf("%d", chaveK[i]);
	}	
	printf("\n");
	free(senha);
	free(chaveK);
	return 0;
}