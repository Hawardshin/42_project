
#include"libft.h"

static int	check_len(int n)
{
	int	len;


	if (n < 0)
	{
		len = 2;
		n = n * -1;
	}
	else
		len = 1;
	while (n > 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*retstr;

	len = check_len(n);
	retstr = (char *)malloc(sizeof(char) * len + 1);
	if (!retstr)
		return (0);
	if (n < 0)
	{
		retstr[0] = '-';
		n = n * -1;
	}
	retstr[len] = '\0';
	len--;
	while (len)
	{
		retstr[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (retstr);
}
