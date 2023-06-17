/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:38:03 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/18 00:22:03 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status_code; // TODO linux

/**
 * @brief Norminette issues :(. If the input read from readline()
 *       is NULL, print the correct thing.
 * 
 * @note '\033[F' -> Moves one line up
 * @note '\33[2k\r' -> Removes the whole line
 * @note 'printf(···) -> Re-prints the prompt + exit message
*/
static void	print_readline_error(void)
{
	printf("\033[F");
	printf("\33[2K\r");
	printf("%s%s", RL_PROMPT, EXIT_MSG);
	exit(g_status_code);
}

/**
 * @brief Prints a Prompt on the screen and let the user type freely.
 * 		  Stores the line in the history. Clears the print_parse_error() funct.
 * 		  Splits the line read by pipes ('|') and returns the result
 * 
 * @return char**, the line read splitted by pipes (array of raw commands)
*/
char	**get_input(void)
{
	char	*raw_input;
	char	*input;
	char	**splitted;

	print_parse_error(NULL, true);
	ft_prompt_signals();
	raw_input = readline(RL_PROMPT);
	if (!raw_input)
		print_readline_error();
	if (!str_equals(raw_input, ""))
		add_history(raw_input);
	input = join_three(ft_strdup(" "), raw_input, ft_strdup(" "));
	if (!is_valid_input(input))
	{
		free(input);
		return (NULL);
	}
	splitted = ft_split_quote_conscious(input, '|');
	free(input);
	if (!splitted)
		print_parse_error(ERROR_MALLOC, false);
	return (splitted);
}

/**
 * @brief Given a line read by readline(), returns whether the line is
 *        valid or not.
 * 
 * @param line_read, the line read by readline()
 * 
 * @return t_bool, whether the input is valid or not.
 * @note an invalid input is one that contains an empty pipe, or has no content
 *       at all ("\n").
*/
t_bool	is_valid_input(char *line_read)
{
	int		i;
	char	**split;
	t_bool	is_valid;

	split = ft_split_quote_conscious(line_read, '|');
	if (!split)
	{
		print_parse_error(ERROR_MALLOC, false);
		return (false);
	}
	i = 0;
	is_valid = true;
	while (split[i])
	{
		if (ft_strlen(split[i]) == 0)
			is_valid = false;
		free(split[i]);
		i++;
	}
	free(split);
	if (!is_valid && i != 1)
		print_parse_error(INV_TKN_MSG" `|'", false);
	if (!is_valid && i != 1)
		ft_store_result_code(258, true);
	return (is_valid);
}

/**
 * @brief Given an argument list, trims them from spaces. Both initial
 *        and final spaces. This is useful when having environment
 *        variables that expands to a bunch of spaces. This
 *        ensures correct behaviours in situations such as:
 *        'minishell> export test="          echo"'
 *        'minishell> $test Hello World'
 * 
 * @param arg_raw, a pointer to the argument list (triple pointer)
 * 
*/
void	clean_arguments_from_spaces(char ***args_raw)
{
	char	**args;
	int		idx;

	args = *args_raw;
	if (!args)
		return ;
	idx = 0;
	while (args[idx])
	{
		args[idx] = ft_strtrim_free(args[idx], " ");
		idx++;
	}
	*args_raw = clean_nulls(args);
}

/**
 * @brief given an Env. Variable List and a raw command, parses it and
 *        returns the result.
 * 
 * @param envp, the Environment Variable List. Will be used for expanding
 *        the Env. Variables (e.g.: $USER)
 * @param cmd_line, a String representing a command. Note that this is a
 *        single command. Not to be confused with line_read.
 * 
 * @return t_cmd*, the command generated by the funcion. 
 *         Will be NULL if anything went wrong
*/
t_cmd	*parse_command(t_env_lst *envp, char *cmd_line)
{
	t_cmd	*cmd;
	char	**splitted;

	splitted = clean_nulls(ft_split_quote_conscious(cmd_line, ' '));
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!splitted || !cmd)
	{
		print_parse_error(ERROR_MALLOC, false);
		if (cmd)
			free(cmd);
		if (splitted)
			free_str_array(splitted);
		return (NULL);
	}
	cmd->args = splitted;
	cmd->is_first_cmd_quoted = false;
	if (!fill_redirections(&cmd) || !expand_cmd(&cmd, envp))
	{
		ft_free_cmd(cmd);
		return (NULL);
	}
	clean_arguments_from_spaces(&cmd->args);
	if (cmd->args && cmd->args[0])
		cmd->cmd = get_main_command(&cmd->args, cmd->is_first_cmd_quoted);
	return (cmd);
}
