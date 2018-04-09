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

    printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Création du socket MICTCP: \n");
    if ((sockfd = mic_tcp_socket(CLIENT)) == -1) {
        printf("\x1b[1m\x1b[91mERROR\x1b[0m\n");
        return 1;
    } else {
        printf("\x1b[1m\x1b[92mOK\x1b[0m\n");
    }

    printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Connexion du socket MICTCP: \n");
    if (mic_tcp_connect(sockfd, addr) == -1) {
        printf("\x1b[1m\x1b[91mERROR\x1b[0m\n");
        return 1;
    } else {
        printf("\x1b[1m\x1b[92mOK\x1b[0m\n");
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

    printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Fermeture de la connexion.\n");
    mic_tcp_close(sockfd);

    return 0;
}
