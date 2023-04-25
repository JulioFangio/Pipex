/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:56 by juduval           #+#    #+#             */
/*   Updated: 2023/04/25 19:02:26 by juduval          ###   ########.fr       */
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
    {
        paths[i] = ft_strjoin(paths[i], cmd);
        printf("%s\n", paths[i]);
    }
    return (paths);
}

char *check_cmd(char **envp, char *av)
{
    int     i;
    char    **paths;
    char    *cmd;
    char    *res;
    i = 0;
    cmd = av;
    if (access(cmd, F_OK | X_OK) == 0)
        return (cmd);
    paths = path_cmd(ft_split(find_path(envp), ':'), cmd);
    while (paths[i])
    {
        if (access(paths[i], F_OK | X_OK) == 0)
        {
            res = ft_strdup(paths[i]);
            ft_free_2(paths);
            return (res);
        }
        i++;
    }
    ft_free_2(paths);
    return(cmd);
}
