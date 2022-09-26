#ifndef OPERACAO_H_
#define OPERACAO_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define SUB 0x0
#define ADD 0x1
#define MUL 0x2
#define EXP 0x3

typedef char operador;

typedef short int operando;

typedef struct Operacoes {
	operador SUBTRACAO;
	operador ADICAO;
	operador MULTIPLICACAO;
	operador EXPONENCIACAO;
} Operacoes;

static Operacoes OPERACOES = { SUB, ADD, MUL, EXP };

typedef struct Equacao {
	operando x;
	operando y;
	operador op;
} Equacao;

operando randNumero(operando min, operando max);

operador randOperador();

Equacao geraEquacaoAleatoria();

operando calcula(Equacao eq);

void imprimeEquacao(Equacao eq);

void imprimeOperador(operador op);

#endif /* OPERACAO_H_ */
