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

bool confereChamadaCripto(int argc, char *argv) {
	if (argc < 8) return false;
	if (strcmp(argv[2], "-i") != 0) return false;
	if (strcmp(argv[4], "-o") != 0) return false;
	if (strcmp(argv[6], "-p") != 0) return false;
	return true;
}

void criptografar(int argc, char *argv)  {
	if (!confereChamadaCripto(argc, argv)) { 
		printf("Para criptografar arquivos:\n\
programa -c -i <arquivo de entrada> -o\
<arquivo de saída> -p <senha> -a\n\n");
		return;
	}
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

	if (strcmp(argv[1], "-c") == 0) {
		criptografar();
	}

	else if (strcmp(argv[1], "-d") == 0) {
		printf("Falta fazer Decriptografar!\n");
	}

	else if (strcmp(argv[1], "-1") == 0) {
		printf("Falta fazer aleatoriedade pelo método 1!\n");
	}

	else if (strcmp(argv[1], "-2") == 0) {
		printf("Falta fazer aleatoriedade pelo método 2!\n");
	}

	else {
		instrucoesDeUso();
	}

	return 0;
}