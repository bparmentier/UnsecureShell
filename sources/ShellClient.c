/*
NOM     : ShellClient.c
CLASSE  : IPC - IPC051
#OBJET  : réservé au makefile
AUTEUR  : Bruno Parmentier, 03/2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define FBUF_MAX_SIZE 2048
#define KBUF_MAX_SIZE 254

main() {
    int sock, h, len, i;
    char c;
    char kbuf[KBUF_MAX_SIZE] = ""; // buffer clavier
    char fbuf[FBUF_MAX_SIZE] = ""; // buffer socket
    char buffer[FBUF_MAX_SIZE]; // buffer d'écriture du résultat sur stdout
    struct sockaddr_in sockstr;
    struct in_addr adresse;

    /* initialisation de la connexion */
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("SOCKET");
        exit(1);
    }

    sockstr.sin_family = AF_INET;
    sockstr.sin_port = htons(5990); // converti port little endian en big endian
    if (!inet_aton("127.0.0.1", &adresse)) {
        perror("INET_ATON");
        exit(1);
    }
    sockstr.sin_addr=adresse;

    /* demande de communication au serveur */
    if (connect(sock, &sockstr, sizeof(sockstr)) == -1) {
        perror("CONNECT");
        exit(1);
    }

    printf("Connexion établie.\n");
    printf("(\"exit\" pour sortir)\n");

    /* lecture au clavier et envoi des commandes au serveur */
    while (1) {
        printf("$ ");
        fgets(kbuf, KBUF_MAX_SIZE, stdin);
        if (strncmp(kbuf, "exit", 4) == 0) break;
        write(sock, kbuf, KBUF_MAX_SIZE);
        len = read(sock, fbuf, FBUF_MAX_SIZE);
        fbuf[len] = '\0';
        i = 0;
        while (((buffer[i] = fbuf[i]) != '\0') && (i < FBUF_MAX_SIZE)) {
            putc(buffer[i], stdout);
            i++;
        }
        fbuf[0] = '\0';
            
    }

    write(sock, "exit", KBUF_MAX_SIZE);
    close(sock);
    exit(0);
}
