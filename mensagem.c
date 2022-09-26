#include "mensagem.h"

Equacao carregaEquacaoDeMsg(mensagem_de_desafio msg) {
	operando x;
	memcpy(&x, msg + 1, TAMANHO_NUMERO);

	operando y;
	memcpy(&y, msg + 3, TAMANHO_NUMERO);

	operador op;
	memcpy(&op, msg + 5, TAMANHO_OPERADOR);

	Equacao eq = { x, y, op };

	return eq;
}

void inicializaDesafioAtravesDeMsg(Desafio *d, operando resultado,
		mensagem_de_desafio mes) {

	d->resultado = resultado;
	memcpy(d->msg, mes, COD_DESAFIO);
	memcpy(d->msg + 1, mes + 1, 2);
	memcpy(d->msg + 3, mes + 3, 2);
	memcpy(d->msg + 5, mes + 5, 1);
}

Desafio geraDesafio() {

	codigo cod = COD_DESAFIO;

	Equacao eq = geraEquacaoAleatoria();

	operando resultado = calcula(eq);

	mensagem_de_desafio mes;

	// seta todos os campos para zero
	memset(mes, '\0', sizeof(mes));

	// copia para a mensagem os valores gerados pela equacao
	memcpy(mes, &cod, sizeof(cod));
	memcpy(mes + 1, &eq.x, sizeof(eq.x));
	memcpy(mes + 3, &eq.y, sizeof(eq.y));
	memcpy(mes + 5, &eq.op, sizeof(eq.op));

	Desafio d;
	inicializaDesafioAtravesDeMsg(&d, resultado, mes);

	return d;

}

Resposta geraResposta(operando resultado) {
	Resposta r = { resultado };
	return r;
}

MsgResposta geraMsgDeResposta(Resposta r) {

	MsgResposta m;

	codigo cod = COD_RESPOSTA;

	// seta todos os campos para zero
	memset(m.msg, '\0', TAMANHO_MSG_RESPOSTA);

	// copia para a mensagem os valores gerados pela equacao
	memcpy(m.msg, &cod, sizeof(cod));
	memcpy(m.msg + 1, &r.resposta, sizeof(r.resposta));

	return m;

}

void imprimeDesafio(Desafio d) {

	Equacao eq = carregaEquacaoDeDesafio(d);

	printf("Por favor responda quanto eh %d ", eq.x);
	imprimeOperador(eq.op);
	printf(" %d:\n", eq.y);

}

void imprimeResposta(Resposta r) {

	operando resp;

	memcpy(&resp, &r.resposta, TAMANHO_NUMERO);

	printf("%d\n", resp);
}

bool confereResposta(Desafio d, Resposta r) {

	if (d.resultado == r.resposta)
		return true;

	return false;
}

Equacao carregaEquacaoDeDesafio(Desafio d) {

	operando x;
	memcpy(&x, d.msg + 1, TAMANHO_NUMERO);

	operando y;
	memcpy(&y, d.msg + 3, TAMANHO_NUMERO);

	operador op;
	memcpy(&op, d.msg + 5, TAMANHO_OPERADOR);

	Equacao eq = { x, y, op };

	return eq;

}

Resposta carregaRespostaDeMsg(mensagem_de_resposta m) {

	operando resp;

	memcpy(&resp, m + 1, TAMANHO_NUMERO);

	Resposta r = geraResposta(resp);

	return r;

}
