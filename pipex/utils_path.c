/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:56 by juduval           #+#    #+#             */
/*   Updated: 2023/04/14 18:49:17 by juduval          ###   ########.fr       */
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
            return (&envp[i][5]);
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

char    **gather_cmds(char **av)
{
    char **list_cmds;
    int i;
    int j;
    
    i = 2;
    j = 0;
    list_cmds = ft_calloc(3, sizeof(char *));
    if (!list_cmds)
        return (NULL);
    while(av[i] && i < 4)
    {
        list_cmds[j] = ft_strdup(av[i]);
        i++;
        j++;
    }
    return (list_cmds);
}

// acces(cmds[i], F_OK | X_OK) < 0)