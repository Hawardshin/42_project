
#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*retstr;
	unsigned int	i;

	i = 0;
	retstr = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
		return (0);if (!retstr)

	while (s[i])
	{
		retstr[i] = f(i, s[i]);
		i++;
	}
	retstr[i] = '\0';
	return (retstr);
}
