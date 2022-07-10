
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	slen;

	if (s && f)
	{
		slen = ft_strlen(s);
		i = 0;
		while (i < slen)
		{
			f(i, &s[i]);
			i++;
		}
	}
}
