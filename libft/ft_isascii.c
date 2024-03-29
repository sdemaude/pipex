/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:13:35 by sdemaude          #+#    #+#             */
/*   Updated: 2023/10/20 15:02:02 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if ((c >= 0 && c < 127) || (c == 127))
		return (1);
	else
		return (0);
}

/*int	main()
{
	char	c;

	c = 127;
	printf("%d\n", ft_isascii(c));
	printf("%d\n", isascii(c));
}*/
