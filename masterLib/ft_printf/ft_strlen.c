/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:48:08 by glevin            #+#    #+#             */
/*   Updated: 2024/06/03 15:27:03 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The	strlen(void) function takes a string as an argument and returns its length.
The returned value is of type size_t (an unsigned integer type).
*/

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
	{
		size++;
	}
	return (size);
}
