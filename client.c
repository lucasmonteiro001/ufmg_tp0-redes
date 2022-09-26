#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "operacao.h"
#include "mensagem.h"

int main(int argc, char *argv[]) {
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	mensagem_de_desafio server_answer;

	if (argc < 3) {
		perror("Parametros invalidos\n");
		printf("Correto: ./client <host> <port_number>\n");
		exit(EXIT_FAILURE);
	}
	portno = atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}
	server = gethostbyname(argv[1]);

	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR connecting");
		exit(1);
	}

	bool isCorrect;

	isCorrect = false;

	while (isCorrect != true) {

		// le a mensagem de desafio
		bzero(server_answer, sizeof(server_answer));
		n = read(sockfd, server_answer, sizeof(server_answer));

		if (n < 0) {
			perror("ERROR reading from socket");
			exit(1);
		}

		Equacao eq = carregaEquacaoDeMsg(server_answer);
		operando res = calcula(eq);

		Desafio d;
		inicializaDesafioAtravesDeMsg(&d, res, server_answer);
		imprimeDesafio(d);

		Resposta r = geraResposta(res);

		scanf("%hd", &r.resposta);

		MsgResposta m = geraMsgDeResposta(r);

		// Envia a resposta para o server
		n = write(sockfd, m.msg, sizeof(m.msg));

		if (n < 0) {
			perror("ERROR writing to socket");
			exit(1);
		}

		// Le o feedback do servidor
		char feedback;
		n = read(sockfd, &feedback, sizeof(feedback));

		if (feedback == COD_OK) {
			isCorrect = true;
			printf("Sucesso! Autenticacao liberada.\n\n");
		} else if (feedback == COD_WR) {
			printf(
					"Erro! Voce esta muito cansado, tente novamente mais tarde.\n\n");
			isCorrect = false;
		} else {
			perror("\nCODIGO ERRADO\n");
			exit(EXIT_FAILURE);
		}

	}

	// se chegou aqui, a resposta foi correta
	close(sockfd);

	return EXIT_SUCCESS;
}
