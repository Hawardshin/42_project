#include<stdio.h>
#include"get_next_line.h"
int main()
{
	char *line;

	//line = "1";
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break;
		printf("%s",line);
		free(line);
	}
	return (0);
}
