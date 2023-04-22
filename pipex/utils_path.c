/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:56 by juduval           #+#    #+#             */
/*   Updated: 2023/04/22 14:29:22 by juduval          ###   ########.fr       */
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

char    **path_cmd(char **paths, char *cmd)
{
    int i;

    i = -1;
    while(paths[++i])
        paths[i] = ft_strjoin(paths[i], cmd);
    return (paths);
}

char *check_cmd(char **envp, char **av,  int j)
{
    int i;
    char **paths;
    char **cmds;
    
    i = 0;
    cmds = gather_cmds(av);
    paths = path_cmd(ft_split(find_path(envp), ':'), cmds[j]);
    while (paths[i])
    {
        if (acces(paths[i], F_OK | X_OK) == 0)
            return (paths[i]);
        i++;
    }
    return(NULL);
}
// acces(cmds[i], F_OK | X_OK) < 0)