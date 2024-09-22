/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tax_collector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:26:42 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/22 10:56:37 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	collect_taxes(t_collector **taxes)
{
	t_collector	*current;
	t_collector	*temp;

	if (!taxes || !*taxes)
		return ;
	current = *taxes;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->ptr);
		free(temp);
	}
	*taxes = NULL;
}

static void	appand_taxes(t_collector **taxes, void *ptr)
{
	t_collector	*new_tax;

	new_tax = malloc(sizeof(t_collector));
	if (!new_tax)
		return (perror("Malloc :"));
	new_tax->ptr = ptr;
	new_tax->next = *taxes;
	*taxes = new_tax;
}

void	*o_malloc(size_t size, t_malloc flag)
{
	static t_collector	*freq_taxes;
	static t_collector	*end_taxes;
	void				*ptr;

	1 && (end_taxes = NULL, freq_taxes = NULL);
	if (flag == FREQ)
	{
		ptr = malloc(size);
		if (!ptr)
			return (perror("Malloc :"), NULL);
		appand_taxes(&freq_taxes, ptr);
		return (ptr);
	}
	else if (flag == END)
	{
		ptr = malloc(size);
		if (!ptr)
			return (perror("Malloc :"), NULL);
		return (appand_taxes(&end_taxes, ptr), ptr);
	}
	else if (flag == CLEAR_FREQ)
		collect_taxes(&freq_taxes);
	else if (flag == CLEAR_END)
		collect_taxes(&end_taxes);
	return (NULL);
}
