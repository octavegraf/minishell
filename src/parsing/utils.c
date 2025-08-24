/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:46:52 by ljudd             #+#    #+#             */
/*   Updated: 2025/08/24 15:45:26 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *inputs, char quoted, t_token *next, t_token *past)
{
	t_token	*res;

	res = ft_calloc(1, sizeof(t_token));
	if (!res)
		clean_exit(12);
	res->inputs = inputs;
	res->quoted = quoted;
	res->next = next;
	res->past = past;
	return (res);
}

void	parse_error(t_data *data, char *msg)
{
	data->error_parse = true;
	ft_dprintf(2, "%s", msg);
}

void	token_visualizer(t_token *token)
{
	while (token)
	{
		ft_printf("inputs:%s\n", token->inputs);
		ft_printf("quoted:%c\n", token->quoted);
		ft_printf("type:%d\n", token->type);
		ft_printf("redir_type:%d\n", token->redir_type);
		ft_printf("target:%s\n\n", token->target);
		token = token->next;
	}
}

void	env_visualizer(t_env *env)
{
	while (env)
	{
		ft_printf("name:%s\n", env->name);
		ft_printf("value:%s\n\n", env->value);
		env = env->next;
	}
}
