/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2022/11/27 18:24:53 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(void)
{
    extern char **environ;
    bool didExit;

    didExit = false;
    while(!didExit)
    {
        didExit = prompt();

        //int i = -1;
        // while (environ[++i])
        // {
        //     printf("%s\n", environ[i]);
        // }
    }
    printf("exit\n");
    //system("leaks minishell");
    return (0);
}