/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:55:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/22 10:42:13 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_validation(t_tokenizer *token, t_minishell *mini)
{
	int	error_code;

	if (token && *token->type == PIPE)
		return (printf("syntax error near unexpected token `%s'\n", \
			token->token), 258);
	while (token)
	{
		if (g_exit_stts == 6)
			return (-1);
		error_code = check_syntax_errors(token);
		if (error_code != 0)
			return (error_code);
		if (*token->type == LESSLESS && *token->next->type == WORD)
			if (!here_doc(token->next, mini))
				return (258);
		error_code = check_redirection_errors(token);
		if (error_code != 0)
			return (error_code);
		if (ft_strchr(token->token, '$') && *token->stat != INQUOTES)
			token->token = expansion(token->token, mini);
		token = token->next;
	}
	return (1);
}

void	handle_quotes(t_tokenizer **tmp, int quote_type)
{
	*(*tmp)->stat = quote_type;
	(*tmp)->token = ft_strjoin((*tmp)->token, (*tmp)->next->token);
	(*tmp)->next = (*tmp)->next->next;
}

void	handle_join(t_tokenizer **tmp)
{
	if ((*tmp)->next)
	{
		(*tmp)->token = ft_strjoin((*tmp)->token, (*tmp)->next->token);
		(*tmp)->next = (*tmp)->next->next;
	}
	else
		*tmp = (*tmp)->next;
}

void	join_tokens(t_tokenizer *token)
{
	t_tokenizer	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->joinable == 1 || (tmp->prev && tmp->prev->joinable == 1))
		{
			if (tmp->next && *tmp->next->stat == INQUOTES)
				handle_quotes(&tmp, INQUOTES);
			else if (tmp->next && *tmp->next->stat == INDQUOTES)
				handle_quotes(&tmp, INDQUOTES);
			else
				handle_join(&tmp);
		}
		else
			tmp = tmp->next;
	}
}

void	parse_input(t_minishell *mini, t_cmd **cmds)
{
	int	checker;

	checker = check_validation(mini->start, mini);
	if (checker == 258)
	{
		mini->ret_value = 258;
		return ;
	}
	if (checker == -1)
	{
		mini->ret_value = 1;
		return ;
	}
	join_tokens(mini->start);
	if (mini->start)
	{
		send_to_execution(mini->start, cmds);
		mini->cmd = *cmds;
		mini->ret_value = execution(mini, *cmds);
	}
}
