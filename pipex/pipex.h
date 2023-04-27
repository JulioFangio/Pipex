/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:17:35 by juduval           #+#    #+#             */
/*   Updated: 2023/04/27 18:27:26 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

//utils
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
//utils 2
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_free_2(char **s);
int 	write_error(char *str);
//utils paths
char    *find_path(char **env);
char    **path_cmd(char **paths, char *cmd);
char    *check_cmd(char **envp, char *av);
//utils split
char    **ft_split(char const *s, char c);
char	**ft_split_bis(char const *s, char c);
char	**ft_free(char **s, int j);
//pipex
void    child(char **av, char **envp, int *end);
void    main_process(char **av, char **envp, int *end);
void    pipex(char **av, char **envp);

#endif

// ** path = tous
// *cmd = "wc -l" = split avec cmd, ' ';
// *pathname = celui du execve
// **cmd =  av 
// envp;