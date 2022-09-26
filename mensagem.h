#ifndef MENSAGEM_H_
#define MENSAGEM_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operacao.h"

#define printLine printf(">>> waiting in line: %d\n", __LINE__);

// o tamanho eh definido em bytes
#define TAMANHO_MSG_DESAFIO 6
#define TAMANHO_MSG_RESPOSTA 3
#define TAMANHO_OPERADOR 1
#define TAMANHO_NUMERO 2

#define COD_DESAFIO 0x01
#define COD_RESPOSTA 0x02
#define COD_OK 0x03
#define COD_WR 0x04

typedef enum {
	false = 0, true = !false
} bool;

typedef char mensagem_de_resposta[TAMANHO_MSG_RESPOSTA];
typedef char mensagem_de_desafio[TAMANHO_MSG_DESAFIO];
typedef char mensagem_feedback;
typedef char codigo;

typedef struct Desafio {
	operando resultado; // resultado da eq gerada pela mensagem
	mensagem_de_desafio msg;
} Desafio;

typedef struct Resposta {
	operando resposta;
} Resposta;

typedef struct MsgResposta {
	mensagem_de_resposta msg;
} MsgResposta;

// gera Desafio com o resultado e a msg de desafio
Desafio geraDesafio();

void inicializaDesafioAtravesDeMsg(Desafio *d, operando resultado,
		mensagem_de_desafio mes);

Resposta geraResposta(operando resultado);

MsgResposta geraMsgDeResposta(Resposta);

bool confereResposta(Desafio d, Resposta r);

Equacao carregaEquacaoDeDesafio(Desafio d);

Equacao carregaEquacaoDeMsg(mensagem_de_desafio msg);

Resposta carregaRespostaDeMsg(mensagem_de_resposta m);

void imprimeDesafio(Desafio m);

void imprimeResposta(Resposta r);

#endif /* MENSAGEM_H_ */
