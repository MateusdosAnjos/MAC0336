#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* Funcao que recebe um numero em hexadecimal na forma
// XX e devolve o valor correspondente em binario
// hex[0] é o mais significativo
*/
int *hexaParaBinario(char *hex) {
	int *binario = NULL;
	int i;


	binario = malloc(8 * sizeof(int));

	for (i = 0; i < 2; i++) {
		switch(hex[(i+1)%2]) {
			case '0':
	            binario[0 + (4*i)] = 0;
	            binario[1 + (4*i)] = 0;
	            binario[2 + (4*i)] = 0;
	            binario[3 + (4*i)] = 0;
                break;
	      	case '1':
	            binario[0 + (4*i)] = 1;
	            binario[1 + (4*i)] = 0;
	            binario[2 + (4*i)] = 0;
	            binario[3 + (4*i)] = 0;
	            break;
	     	case '2':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 0;
                break;
	    	case '3':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 0;
                break;
	     	case '4':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 0;
                break;
	        case '5':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 0;
                break;
	        case '6':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 0;
                break;
	        case '7':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 0;
                break;
	        case '8':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 1;
                break;
	        case '9':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 1;
                break;
	        case 'a':
	        case 'A':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 1;
                break;
	        case 'b':
	        case 'B':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 0;
                binario[3 + (4*i)] = 1;
                break;
	        case 'c':
	        case 'C':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 1;
                break;
	        case 'd':
	        case 'D':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 0;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 1;
                break;
	        case 'e':
	        case 'E':
                binario[0 + (4*i)] = 0;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 1;
                break;
	        case 'f':
	        case 'F':
                binario[0 + (4*i)] = 1;
                binario[1 + (4*i)] = 1;
                binario[2 + (4*i)] = 1;
                binario[3 + (4*i)] = 1;
                break;
	        default:
	            printf("Invalid hexadecimal input.");
	        } 
	    }
	
	return binario;
}

/* Funcao que recebe uma senha de tamanho n e verifica
// se a senha esta conforme o enunciado pede
*/
bool confereSenha(char *senha, int n) {
	int numChar = 0, num09 = 0, i;

	/* Conferindo o tamanho minimo desejado
	*/
	if (n < 8) return false;

	/* Conferindo se temos pelo menos 2 letras e 2 
	// algarismos decimais (poderia ser mais eficiente
	// porem julguei esta forma mais legivel).
	*/
	for (i = 0; i < n; i++) {
		if (isalpha(senha[i])) numChar++;
		else if (isdigit(senha[i])) num09++;
	}
	if (numChar < 2) return false;
	if (num09 < 2) return false;
	return true;
}
/* Funcao que espera uma senha da entrada conforme
// pedido no enunciado.
*/
char* recebeSenha() {
	int i = 0, j;
	char* senha;
	char c;

	senha = malloc(16 * sizeof(char));
	c = getchar();
	/* 10 representa a tecla "ENTER"
	// -1 representa o fim de um arquivo
	*/
	while (c != -1 && c != 10) {
		senha[i] = c;
		c = getchar();
		i++;
	}

	/*conferindo se a senha esta OK
	*/
	if (!confereSenha(senha, strlen(senha))) {
		return NULL;
	}
	/*Tudo OK, completamos a senha se necessario
	*/
	i = strlen(senha);
	j = i;

	/*completa senha caso necessário
	*/
	while (i < 16) {
		senha[i] = senha[i - j];
		i++;
	}

	return senha;
}

int geraChaveK(char *senha) {
	int i;
	for (i = 0; i < 16; i++) {
		printf("%X ", senha[i]);
	}
	return 0;
}

int main() {
	char* senha = NULL;
	
	while (senha == NULL) {
		printf("Entre com uma senha\n");
		senha = recebeSenha();
	}

	geraChaveK(senha);
	printf("\n");

	free(senha);
	return 0;
}