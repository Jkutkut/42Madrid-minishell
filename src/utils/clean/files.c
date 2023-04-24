/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:40 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 19:08:24 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Closes the given fd. If null, nothing done.
 * If closed, the null value is assigned as a check.
 *
 * @param fd File descriptor.
 */
// TODO: close() can fail
void	ft_close_fd(int *fd)
{
	if (*fd > 1)
		close(*fd);
	*fd = INVALID;
}

void	ft_free_file(t_file *file)
{
	if (!file)
		return ;
	if (file->name)
		free(file->name);
	ft_close_fd(&file->fd);
	free(file);
}

void	ft_close_fds(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_lstclear((t_list **) &cmd->in, (void (*)(void *)) ft_free_file);
	ft_close_fd(&cmd->fd_in);
	ft_lstclear((t_list **) &cmd->out, (void (*)(void *)) ft_free_file);
}
