#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* recebeSenha() {
	int i = 0, j;
	char* a;
	char c;

	a = malloc(sizeof(char));
	c = getchar();
	/* 10 representa a tecla "ENTER"*/
	while (c != -1 && c != 10) {
		a[i] = c;
		c = getchar();
		i++;
	}
	i = strlen(a);
	j = i;
	while (i < 16) {
		a[i] = a[i - j];
		i++;
	}
	return a;
}

int geraChaveK() {
	return 0;
}

int main() {
	char* a;
	printf("Falta Fazer o EP :D\n");
	a = recebeSenha();
	printf("%s\n", a);
	return 0;
}