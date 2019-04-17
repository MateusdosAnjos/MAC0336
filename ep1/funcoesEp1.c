#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

/* Funcao que recebe um numero em hexadecimal na forma
// XX e devolve o valor correspondente em binario
// hex[0] é o mais significativo
*/
int *hexaParaBinario(char *hex) {
	int *binario = NULL;
	int i;


	/*printf("Em hexaParaBinario temos = %s\n", hex);*/
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

/* Funcao que gera os bits da chave K
*/
int *geraChaveK(char *senha) {
	int *chaveK;
	int *bin = NULL;
	int i, j, k;
	char * c;

	chaveK = malloc(128 * sizeof(int));
	bin = malloc(8 * sizeof(int));
	c = malloc(16 * sizeof(char));
	for (i = 0; i < 16; i++) {
		sprintf(c, "%02x", senha[i]);
		bin = hexaParaBinario(c);
		for (j = i * 8; j < (i+1)*8; j++) {
			chaveK[j] = bin[j - (8*i)];
		}
		for (k = 0; k < 8; k++) {
			bin[k] = 0;
		}
	}
	free(bin);
	free(c);
	return chaveK;
}

/* Funcao que recebe um numeros a, b em representacao
// binaria e devolve c, tal que c = (a+b)%64
*/
int *somaBinario64(int *a, int *b) {
	int *c;
	int i;
	int vaiUm = 0;
	c = calloc(64, sizeof(int));

	for (i = 0; i < 64; i++) {
		c[i] = (a[i] + b[i] + vaiUm)%2;
		vaiUm = (a[i] + b[i] + vaiUm)/2;
	}

	return c;
}

/* Funcao que faz a rotacao (deslocamento circular) de
// alpha bits para a esquerda dos 64 bits de beta.
*/
int *deslocaCircular(int *beta, int alpha) {
	int i;
	int *deslocado;

	deslocado = malloc(alpha * sizeof(int));

	for (i = 0; i < alpha; i++) {
		deslocado[i] = beta[i];
	}
	for (i = alpha; i < 64; i++) {
		beta[i-alpha] = beta[i];
	}
	for (i = 64-alpha; i < 64; i++) {
		beta[i] = deslocado[i - (64-alpha)];
	}

	free(deslocado);
	return beta;
}

/* Funcao que recebe 8 bytes em hexadecimal e devolve
// os 64 bits correspondentes
*/
int *gera64(char *bytes) {
	int *bits = NULL, *aux;
	int i, j, k = 0;
	char *c = NULL;

	bits = malloc(64 * sizeof(int));
	aux = malloc(8 * sizeof(int));
	c = malloc(2 * sizeof(char));
	for (i = 15; i > 0; i = i - 2) {
		c[1] = bytes[i];
		c[0] = bytes[i-1];
		aux = hexaParaBinario(c);
		for (j = 0; j < 8; j++) {
			bits[k] = aux[j];
			k++;
		}
	}
	free(aux);
	return bits;
}

double binarioParaBase10(int *bin) {
	double resp = 0;
	int i;

	for (i = 0; i < 64; i++) {
		if (bin[i] == 1) { 
			resp = resp + pow(2, i);
		}
	}
	return resp;
}

/* Algoritmo de geracao de (4*r + 2) sub Chaves como descrito no
// enunciado
*/
int **geraSubChaves(int *chaveK, int r) {
	int **L = NULL, **subChavesK = NULL, *offset1, *offset2, *offset3,
	*A, *B, *C;
	int i, j, x = 0, y = 0, s;
	char *c1 = "9e3779b97f4a7151", *c2 = "8aed2a6bb7e15162",
	*c3 = "7c159e3779b97f4a";

	/*Alocando memórias*/
	L = (int **)malloc((4*r + 2) * sizeof(int *));
	for (i = 0; i < (4*r + 2); i++) {
		L[i] = malloc(64 * sizeof(int));
	}
	subChavesK = (int **)malloc((4*r + 2) * sizeof(int *));
	for (i = 0; i < (4*r + 2); i++) {
		subChavesK[i] = malloc(64 * sizeof(int));
	}

	/*Utilizaremos isso para o calculo*/
	offset1 = malloc(64 * sizeof(int));
	offset2 = malloc(64 * sizeof(int));
	offset3 = malloc(64 * sizeof(int));

	offset1 = gera64(c1);
	offset2 = gera64(c2);
	offset3 = gera64(c3);

	/*Passo 1 do algoritmo descrito no enunciado*/
	for (i = 0; i < 128; i++) {
		if (i%8 < 4) {
			L[1][y] = chaveK[i];
			y++;
		}
		else {
			L[0][x] = chaveK[i];
			x++;
		}
	}
	/*Passo 2 do algoritmo descrito no enunciado*/
	for (j = 2; j < (4*r + 2); j++) {
		L[j] = somaBinario64(L[j-1], offset1);
	} 
	/*Passo 3 do algoritmo descrito no enunciado*/
	subChavesK[0] = offset2;
	/*Passo 4 do algoritmo descrito no enunciado*/
	for (j = 1; j < (4*r + 2); j++) {
		subChavesK[j] = somaBinario64(subChavesK[j-1], offset3);
	} 
	/*Passo 5 do algoritmo descrito no enunciado*/
	i = 0;
	j = 0;
	A = calloc(64, sizeof(int));
	B = calloc(64, sizeof(int));
	C = calloc(64, sizeof(int));

	/*Passo 6 do algoritmo descrito no enunciado*/
	for (s = 1; s < (4*r + 2); s++) {
		C = somaBinario64(A, B);
		subChavesK[i] = deslocaCircular(somaBinario64(subChavesK[i], C), 3);
		A = subChavesK[i];
		i++;
		C = somaBinario64(A, B);
		L[j] = deslocaCircular(somaBinario64(L[j], C), binarioParaBase10(C));
		B = L[j];
		j++;
	}

	/*Liberando a memória*/
	free(offset1);
	free(offset2);
	free(offset3);
	for (i = 0; i < (4*r+2); i++) {
        free(L[i]);
    }
    free(L);
    free(A);
    free(B);
    free(C);

    /*devolvendo a resposta*/
	return subChavesK;
}