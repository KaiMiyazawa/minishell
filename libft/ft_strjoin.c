/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:53:18 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/11/24 18:48:35 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*result;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcat(result, s2, s1_len + s2_len + 1);
	return (result);
}

//int	main(void)
//{
//	char *a = "asdfghjkl";
//	char *b = "qwertyuiop";

//	char *s1 = "where is my ";
//	char *s2 = "malloc ???";

//	char *res = ft_strjoin(s1,s2);
//	if (res = ft_strjoin(s2, s1))
//		printf("aa\n");
//	printf("bb\n");
//}
