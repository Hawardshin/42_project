/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:19:08 by joushin           #+#    #+#             */
/*   Updated: 2022/07/14 17:50:51 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	chk_new_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_read_line(int fd, char *buff, char *backup)
{
	int 	read_size;
	char	*ret;
	int		l_size;

	ret = NULL;
	while (1)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		//read함수가 오류가 발생했다. ex) fd 값 틀림.
		if (read_size < 0)
			return (NULL);
		if (read_size < BUFFER_SIZE)
		{
			if (!ret)
				ret = ft_strdup(buff);
			else
				ret = ft_strjoin(ret, buff);
			return (ret);
		}
		//만약 개행이 존재하지 않는다. -> 이 문자열과 다른 문자열을 개행이 나올때까지 합친다.
		l_size = chk_new_line(buff);
		if (l_size == -1)
			return (NULL);
		else
		{
			if (!ret)
				ret = ft_strdup(buff);//널가드 안하는 이유 리턴 ret해주기 때문
			else
				ret = ft_strjoin(ret, buff);//널가드 안하는 이유 리턴 ret해주기 때문.
			return (ret);
		}
	}
}

char	*get_next_line(int fd)
{

	char		buff[BUFFER_SIZE + 1];//read에서 사용할 버퍼
	static int	idx;//현재 위치
	if (fd < 0 || BUFFER_SIZE <= 0)
    	return (NULL);
	if (!buff)
		return (NULL);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
  int fd;
  //atest.txt 를 읽음
  fd = open("./atest.txt", O_RDONLY);
  char *result;
  while (result)
  {
	  result = get_next_line(fd);
	  printf("%s",result);
	  printf("%p",result);
  }
  return (0);
}
/*read를 실패한다.
*/
