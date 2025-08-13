/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:19:42 by ocgraf            #+#    #+#             */
/*   Updated: 2025/08/12 14:05:11 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* main_clean_next :
	clean all the elements used between two commands
*/
void	main_clean_next(t_data *data)
{
	// TBD TBD TBD
	return ;
}

/* main_loop :
	core loop used in function main, 4 parts
	- read the input
	- process the input to get the commands to execute
	- exec the commands
	- clean the elements
*/
int	main_loop(t_data *data)
{
	// prompt ? necessaire a gerer ? "minishell ATM"
	data->inputs = readline("minishell");
	// precaution a prendre relative au readline ?
	// readline vide a convertir en \n ?
	add_history(data->inputs);
	core_parsing(data);
	if (!data->error_parse)
		core_exec(data);
	main_clean_next(data);
}

/* main :
	the part post loop is never supposed to happen, we exit in the loop directly
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	ft_bzero(&data, sizeof(t_data));
	// recup environement a faire
	while (main_loop(&data))
		continue ;
	// fonction free_all
	return (data.exit_code);
}
