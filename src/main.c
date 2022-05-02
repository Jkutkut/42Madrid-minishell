/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/02 16:52:21 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(void)
{
    extern char **environ;

    int i = -1;
    while (environ[++i])
    {
        printf("%s\n", environ[i]);
    }

    //char cwd_buffer[1000];
    //char *pwd = getcwd(cwd_buffer, 1000);
    //printf("%s➜ %s %s%s: %s%s\n", GREEN, CYAN, pwd, YELLOW, RESET, "rm -rf test/");

    while(1)
    {
        prompt();
    }
}