/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:36:45 by juduval           #+#    #+#             */
/*   Updated: 2023/05/22 22:34:55 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    child(char **av, char **envp, int *end) 
{
    int     f1;
    char    *cmd1;
    char    **split_cmd;

    if ((f1 = open(av[1], O_RDONLY)) == -1)
    {    
        close(end[0]);
        close(end[1]);
        perror("could not open file, error");  
        exit(1);
    }
    cmd1 = check_cmd(envp, av[2]);
    split_cmd = ft_split_bis(av[2], ' ');
    if (access(cmd1, F_OK | X_OK) != 0)
        perror("command one not found, error");
    if (dup2(f1, STDIN_FILENO) < 0)
        perror("dup2 error");
    if (dup2(end[1], STDOUT_FILENO) < 0)
        perror("dup2 error");
    close(end[0]);
    close(end[1]);
    close(f1);
    execve(cmd1, split_cmd, envp);
    ft_free_2(split_cmd);
}

void    main_process(char **av, char **envp, int *end)
{
    int     f2;
    char    *cmd2;
    char    **split_cmd;

    if ((f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644)) == -1)
    {    
        close(end[0]);
        close(end[1]);
        perror("could not open file, error");    
        exit(1);
    }
    cmd2 = check_cmd(envp, av[3]);
    split_cmd = ft_split_bis(av[3], ' ');
    if (access(cmd2, F_OK | X_OK) != 0)
        perror("command two not found, error");
    if (dup2(end[0], STDIN_FILENO) < 0)
        perror("dup2 error");
    if (dup2(f2, STDOUT_FILENO) < 0)
        perror("dup2 error");
    close(end[0]);
    close(end[1]); 
    close(f2);  
    execve(cmd2, split_cmd, envp);
    ft_free_2(split_cmd);
}

void    pipex(char **av, char **envp)
{
    int   end[2];
    int   status;
    pid_t child_nb;
    pid_t child2;

    if (pipe(end) < 0)
        return (perror("pipe error"));
    child_nb = fork();
    if (child_nb < 0)
        return (perror("fork error"));
    if (*av[2] == '\0' && child_nb == 0)
        write (2, "command one not found, error\n", 29);
    if (child_nb == 0 && *av[2] != '\0')
        child(av, envp, end);
    child2 = fork();
    if (*av[3] == '\0' && child2 == 0)
        write (2, "command two not found, error\n", 29);
    if (child2 < 0)
        return (perror("fork error"));
    if (child2 == 0 && *av[3] != '\0')
        main_process(av, envp, end);
    close(end[0]);
    close(end[1]);
    waitpid(child_nb, &status, 0);
    waitpid(child2, &status, 0);
}

int main(int ac, char **av, char **envp)
{
    if (ac !=5)
        return (write_error("Error : invalid number of args"));
    pipex(av, envp);
    return (0);
}
