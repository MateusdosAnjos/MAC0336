CC = gcc
CFLAGS  = -g -Wall -ansi -pedantic

default: ep1

ep1:  ep1.o funcoesEp1.o conversao.o criptografa.o decriptografa.o aleatorioMetodo1.o
	$(CC) $(CFLAGS) -o ep1 ep1.o funcoesEp1.o conversao.o criptografa.o decriptografa.o aleatorioMetodo1.o -lm

ep1.o:  ep1.c funcoesEp1.h conversao.h criptografa.h aleatorioMetodo1.h
	$(CC) $(CFLAGS) -c ep1.c

criptografa.o:  criptografa.c criptografa.h 
	$(CC) $(CFLAGS) -c criptografa.c -lm	

decriptografa.o:  decriptografa.c decriptografa.h 
	$(CC) $(CFLAGS) -c decriptografa.c -lm		

funcoesEp1.o:  funcoesEp1.c funcoesEp1.h 
	$(CC) $(CFLAGS) -c funcoesEp1.c -lm

conversao.o:  conversao.c conversao.h 
	$(CC) $(CFLAGS) -c conversao.c -lm	

aleatorioMetodo1.o:  aleatorioMetodo1.c aleatorioMetodo1.h
	$(CC) $(CFLAGS) -c aleatorioMetodo1.c -lm		

teste:	teste.o funcoesEp1.o conversao.o
	$(CC) $(CFLAGS) -o teste teste.o funcoesEp1.o conversao.o -lm

teste.o:  teste.c funcoesEp1.h conversao.h
	$(CC) $(CFLAGS) -c teste.c -lm

clean: 
	$(RM) ep1 *.o *~
