/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:56 by juduval           #+#    #+#             */
/*   Updated: 2023/04/27 19:07:23 by juduval          ###   ########.fr       */
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
            // printf("%s\n", envp[i]);
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
    {
        paths[i] = ft_strjoin(paths[i], cmd);
        // printf("%s\n", paths[i]);
    }
    return (paths);
}

char *check_cmd(char **envp, char *av)
{
    int     i;
    char    **paths;
    char    *res;
    char    **split_cmd;
    
    i = 0;
    split_cmd = ft_split_bis(av, ' ');
    // printf("split cmd est :%s\n", split_cmd[0]);
    printf("je passe la\n");
    if (access(av, F_OK | X_OK) == 0)
    {
        // printf("la cmd seule est :%s\n", av);
        ft_free_2(split_cmd);
        return (av);
    }
    printf("et la \n");
    paths = path_cmd(ft_split(find_path(envp), ':'), split_cmd[0]);
    while (paths[i])
    {
        // printf("split result : %d, %s\n", i, paths[i]);
        if (access(paths[i], F_OK | X_OK) == 0)
        {
            res = ft_strdup(paths[i]);
            ft_free_2(split_cmd);
            ft_free_2(paths);
            // printf("la ligne de cmd est :%s\n", res);
            return (res);
        }
        i++;
    }
    // printf("la cmd seule deux est :%s\n", cmd);
    ft_free_2(split_cmd);
    ft_free_2(paths);
    return(av);
}
