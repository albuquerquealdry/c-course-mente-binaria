/*

 * payload.c - PoC de "Payload" Malicioso Simulado

 * Tenta se conectar ao localhost:4444.

 * Este é um ambiente de laboratório controlado.

 */



#include <stdio.h>

#include <unistd.h>     // Para getpid()

#include <stdlib.h>     // Para exit()

#include <string.h>     // Para memset()



// Cabeçalhos de Rede (Networking)

#include <sys/socket.h> // Para socket(), connect()

#include <arpa/inet.h>  // Para sockaddr_in, inet_addr()



#define TARGET_IP   "172.23.195.120"

#define TARGET_PORT 4444



int main(int argc, char *argv[]) {

    int sock_fd;

    struct sockaddr_in serv_addr;



    printf("   [Filho-Payload, PID: %d] Olá! Eu sou o payload.\n", getpid());

    printf("   [Filho-Payload, PID: %d] Simulação: Tentando 'ligar para casa' (C2 Beacon) para %s:%d\n", 

           getpid(), TARGET_IP, TARGET_PORT);



    // 1. Criar o descritor de arquivo do socket

    // AF_INET = IPv4, SOCK_STREAM = TCP

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd < 0) {

        perror("   [Filho-Payload] Erro ao criar socket");

        exit(1);

    }



    // 2. Preparar a estrutura de endereço do servidor (localhost:4444)

    memset(&serv_addr, 0, sizeof(serv_addr)); // Limpar a estrutura

    serv_addr.sin_family = AF_INET;

    serv_addr.sin_port = htons(TARGET_PORT); // htons() = Host-to-Network Short



    // Converter o IP "127.0.0.1" para o formato de rede binário

    if (inet_pton(AF_INET, TARGET_IP, &serv_addr.sin_addr) <= 0) {

        perror("   [Filho-Payload] Endereço IP inválido");

        exit(2);

    }



    // 3. Tentar se conectar ao servidor

    // Esta é a chamada de sistema que queremos detectar!

    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {

        perror("   [Filho-Payload] Conexão Falhou (Isso é esperado se nada estiver ouvindo na porta)");

        // Nota: Nós *esperamos* que isso falhe, pois não há servidor.

        // O importante é que a *tentativa* (a syscall) será registrada.

    } else {

        printf("   [Filho-Payload] Conexão Bem-Sucedida! (Inesperado, mas ok)\n");
        sleep(30);

    }



    // 4. Limpeza


    printf("   [Filho-Payload, PID: %d] Missão concluída. Encerrando.\n", getpid());

    

    return 0;

}
