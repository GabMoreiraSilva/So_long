/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoreira <gmoreira@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:17:52 by gmoreira          #+#    #+#             */
/*   Updated: 2022/05/17 20:17:21 by gmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void					*ptr;
	long long unsigned int	result;

	ptr = NULL;
	result = nmemb * size;
	if (nmemb != 0 && result / nmemb != size)
		return (NULL);
	ptr = malloc(result);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, result);
	return (ptr);
}
