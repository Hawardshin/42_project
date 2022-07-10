#include "libft.h"

char	*ft_strjoin(char const *s1, char *const *s2)
{
	size_t 	len1;
	size_t	len2;
	char	*retstr;
	size_t 	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	retstr = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!retstr)
		return (0);
	while (i < len1)
	{
		retstr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		retstr[len1 + i] = s2[i];
		i++;
	}
	retstr[len1 +len2] = '\0';
	return (retstr);
}
