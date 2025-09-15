#include <unistd.h>
#include <stdio.h>
int main(int ac, char *av[], char *env[])
{
    if(chdir(av[1]) == 0)
        printf("Sucesso\n");
    else
        perror("-minishell: cd");
    return 0;
}