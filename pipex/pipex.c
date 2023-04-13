#include <errno.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void    pipex(int file_1, int file_2, char **av, char **envp)
{
    int     end[2];
    pid_t   parent;

    if (pipe(end) < 0)
        perror("pipe: Error");
    parent = fork();
    if (parent < 0)
        return (perror("fork: Error"));
    if (!parent)
        child_process(file_1, av[2]);
    else
        parent_process(file_2, av[3]);
}

void    child_process(int file_1, char *cmd1)
{
    if (dup2(file_1, STDIN_FILENO) < 0);
        return (perror("dup2: Error"));
    if (dup2(end[1], STDOUT_FILENO) < 0);
        return (perror("dup2: Error"));
    
}

void    parent_process(int file_2, char *cmd2)
{
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