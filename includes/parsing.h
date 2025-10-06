/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:39:28 by ljudd             #+#    #+#             */
/*   Updated: 2025/10/06 11:09:48 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/**
 * @file parsing.h
 * @brief Parsing part of the program.
 */

# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "struct.h"

//	utils.c
/**
 * @brief Add a string to the given array of strings. Create a new array and
 * free the input one.
 * @param[in, out] vec Input array.
 * @param[in] str String to add.
 * @param[in] data Data structure for clean_exit if malloc fails.
 * @return New array created.
 */
char	**add_to_args(char **vec, char *str, t_data *data);
/**
 * @brief Indicate that an error happened during the parsing and print an error
 * message.
 * @param[out] data error_parse is set to true.
 * @param[in] msg Message to be printed.
 * @param[in] token If no message is given, print an error message depending on
 * the token type.
 */
void	parse_error(t_data *data, char *msg, t_token *token);
/**
 * @brief Print in output the list of tokens. Used for debugging.
 * @param[in] token First token of the list.
 */
void	token_visualizer(t_token *token);
/**
 * @brief Print in output the list of env variables. Used for debugging.
 * @param[in] env First env variable of the list.
 */
void	env_visualizer(t_env *env);
/**
 * @brief Print in output the list of commands. Used for debugging.
 * @param[in] cmd First cmd of the list.
 */
void	cmd_visualizer(t_cmd *cmd);

//	parsing.c
/**
 * @brief Copy a substring from src, starting at index i and of length j.
 * @param[in] src Source string.
 * @param[in] i Starting index.
 * @param[in] j Length of the substring.
 * @param[in] data Data structure for clean_exit if malloc fails.
 * @return char* New string created.
 */
char	*ft_strcpy_ij(char *src, int i, int j, t_data *data);
/**
 * @brief Parsing of the input string, to reach the command list used in the
 * execution phase. Four steps.
 * @param[in,out] data Input is used, token and cmd are created and error_parse
 * is modified if an error happens.
 */
void	core_parsing(t_data *data);

//	news.c
/**
 * @brief Create a new token structure.
 * @param[in] inputs Inputs of the token.
 * @param[in] quoted Whether the token is quoted or not. ' or " or \0 if not
 * quoted.
 * @param[in] past Previous token in the list (will set past->next).
 * @param[in] data Data structure for clean_exit if malloc fails.
 * @return t_token* New token created.
 */
t_token	*token_new(char *inputs, char quoted, t_token *past, t_data *data);

/**
 * @brief Create a new empty command structure.
 * @note res->args is initialized as an array with one NULL element.
 * @param[in] data Data structure for clean_exit if malloc fails.
 * @return t_cmd* New command created.
 */
t_cmd	*new_cmd(t_data *data);

/**
 * @brief Create a new redirection structure from a token.
 * @param[in] token Token from which we want to create a redirection.
 * @param[in] data Data structure for clean_exit if malloc fails.
 * @return t_redir* Redirection created.
 */
t_redir	*new_redir(t_token *token, t_data *data);

//	pretoken_subfunc.c
/**
 * @brief Add the current word as input the token and reset the word length
 * counter.
 * @param[in, out] data Inputs is used and token is created.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
void	pretoken_copy(t_data *data, int *i, int *j, t_token **token);

/**
 * @brief Handle the operators in the input string during the pretokenization
 * phase.
 * @param[in, out] data Inputs is used and token is created.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
void	pretoken_ope(t_data *data, int *i, int *j, t_token **token);

/**
 * @brief Handle the spaces in the input string during the pretokenization
 * phase.
 * @param[in, out] data Inputs is used and token is created.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
void	pretoken_space(t_data *data, int *i, int *j, t_token **token);

/**
 * @brief Handle the quotes in the input string during the pretokenization
 * phase.
 * @param[in, out] data Inputs is used and token is created.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
void	pretoken_quotes(t_data *data, int *i, int *j, t_token **token);

/**
 * @brief Recursive function to create the list of tokens from the input string.
 * @param[in, out] data Inputs is used, token is created and error_parse can be
 * set to true.
 * @param[in, out] i Current index in the input string.
 * @param[in, out] j Length of the current word being processed.
 * @param[in, out] token Current token being processed.
 */
void	pretoken_rec(t_data *data, int *i, int *j, t_token **token);

//	expander_subfunc.c
/**
 * @brief Add a character to the end of a string. Create a new string and free
 * the input one.
 * @param[in, out] str Pointer to the string we modify.
 * @param[in] c Character to add.
 * @param[in] data Data structure for clean_exit if malloc fails.
 */
