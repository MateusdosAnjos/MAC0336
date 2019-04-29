#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include "conversao.h"

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
/* Funcao que completa a senha da entrada conforme
// pedido no enunciado.
*/
char *completaSenha(char *senha) {
	int i = 0, j;
	char* senhaCompleta;

	senhaCompleta = malloc(16 * sizeof(char));

	for (i = 0; i < strlen(senha); i++) {
		senhaCompleta[i] = senha[i];
	}

	i = strlen(senha);
	j = i;

	while (i < 16) {
		senhaCompleta[i] = senha[i - j];
		i++;
	}

	return senhaCompleta;
}

/* Funcao que gera os bits da chave K
*/
int *geraChaveK(char *senha) {
	int *chaveK;
	int *bin = NULL;
	int i, j, k;
	char *c;

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
// binaria e devolve c, tal que c = (a+b)%(2^64)
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

/* Funcao que calcula a soma binaria inversa mod 2^64
// necessaria para a decriptografia
*/
int *somaBinario64Inv(int *a, int *b) {
	int *resultado;
	uint64_t aDec, bDec;

	aDec = binarioParaDecimal(a, 64);
	bDec = binarioParaDecimal(b, 64);
	resultado = decimalParaBinario((aDec - bDec), 64);

	return resultado;
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
	free(c);
	return bits;
}

/* Funcao que recebe um vetor bin de 64 bits
// e devolve um intero resp tal que:
// bin%64 = resp
*/
int mod64(int *bin) {
	int i;
	int resp = 0;

	for(i = 0; i < 6; i++) {
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
		L[i] = calloc(64, sizeof(int));
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
	for (j = 2; j <= (4*r + 2); j++) {
		L[j] = somaBinario64(L[j-1], offset1);
	}
	/*Passo 3 do algoritmo descrito no enunciado*/
	subChavesK[0] = offset2;
	/*Passo 4 do algoritmo descrito no enunciado*/
	for (j = 1; j <= (4*r + 3); j++) {
		subChavesK[j] = somaBinario64(subChavesK[j-1], offset3);
	} 
	/*Passo 5 do algoritmo descrito no enunciado*/
	i = 0;
	j = 0;
	A = calloc(64, sizeof(int));
	B = calloc(64, sizeof(int));
	C = calloc(64, sizeof(int));

	/*Passo 6 do algoritmo descrito no enunciado*/
	for (s = 1; s <= (4*r + 3); s++) {
		C = somaBinario64(A, B);
		subChavesK[i] = deslocaCircular(somaBinario64(subChavesK[i], C), 3);
		A = subChavesK[i];
		i++;
		C = somaBinario64(A, B);
		L[j] = deslocaCircular(somaBinario64(L[j], C), mod64(C));
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
	/*free(B) liberado no L*/
    free(C);

    /*devolvendo a resposta*/
	return subChavesK;
}

/* Funcao que recebe 2 vetores com n bits e
// calcula c fazendo XOR de a com b
*/ 
int *xor(int *a, int *b, int n) {
	int *c;
	int i;

	c = malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		if (a[i] == b[i]) {
			c[i] = 0;
		}
		else {
			c[i] = 1;
		}
	}

	return c;
}

/* Funcao que preenche os vetores exp e log
// referente ao corpo de Galois(257)
*/
void galois257(int *exp, int *log) {
	FILE *galois;
	int i;

	galois = fopen("galois257", "r");

	if (galois == NULL) printf("Erro lendo arquivo de Galois\n");

	for (i = 0; i < 256; i++) {
		fscanf(galois, "%d", &exp[i]);
	}
	for (i = 0; i < 256; i++) {
		fscanf(galois, "%d", &log[i]);
	}

	fclose(galois);

	return;
}

/* Funcao que divide os 64 bits de A em 8 bytes
// de 8 bits
*/
int **divide64BitsEm8Bytes(int *A) {
	int **bytes;
	int i;

	bytes = malloc(8 * sizeof(int *));
	for (i = 0; i < 8; i++) {
		bytes[i] = malloc(8 * sizeof(int));
	}

	for (i = 0; i < 64; i++) {
		bytes[i/8][i%8] = A[i];
	}

	return bytes;
}

/* Funcao que implementa a operacao basica numero 3
// (em LaTeX \odot)
*/
int *odot(int *B, int *C) {
	int **bytesA, **bytesB, **bytesC;
	int *fBi, *fCi, *exp = NULL, *log = NULL, *resultado;
	int decimalB, decimalC;
	int i, j;

	exp = malloc(256 * sizeof(int));
	log = malloc(256 * sizeof(int));
	galois257(exp, log);

	bytesA = malloc(8 * sizeof(int *));

	bytesB = divide64BitsEm8Bytes(B);
	bytesC = divide64BitsEm8Bytes(C);

	
	for (i = 0; i < 8; i++) {
		decimalB = binarioParaDecimal(bytesB[i], 8);
		decimalC = binarioParaDecimal(bytesC[i], 8);
		fBi = decimalParaBinario(exp[decimalB], 8);
		fCi = decimalParaBinario(exp[decimalC], 8);
		bytesA[i] = xor(fBi, fCi, 8);
	}

	resultado = malloc(64 * sizeof(int));
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			resultado[(i*8) + j] = bytesA[i][j];
		}
	}
	return resultado;
}

