/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:40:59 by mayu              #+#    #+#             */
/*   Updated: 2023/10/31 21:37:40 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
	if (signum == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_replace_line("", 0);
		g_sigstatus = SIGINT;
		rl_redisplay();
	}
}

void	ft_signals(void)
{
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
}
