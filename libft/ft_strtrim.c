
#include"libft.h"

static int check_in(char a,char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}


char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*ret;

	start = 0;
	i = 0;
	end =ft_strlen(s1) - 1;
	while (s1[start] && check_in(s1[start], set))
		start++;
	while (s1[end] && check_in(s1[end],set) && start <= end)
		end--;
	ret = malloc(sizeof(char) * (end - start + 2));
	if (!ret)
		return (0);
	while (start <= end)
		ret[i++] = s1[start++];
	ret[i] = '\0';
	return (ret);
}
