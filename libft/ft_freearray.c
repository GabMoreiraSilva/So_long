/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 22:29:24 by gmoreira          #+#    #+#             */
/*   Updated: 2022/10/18 21:04:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freearray(void **ptr)
{
	int	index;
	
	if (!ptr)
		return ;
	index = 0;
	while (ptr[index] != NULL)
	{
		ft_freeptr(ptr[index]);
		index++;
	}
	ft_freeptr(ptr);
}