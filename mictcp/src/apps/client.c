#include <mictcp.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int main() {
    int sockfd = 0;
    int running = 1;
    char chaine[MAX_SIZE];
    char * exit_command = "/exit";
    mic_tcp_sock_addr addr;
    addr.ip_addr = "127.0.0.1";
    addr.port = 1234;

    if ((sockfd = mic_tcp_socket(CLIENT)) == -1) {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Erreur a la creation du socket MICTCP!\n");
        return 1;
    } else {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Creation du socket MICTCP: OK\n");
    }

    if (mic_tcp_connect(sockfd, addr) == -1) {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Erreur a la connexion du socket MICTCP!\n");
        return 1;
    } else {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Connexion du socket MICTCP: OK\n");
    }

    memset(chaine, 0, MAX_SIZE);

    printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Entrez vos messages à envoyer, CTRL+D pour quitter\n");
    printf(">>> \x1b[1m");
    while(running != 0 && fgets(chaine, MAX_SIZE , stdin) != NULL) {
        if (strncmp(chaine,exit_command,4) == 0) {running = 0;}
        int sent_size = mic_tcp_send(sockfd, chaine, strlen(chaine)+1);
        printf("\x1b[0m\n[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Appel de mic_send avec un message de taille : %ld\n", strlen(chaine)+1);
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Appel de mic_send valeur de retour : %d\n", sent_size);
        if (strncmp(chaine,exit_command,4) != 0) {printf(">>> \x1b[1m");}
    }

    mic_tcp_close(sockfd);

    return 0;
}
