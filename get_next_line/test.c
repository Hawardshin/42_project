#include<stdio.h>
#include <fcntl.h>
#include<unistd.h>

static u_int32_t coud_()
{
	static int a = 1;
	//이거랑
	a++;
	return a;
}


int main()
{
//	static int a = 1;
//	printf("%d",a);
	printf("%d",coud_());
	printf("%d",coud_());
//	a = 5;
//	printf("%d",a);
}
