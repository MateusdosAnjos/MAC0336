#include "funcoesEp1.h"


int main() {
	char* senha = NULL;
	int* chaveK = NULL;
	int i;
	
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