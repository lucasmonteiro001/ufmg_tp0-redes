#include "operacao.h"
#include "mensagem.h"
#include <string.h>

int main() {

	Desafio d = geraDesafio();

	Equacao eq = carregaEquacaoDeDesafio(d);

	imprimeDesafio(d);

	imprimeEquacao(eq);

	Resposta r = geraResposta(d.resultado);
	printf("\nA resposta correta eh: ");imprimeResposta(r);printf("\n");

//	existe a funcao confereResposta(desafio, resposta)

	MsgResposta m = geraMsgDeResposta(r);

	Resposta rr = carregaRespostaDeMsg(m);

	printf("\nResposta lida da msg de resposta: "); imprimeResposta(rr); printf("\n");
	printf("tamanho msg de resposta: %lu\n", sizeof(m));
	printf("tamanha msg de desafio: %lu\n", sizeof(d.msg));

	return (EXIT_SUCCESS);
}