void	add_char(char **str, char c, t_data *data);

/**
 * @brief Add a string to the end of a string. Create a new string and free
 * the input one.
 * 
 * @param[in, out] str Pointer to the string we modify.
 * @param[in] to_add String to add.
 * @param[in] data Data structure for clean_exit if malloc fails.
 */
void	add_str(char **str, char *to_add, t_data *data);

/**
 * @brief Add the exit code to the result string, starting from the index i.
 * 
 * @param[out] res Output string where the exit code is added.
 * @param[in] data Fetch the exit code.
 */
void	add_exit(char **res, t_data *data);

/**
 * @brief Expand a variable in a string, starting from the index i.
 * @param[out] res Output string where the expansion is added.
 * @param[in] inp Input string containing the variable to expand.
 * @param[in, out] i Current index in inp, is updated to the end of the
 * variable name.
 * @param[in] data Fetch the env list to find the variable.
 */
void	expand_dollar(char **res, char *inp, int *i, t_data *data);

/**
 * @brief Expand all the variables in a string.
 * @param[in] inp Input string to expand.
 * @param[in] data Fetch the env list to find the variables.
 * @return char* String after expansion.
 */
char	*expand_inputs(char *inp, t_data *data);

//	expander.c
/**
 * @brief Expand all the tokens in the token list.
 * @param[in, out] data token list is modified.
 */
void	expander(t_data *data);

//	pretoken.c
/**
 * @brief Create the list of tokens from the input string.
 * @note Empty tokens are created but will be deleted in the tokenization phase.
 * @param[in, out] data Inputs is used, token is created.
 */
void	pretokenization(t_data *data);

//	merge_adjacent.c
/**
 * @brief Merge consecutive CMD tokens that are not separated by a space.
 * This handles cases like echo hello'world' or echo hello""world where
 * quotes should not introduce spaces.
 * @param[in, out] data Token list is modified.
 */
void	merge_adjacent_tokens(t_data *data);

//	tokenization_subfunc.c
/**
 * @brief Delete the current token and adjust accordingly the previous and next.
 * @param[out] data error_parse is set to true if the list is empty after the
 * deletion.
 * @param[in, out] token token to delete.
 * @return t_token* next token after the deletion.
 */
t_token	*token_deleter(t_data *data, t_token *token);

/**
 * @brief Add the next token as a target to the current redirection token and
 * delete the next token from the list.
 * @param[out] data error_parse is set to true if the next token is a
 * redirection or a pipe.
 * @param[in, out] token Redirection token to which we want to add a target.
 */
void	token_redir_target(t_data *data, t_token *token);

//	tokenization.c
/**
 * @brief Change the token list to finish the tokenization phase, two steps.
 * @param[in, out] data token is modified and error_parse can be set to true.
 */
void	tokenization(t_data *data);

//	token_to_cmd_subfunc.c
/**
 * @brief Convert a command token into a command. Add the input to the args and
 * set cmd_path if not already set.
 * @param[in] token Token to convert.
 * @param[in, out] cmd Current command to which we add the argument.
 * @param[in] data Data structure for clean_exit if malloc fails.
 */
void	token_convert_cmd(t_token *token, t_cmd **cmd, t_data *data);

/**
 * @brief Convert a redirection token into a redirection in the current command.
 * @param[in] token Token to convert.
 * @param[in, out] cmd Current command to which we add the redirection.
 * @param[in] data Data structure for clean_exit if malloc fails.
 */
void	token_convert_redir(t_token *token, t_cmd **cmd, t_data *data);

/**
 * @brief Convert a pipe token into a new command in the command list.
 * @param[in, out] cmd Current command to which we add a new command.
 * @param[in] data Data structure for clean_exit if malloc fails.
 */
void	token_convert_pipe(t_cmd **cmd, t_data *data);

/**
 * @brief Convert a token depending on its type and the last treated token in a
 * command.
 * @param[out] data error_parse is set to true if an error happens.
 * @param[in, out] last_treated Last treated token type, is updated.
 * @param[in] token Current token to convert.
 * @param[in, out] cmd Current command to which we add args/redirs or create a
 * new command.
 */
void	token_converter(t_data *data, t_node_type *last_treated,
			t_token *token, t_cmd **cmd);

//	token_to_cmd.c
/**
 * @brief Convert the token list into a command list.
 * @param[in, out] data cmd is created and error_parse can be set to true.
 */
void	token_to_cmd(t_data *data);

#endif