/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:19:08 by joushin           #+#    #+#             */
/*   Updated: 2022/07/15 15:14:17 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include<stdio.h>
int	check_new_line(char *buf,int idx)
{
	while (buf[idx])
	{
		if (buf[idx] == '\n')
		{
			return (idx + 1);
		}
		idx++;
	}
	return (-1);
}

char	*ft_read_line(int fd, int idx,char *backup)
{
	char	buff[BUFFER_SIZE + 1];//read에서 사용할 버퍼
	int		read_size;
	char	*to_read;
	int		l_size;

	to_read = backup;
	while (1)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size < 0) //read함수가 오류가 발생했다. ex fd 값 틀림.
			return (NULL);
		if (read_size == 0)
			return (to_read);
		if (!to_read)
			to_read = ft_strdup(buff);
		else
			to_read = ft_strjoin(to_read, buff);
		if (read_size < BUFFER_SIZE)
			return (to_read);
		//만약 개행이 존재하지 않는다. 이 문자열과 다른 문자열을 개행이 나올때까지 합친다.
			l_size = check_new_line(buff, idx);
		if (l_size != -1)
		{
			if (!to_read)
				to_read = ft_strdup(buff); //널가드 안하는 이유 리턴 ret해주기 때문
			else
				to_read = ft_strjoin(to_read, buff); //널가드 안하는 이유 리턴 ret해주기 때문.
			return (to_read);
		}
	}
}

char	*ft_get_line(char *str)
{
	int		idx;
	char	*ret_line;
	int		i;

	i = 0;
	idx = check_new_line(str, 0);
	if (idx == -1)//이 경우는 아에 개행이 없는 경우이다.이 경우는 버퍼를 프리해줘야 한다?
		return (ft_strdup(str));
	ret_line = (char *)malloc(sizeof(char) * (idx));
	if (!ret_line)
		return (NULL);
	while (i < idx)
	{
		ret_line[i] = str[i];
		i++;
	}
	return (ret_line);
}

// read로 개행이 나올때까지 읽는다.
char	*get_next_line(int fd)
{
	static int	idx;//현재 위치
	static char	*backup;
	char		*ret_line;
	int			i;
	int			tmp;
	printf("backup :::%s\n",backup);
	if (backup)
		printf("backup dix\n\n");
	 if (fd < 0 || BUFFER_SIZE <= 0)
	 	return (NULL);
	printf("zz\n\n");
	 if (backup && !backup[idx] && check_new_line(backup, idx) >= 0)
	 {
		//printf("iiiiii");
	 	i = 0;
	 	tmp = idx;
	 	idx = check_new_line(backup, tmp);
		//printf("tmp :: %d idx ::%d",tmp,idx);
	 	ret_line = (char *)malloc(sizeof(char) * (idx - tmp + 1));
	 	if (!ret_line)
			return (NULL);
	 	while (tmp < idx)
	 		ret_line[i++] = backup[tmp++];
	 	ret_line[i] = '\0';
	 	return (ret_line);
	 }
	 printf("aaa");

	backup = ft_read_line(fd, idx, backup);
	//printf("%s",backup);
	//printf("%p",backup);
	ret_line = ft_get_line(backup);
	idx = check_new_line(backup, 0);
	return (ret_line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
  int fd;
  //atest.txt 를 읽음
  fd = open("./atest.txt", O_RDONLY);
  char *result;
  while (1)
  {
	  result = get_next_line(fd);
	  if (!result)
	  {
			printf("malloc no\n");
			return (0);
	  }
	  printf("%s", result);
	  printf("%p",result);
	  free(result);
  }
  return (0);
}
/*read를 실패한다.
*/
