/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:56 by juduval           #+#    #+#             */
/*   Updated: 2023/05/03 18:53:50 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *find_path(char **envp)
{
    int i;

    i = 0;
    while (envp[i++])
    {
        if (!ft_strncmp("PATH=", envp[i], 5))
        {
            printf("%s\n", envp[i]);
            return (&envp[i][5]);
        }
    }
	return (NULL);
}

char    **path_cmd(char **paths, char *cmd)
{
    int i;

    i = -1;
    while(paths[++i])
        paths[i] = ft_strjoin(paths[i], cmd);
    return (paths);
}

char *check_cmd(char **envp, char *av)
{
    int     i;
    char    **paths;
    char    **split_cmd;
    char    *pathcmd;
    
    i = 0;
    split_cmd = ft_split_bis(av, ' ');
    if (access(split_cmd[0], F_OK | X_OK) == 0)
    {
        ft_free_2(split_cmd);
        return (split_cmd[0]);
    }
    paths = ft_split(find_path(envp), ':');
    while (paths[i])
    {
        pathcmd = ft_strjoin(paths[i], split_cmd[0]);
        if (access(pathcmd, F_OK | X_OK) == 0)
        {
            ft_free_2(split_cmd);
            ft_free_2(paths);
            return (pathcmd);
        }
        free(pathcmd);
        i++;
    }
    ft_free_2(split_cmd);
    ft_free_2(paths);
    return(av);
}
