#include <mictcp.h>
#include <stdio.h>

#define MAX_SIZE 1000

int main() {
    int sockfd;
    int running = 1;
    mic_tcp_sock_addr addr;
    mic_tcp_sock_addr remote_addr;
    char chaine[MAX_SIZE];
    char * exit_command = "/exit";

    addr.ip_addr = "127.0.0.1";
    addr.port = 1234;


    if ((sockfd = mic_tcp_socket(SERVER)) == -1) {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Erreur a la creation du socket MICTCP!\n");
        return 1;
    } else {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Creation du socket MICTCP: OK\n");
    }

    if (mic_tcp_bind(sockfd, addr) == -1) {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Erreur lors du bind du socket MICTCP!\n");
        return 1;
    } else {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Bind du socket MICTCP: OK\n");
    }

    if (mic_tcp_accept(sockfd, &remote_addr) == -1) {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Erreur lors de l'accept sur le socket MICTCP!\n");
        return 1;
    } else {
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Accept sur le socket MICTCP: OK\n");
    }


    memset(chaine, 0, MAX_SIZE);

    printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Appuyez sur CTRL+C pour quitter ...\n");

    while(running) {
        int rcv_size = 0;
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Attente d'une donnée, appel de mic_recv ...\n");
        rcv_size = mic_tcp_recv(sockfd, chaine, MAX_SIZE);
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Réception d'un message de taille : %d\n", rcv_size);
        printf("[\x1b[1m\x1b[93m_TSOCK_\x1b[0m] Message Recu : \x1b[1m%s\x1b[0m", chaine);
        if (strncmp(chaine,exit_command,4) == 0) {running = 0;}
    }
    return 0;
}
