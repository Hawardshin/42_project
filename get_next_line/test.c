#include<stdio.h>
#include <fcntl.h>
#include<unistd.h>

int main()
{
	int fd = open("./test.txt", O_RDONLY);
	for (int i=0; i < 10; i++)
	{
		char buff[10];
		printf("%d : %zd ", i, read(2, buff, 10));
	}
}
