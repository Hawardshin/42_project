#include <stdio.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>

int main()
{
	char *str;
	while (1)
	{
		str = readline("hello>");
		if (!str)
		{
			return 0;
		}
	}
}