/* Funcao que implementa a inversa da operacao basica numero 3
// (em LaTeX \odot)
*/
int *odotInv(int *A, int *C) {
	int **bytesA, **bytesB, **bytesC;
	int *exp = NULL, *log = NULL, *resultado, *expBin = NULL;
	int decimalC, indiceDoLog;
	int i, j;

	exp = malloc(256 * sizeof(int));
	log = malloc(256 * sizeof(int));
	galois257(exp, log);

	bytesB = malloc(8 * sizeof(int *));

	bytesA = divide64BitsEm8Bytes(A);
	bytesC = divide64BitsEm8Bytes(C);

	
	for (i = 0; i < 8; i++) {
		decimalC = binarioParaDecimal(bytesC[i], 8);
		expBin = decimalParaBinario(exp[decimalC], 8);
		indiceDoLog = binarioParaDecimal(xor(bytesA[i], expBin, 8), 8);
		bytesB[i] = decimalParaBinario(log[indiceDoLog], 8);
	}

	resultado = malloc(64 * sizeof(int));
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			resultado[(i*8) + j] = bytesB[i][j];
		}
	}
	return resultado;
}

/* Funcao que implementa o K 128 como descrito no enunciado
*/
int *K128(int *X, int **subChavesK, int R) {
	int *Xa, *Xb, *ka, *kb, *ke, *kf, *Xe, *Xf;
	int *Y1, *Y2, *Z, *XeFINAL, *XfFINAL, *resultado;
	int i;

	Xa = malloc(64 * sizeof(int));
	Xb = malloc(64 * sizeof(int));

	for (i = 0; i < 64; i++) {
		Xa[i] = X[i];
		Xb[i] = X[i+64];
	}

	for (i = 0; i < R; i++) {
		ka = subChavesK[i*4];
		kb = subChavesK[(i*4)+1];
		ke = subChavesK[(i*4)+2];
		kf = subChavesK[(i*4)+3];
		Xe = odot(Xa, ka);
		Xf = somaBinario64(Xb, kb);
		Y1 = xor(Xe, Xf, 64);
		Y2 = odot(somaBinario64((odot(ke, Y1)), Y1), kf);
		Z = somaBinario64(odot(ke, Y1), Y2);
		/*Saida de 1 iteracao eh a entrada da proxima*/
		Xa = xor(Xe, Z, 64);
		Xb = xor(Xf, Z, 64);
	}
	ka = subChavesK[(i*4)];
	kb = subChavesK[(i*4)+1];
	XeFINAL = odot(Xb, ka);
	XfFINAL = somaBinario64(Xa, kb);

	resultado = malloc(128 * sizeof(int));
	for (i = 0; i < 64; i++) {
		resultado[i] = XeFINAL[i];
		resultado[i+64] = XfFINAL[i];
	}

	return resultado;
}

/* Funcao que implementa o  inverso do K 128 utilizado na decriptografia
*/
int *K128Inv(int *X, int **subChavesK, int R) {
	int *XeFINAL, *XfFINAL, *XeLinha, *XfLinha, *Xe, *Xf, *Xa, *Xb;
	int *Y1, *Y2, *Z;
	int *ka, *kb, *ke, *kf;
	int *resultado;
	int i;

	XeFINAL = malloc(64 * sizeof(int));
	XfFINAL = malloc(64 * sizeof(int));

	for (i = 0; i < 64; i++) {
		XeFINAL[i] = X[i];
		XfFINAL[i] = X[i+64];
	}
	XeLinha = somaBinario64Inv(XfFINAL, subChavesK[((4*R) + 1)]);
	XfLinha = odotInv(XeFINAL, subChavesK[4*R]);

	for (i = 0; i < R; i++) {
		kf = subChavesK[(4*R) - ((4*i) + 1)];
		ke = subChavesK[(4*R) - ((4*i) + 2)];
		Y1 = xor(XeLinha, XfLinha, 64);
		Y2 = odot(somaBinario64((odot(ke, Y1)), Y1), kf);
		Z = somaBinario64(odot(ke, Y1), Y2);
		Xe = xor(XeLinha, Z, 64);
		Xf = xor(XfLinha, Z, 64);
		kb = subChavesK[(4*R) - ((4*i) + 3)];
		ka = subChavesK[(4*R) - ((4*i) + 4)];
		Xa = odotInv(Xe, ka);
		Xb = somaBinario64Inv(Xf, kb);
		XeLinha = Xa;
		XfLinha = Xb;
	}

	resultado = malloc(128 * sizeof(int));
	for (i = 0; i < 64; i++) {
		resultado[i] = XeLinha[i];
		resultado[i+64] = XfLinha[i];
	}

	return resultado;
}