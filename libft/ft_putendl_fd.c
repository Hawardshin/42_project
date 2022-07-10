
#include"libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n',fd);
}


#include<stdio.h>

#include<string.h>
int main()
{
	ft_putendl_fd("hi my name is joushin", 1);

	printf("\n---------------after------------------\n");
	printf("\n---------------after------------------\n");
	printf("\n---------------after------------------\n");
	printf("\n---------------after------------------\n");

}
