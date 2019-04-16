CC = gcc
CFLAGS  = -g -Wall -ansi -pedantic

default: ep1

ep1:  ep1.o funcoesEp1.o
	$(CC) $(CFLAGS) -o ep1 ep1.o funcoesEp1.o

ep1.o:  ep1.c funcoesEp1.h 
	$(CC) $(CFLAGS) -c ep1.c

funcoesEp1.o:  funcoesEp1.c funcoesEp1.h 
	$(CC) $(CFLAGS) -c funcoesEp1.c

teste:	teste.o funcoesEp1.o
	$(CC) $(CFLAGS) -o teste teste.o funcoesEp1.o

teste.o:  teste.c funcoesEp1.h 
	$(CC) $(CFLAGS) -c teste.c

clean: 
	$(RM) ep1 *.o *~
