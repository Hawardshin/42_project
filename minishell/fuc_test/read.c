#include <stdio.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>

int main()
{
	char	*str;

	while (1)
	{
		str = readline("jshell$ ");
		if (!str)
		{
			printf("done\n");
			return (0);
		}
	}
}
