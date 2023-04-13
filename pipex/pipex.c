#include <errno.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void    pipex(int file_1, int file_2, char **av)
{
    int   end[2];
    int   status;
    pid_t child1;
    pid_t child2;

    if (pipe(end) < 0);
        return (perror("Pipe: Error"));
    child1 = fork();
    if (child1 < 0)
        return (perror("Fork: Error"));
    if (child1 == 0)
        child_one(f1, cmd1);
    child2 = fork();
    if (child2 < 0)
        return (perror("Fork: Error"));
    if (child2 == 0)
        child_two(f2, cmd2);
    close(end[0]);
    close(end[1]);
    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);
}
void    child_one(int file_1, char *cmd1, char **envp)
{
    // inserer un boucle while pour verifier si le split est bon avec la fonction access
    if (dup2(file_1, STDIN_FILENO) < 0);
        return (perror("dup2: Error"));
    if (dup2(end[1], STDOUT_FILENO) < 0);
        return (perror("dup2: Error"));
    
}

void    parent_two(int file_2, char *cmd2, char **envp)
{
    // inserer un boucle while pour verifier si le split est bon avec la fonction access
    if (dup2(file_2, STDOUT_FILENO) < 0);
        return (perror("dup2: Error"));
    if (dup2(end[0], STDIN_FILENO) < 0);
        return (perror("dup2: Error"));   
}

int main(int ac, char **av, char **envp)
{
     int f1;
     int f2;

     f1 = open(av[1], O_RDONLY);
     f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
     if (f1 < 0 || f2 < 0)
          return (-1);
     pipex(f1, f2, av, envp);
     return (0);
}

// file_1 = stdin -> cmd1 = stdout -> cmd1 = stdin -> end[1] = stdout (child process)
// -> end[0] = stdin -> cmd2 = stdout -> cmd2 = stdin -> file_2 = stdout;