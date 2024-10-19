/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:12:49 by skang             #+#    #+#             */
/*   Updated: 2024/10/12 17:33:28 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_ch(char *s, char c)
{
	int	index;

	index = 0;
	while (s[index] != '\0' && s[index] != c)
	{
		index++;
	}
	return (index);
}

static int	get_word_count(char *s, char c)
{
	int	index;
	int	count;
	int	in_word;

	index = 0;
	count = 0;
	in_word = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (s[index] == c)
		{
			in_word = 0;
		}
		index++;
	}
	return (count);
}

static char	**free_ptr(char **ptr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static char	**write_split(char const *s, char **s_ptr, int word_count, char c)
{
	int	index;
	int	ch_count;
	int	s_ptr_idx;

	index = 0;
	s_ptr_idx = 0;
	while (s_ptr_idx < word_count)
	{
		while (s[index] == c)
			index++;
		ch_count = count_ch((char *)&s[index], c);
		s_ptr[s_ptr_idx] = ft_substr((char *)&s[index], 0, (size_t)ch_count);
		if (s_ptr[s_ptr_idx] == NULL)
			return (free_ptr(s_ptr, s_ptr_idx));
		s_ptr_idx++;
		index += ch_count;
	}
	s_ptr[s_ptr_idx] = NULL;
	return (s_ptr);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**s_ptr;

	if (!s)
		return (NULL);
	word_count = get_word_count((char *)s, c);
	s_ptr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!s_ptr)
		return (NULL);
	if (write_split(s, s_ptr, word_count, c) == NULL)
		return (NULL);
	return (s_ptr);
}
