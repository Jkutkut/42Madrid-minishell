/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:26:37 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/12 19:04:55 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sig_handler_prompt(int signal)
{
	(void) signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_prompt_signals(void)
{
	signal(SIGINT, sig_handler_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	sig_handler_child_quit(int signal)
{
	(void) signal;
	printf("Quit: 3\n"); // TODO debug
	rl_redisplay();
}

void	ft_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sig_handler_child_quit);
}

static void	sig_handler_heredoc_int(int signal)
{
	(void) signal;
	ft_store_result_code(1, true);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	ft_heredoc_signals(void)
{
	signal(SIGINT, sig_handler_heredoc_int);
	signal(SIGQUIT, SIG_IGN);
}
