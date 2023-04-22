/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:36:45 by juduval           #+#    #+#             */
/*   Updated: 2023/04/22 16:11:50 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    pipex(char **av, char **envp)
{
    int   end[2];
    int   status;
    pid_t child1;
    pid_t child2;

    if (pipe(end) < 0);
        return (perror("pipe error"));
    child1 = fork();
    if (child1 < 0)
        return (perror("fork error"));
    if (child1 == 0)
        child_one(av, envp, end);
    child2 = fork();
    if (child2 < 0)
        return (perror("fork error"));
    if (child2 == 0)
        child_two(av, envp, end);
    close(end[0]);
    close(end[1]);
    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);
}
void    child_one(char **av, char **envp, int *end) 
{
    int     f1;
    char    *cmd1;

    f1 = open(av[1], O_RDONLY);
    cmd1 = check_cmd(envp, av, 0);
    if (cmd1 == "NULL")
        return (perror("access error"));
    if (dup2(f1, STDIN_FILENO) < 0)
        return (perror("dup2 error"));
    if (dup2(end[1], STDOUT_FILENO) < 0)
        return(perror("dup2 error"));
    execve(cmd1, av[1], envp);
    free(cmd1);
    close(end[0]);
    close(end[1]);
    close(f1);
}

void    child_two(char **av, char **envp, int *end)
{
    int     f2;
    char    **cmd2;

    f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
    cmd2 = check_cmd(envp, av, 1);
    if (cmd2 == "NULL")
        return (perror("access error"));
    if (dup2(f2, STDOUT_FILENO) < 0);
        return (perror("dup2 error"));
    if (dup2(end[0], STDIN_FILENO) < 0);
        return (perror("dup2 error"));
    execve(cmd2, av[1], envp);
    free(cmd2);
    close(end[0]);
    close(end[1]);
    close(f2);   
}

int main(int ac, char **av, char **envp)
{
    if (ac !=5)
        return (write_error("Error : invalid number of args"));
    pipex(av, envp);
    return (0);
}

// file_1 = stdin -> cmd1 = stdout -> cmd1 = stdin -> end[1] = stdout (child process)
// -> end[0] = stdin -> cmd2 = stdout -> cmd2 = stdin -> file_2 = stdout;

// int	main(int ac, char **av, char **envp)
// {
// 	(void)ac;
//     (void)av;
    
//     char **cmd;
//     char **res;
//     char **p_c;
    
//     int i = -1;
//     // int j = -1;
    
//     // cmd = gather_cmds(av);
//     res = ft_split(find_path(envp), ':');
//     // p_c = path_cmd(res, cmd[1]);
// //    printf("%c\n", res[0][0]);
//     while (res[++i])
//         printf("%s\n", res[i]);
//     ft_free(res, i);
//     // while (res[++i])
//     //     printf("%s\n", res[i]);
// }
