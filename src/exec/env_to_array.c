/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:12:47 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/24 11:52:33 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_array(t_env *env)
{
	int		i;
	int		count;
	char	**array;
	char	*temp;

	count = env_size(env);
	array = ft_calloc((count + 1), sizeof(char *));
	if (!array)
		return (NULL);
	i = -1;
	while (env)
	{
		temp = ft_strjoin(env->name, "=");
		if (!temp)
			return (double_free((void **)array), NULL);
		array[++i] = ft_strjoin(temp, env->value);
		if (!array[i])
			return (double_free((void **)array), free(temp), NULL);
		free(temp);
		env = env->next;
	}
	return (array);
}

char	**path_to_array(char **path, t_cmd *cmd)
{
	int		i;
	char	*cmd_path;
	char	*temp;

	i = -1;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (double_free((void **)path), NULL);
		cmd_path = ft_strjoin(temp, cmd->cmd_path);
		if (!cmd_path)
			return (free(temp), double_free((void **)path), NULL);
		free(path[i]);
		path[i] = cmd_path;
		free(temp);
	}
	return (path);
}
