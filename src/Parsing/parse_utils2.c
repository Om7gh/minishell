/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:05:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/22 10:45:32 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*remove_dquotes(t_tokenizer *tmp, int *i)
{
	char		*str;

	str = NULL;
	while (tmp->token[*i])
	{
		if (tmp->token[*i] != '"')
			str = ft_freq_strjoin(str, ft_freq_substr(tmp->token, *i, *i + 1));
		if (tmp->token[*i])
			(*i)++;
	}
	return (str);
}

char	*remove_squotes(t_tokenizer *tmp, int *i)
{
	char		*str;

	str = NULL;
	while (tmp->token[*i])
	{
		if (tmp->token[*i] != '\'')
			str = ft_freq_strjoin(str, ft_freq_substr(tmp->token, *i, *i + 1));
		if (tmp->token[*i])
			(*i)++;
	}
	return (str);
}

int	check_syntax_errors(t_tokenizer *token)
{
	if (*token->type != WORD && !token->next)
		return (printf("syntax error near unexpected token `%s'\n", \
			token->token), 258);
	if (*token->type == PIPE && *token->next->type == PIPE)
		return (printf("syntax error near unexpected token `%s'\n", \
			token->token), 258);
	return (0);
}

int	check_redirection_errors(t_tokenizer *token)
{
	if ((*token->type == LESS || *token->type == GREAT || \
		*token->type == GREATGREAT) && token->next)
	{
		if (*token->next->type == LESS || *token->next->type == GREAT || \
			*token->next->type == GREATGREAT)
			return (printf("syntax error near unexpected token `%s'\n", \
				token->token), 258);
	}
	return (0);
}

int	ft_split_len(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
