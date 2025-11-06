/*

 * minifork.c - PoC para Aula 2.1.2 e 2.1.3

 * Demonstra o ciclo de vida fork() -> execve() -> waitpid().

 * Este é um ambiente de laboratório controlado.

 */



#include <stdio.h>      // Para printf(), perror()

#include <unistd.h>     // Para fork(), execve(), getpid()

#include <sys/wait.h>   // Para waitpid()

#include <stdlib.h>     // Para exit()



int main(int argc, char *argv[]) {

    

    pid_t pid;    // Variável para armazenar o ID do processo

    int status;   // Variável para armazenar o status de saída do filho



    /* * Preparação: Definir o programa a ser executado e seus argumentos.

     * args[0] é o próprio programa (/bin/ls)

     * args[1] é o primeiro argumento (-l)

     * O último elemento DEVE ser NULL.

     */

    char *args[] = {"/bin/ls", "-l", NULL}; 

    

    // O ambiente (envp) pode ser NULL para usar o ambiente padrão.

    char *envp[] = {NULL}; 



    printf("--- [Pai, PID: %d] Olá! Vou criar um filho para executar 'ls -l'.\n", getpid());



    // 1. CRIAÇÃO (A chamada fork())

    pid = fork(); 



    // O código a partir daqui é executado tanto pelo Pai quanto pelo Filho.

    // Nós diferenciamos os dois pelo valor de retorno do fork().



    if (pid < 0) {

        /* < 0: Erro Fatal */

        perror("fork falhou"); // perror imprime a mensagem de erro do sistema

        exit(1);

    }

    else if (pid == 0) {

        /* == 0: Estamos no Processo Filho */

        

        printf("   [Filho, PID: %d] Eu sou o filho! Vou me transformar em 'ls' via execve().\n", getpid());

        

        // 2. SUBSTITUIÇÃO (A chamada execve())

        // Se esta chamada for bem-sucedida, o código abaixo dela NUNCA executa.

        execve(args[0], args, envp);

        

        /* * Se chegamos aqui, o execve() falhou. 

         * (ex: /bin/ls não foi encontrado)

         */

        perror("execve falhou");

        exit(2); // Sair com um código de erro diferente

    }

    else {

        /* > 0: Estamos no Processo Pai */

        

        printf("--- [Pai, PID: %d] Criei o filho com PID: %d.\n", getpid(), pid);

        printf("--- [Pai, PID: %d] Vou esperar ele terminar (waitpid)...\n", getpid());



        // 3. TÉRMINO (A chamada waitpid())

        // O Pai bloqueia até que o filho (pid) termine.

        waitpid(pid, &status, 0); 

        

        printf("--- [Pai, PID: %d] Meu filho terminou. Hora de ir embora.\n", getpid());

    }



    /* Saída normal do processo Pai */

    return 0;

}
