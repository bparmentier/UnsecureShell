/*
NOM     : ShellServeur.c
CLASSE  : IPC - IPC051
#OBJET  : réservé au makefile
AUTEUR  : Bruno Parmentier, 03/2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define BUF_MAX_SIZE 2047

main() {
    int i;
    char *tokens[100];

    struct sockaddr_in bd, s;
    int sock, h, len;
    char buf[255] = "";

    /* initialisation de la connexion */
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("SOCKET");
        exit(1);
    }

    bd.sin_family = AF_INET;
    bd.sin_port = htons(5990); // converti port little endian en big endian
    if (!inet_aton("127.0.0.1", &bd.sin_addr.s_addr)) {
        perror("INET_ATON");
        exit(1);
    }

    /* publication de l'adresse */
    if (bind(sock, &bd, sizeof(bd)) == -1) {
        perror("BIND");
        exit(1);
    }
    printf("Démarrage du serveur.\n");

    /* définition du nombre d'appels entrants */
    listen(sock, 1);

    /* attente d'une connexion */
    printf("Attente d'une connexion.\n");
    if ((h = accept(sock, &s, &len)) == -1) {
        perror("ACCEPT");
        exit(1);
    }
    printf("Connexion établie.\n");

    /* lecture du buffer et traitement des commandes */
    while (1) {
        len = read(h, buf, BUF_MAX_SIZE);
        i = 0;

	/* découpe de la chaine reçue en tableau de tokens */
        tokens[i] = strtok(buf, " \n");
        while (tokens[i] != NULL) {
            tokens[++i] = strtok(NULL, " \n");
        }
        tokens[i] = 0;
        if (strcmp(tokens[0], "exit") == 0) break;

	/* exécution de la commande */
        if (fork() == 0) {
            dup2(h, 1); // redirige stdout sur h
            execvp(tokens[0], tokens);
            printf("Commande invalide : %s\n", tokens[0]);
            exit(1);
        }
        wait(0);
    }

    printf("\"%s\" reçu.\nFermeture du serveur.\n", buf);
    close(sock);
    close(h);
    exit(0);
}
