/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:19:08 by joushin           #+#    #+#             */
/*   Updated: 2022/07/16 17:49:43 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include<stdio.h>

int	check_new_line(char *buf)
{
	int	idx;

	idx = 0;
	while (buf[idx])
	{
		if (buf[idx] == '\n')
			return (idx + 1);
		idx++;
	}
	return (0);
}

char	*ft_read_line(int fd, char *backup)
{
	char	buff[BUFFER_SIZE + 1];
	size_t	read_size;
	char	*to_read;

	to_read = backup;
	while (!check_new_line(buff))
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size < 0)
			return (NULL);
		buff[read_size] = '\0';
		if (read_size == 0)
			return (to_read);
		if (!to_read)
			to_read = ft_strdup(buff);
		else
			to_read = ft_strjoin(to_read, buff);
	}
	return (to_read);
}

char	*ft_get_line(char **str)
{
	 char	*ret_line;
	 int		l;
	int		i;

	i = 0;
	l = check_new_line(*str);
	 if (l == -1)
	 	return (*str);
	 else
	 {
	 	ret_line = (char *)malloc(sizeof(char) * (l +1));
	 	if (!ret_line)
	 		return (NULL);
	 	while (i < l)
	 	{
	 		ret_line[i] = *(*str + i);
	 		i++;
	 	}
	 	ret_line[i] = '\0';
	 }//여기 까지 봤어요.
	 ft_memmove(*str, *str + l, ft_strlen(*str) - l);
	 (*str)[l] = '\0';
	 return (ret_line);
}

char	*get_next_line(int fd)
{
	int			move;
	static char	*backup;
	char		*ret_line;
	char		*tmp;
	int			i;

	i = 0;
	move = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = ft_read_line(fd, backup);
	//printf("%s\n",tmp);
	if (tmp && !backup)
	{
		backup = tmp;
		backup[ft_strlen(tmp)] = '\0';
	}
	else if (!tmp)
	{
		free(backup);
		backup = tmp;
		//backup[ft_strlen(tmp)] = '\0';
	}
	//printf("%s\n",backup);
	ret_line = ft_get_line(&backup);
	move = check_new_line(backup);
	if (ret_line == NULL)
		return (NULL);
	while (i < move)
	{
		backup++;
		i++;
	}
	return (ret_line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
  int fd;
  //atest.txt 를 읽음
  fd = open("./atest.txt", O_RDONLY);
  char *result ;
  for (int i = 0; i < 5; i++)
  {
	  result = get_next_line(fd);
	  if (!result)
	  {
			printf("malloc no\n");
			return (0);
	  }
	  printf("\n------aaaa------\n");
	  printf("%s", result);
	//   printf("%p\n",result);
	  free(result);
	  printf("-----nnnn----\n");
  }
  return (0);
}
/*read를 실패한다.
*/
//
