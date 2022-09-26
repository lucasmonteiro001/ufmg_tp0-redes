#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "operacao.h"
#include "mensagem.h"

#define PORT_NUMBER 5001

int main(int argc, char *argv[]) {

	if (argc != 2) {
		perror("Parametros invalidos\n");
		printf("Correto: ./server <port_number>\n");
		return EXIT_FAILURE;
	}

	int sockfd, newsockfd;
	socklen_t clilen;

	struct sockaddr_in serv_addr, cli_addr;

	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(1);
	}

	listen(sockfd, 1);
	clilen = sizeof(cli_addr);

	mensagem_de_resposta client_answer;

	bool isCorrect;

	// Entra no modo listen
	while (1) {

		isCorrect = false;

		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0) {
			perror("ERROR on accept");
			exit(1);
		}

		// Enviar desafios ao cliente ate ele acertar
		while (isCorrect != true) {

			Desafio d = geraDesafio();
			//imprimeDesafio(d);

			// Envia a msg para o cliente
			n = write(newsockfd, d.msg, sizeof(d.msg));
			//printf("tamanho de msg de desafio: %lu\n", sizeof(d.msg));

			if (n < 0) {
				perror("ERROR writing to socket");
				exit(1);
			}

			bzero(client_answer, sizeof(client_answer));

			// Recebe a resposta do cliente
			n = read(newsockfd, client_answer, sizeof(client_answer));
			//printf("tamanho de msg de resposta: %lu\n", sizeof(client_answer));

			if (n < 0) {
				perror("ERROR reading from socket");
				exit(1);
			}

			Resposta r = carregaRespostaDeMsg(client_answer);

			char feedback;

			if (confereResposta(d, r) == true) {

				//printf("Sucesso! Autenticacao liberada.\n\n");

				isCorrect = true;

				// Envia a msg de acerto ao cliente
				feedback = COD_OK;

				n = write(newsockfd, &feedback, sizeof(feedback));
				//printf("tamanho de msg de feedback: %lu\n", sizeof(feedback));
				close(newsockfd);

			} else {
				// Envia a msg de erro ao cliente
				feedback = COD_WR;

				isCorrect = false;

				n = write(newsockfd, &feedback, sizeof(feedback));
				//printf("tamanho de msg de feedback: %lu\n", sizeof(feedback));

			}

		}

	}

	return 0;
}
