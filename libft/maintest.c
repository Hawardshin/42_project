#include<ctype.h> //isalpha 
#include"ft_isalpha.c"
#include"ft_isdigit.c"
#include<stdio.h>
int main()
{
	printf("\n-------------------isalpha-----------------\n");
	printf("input:: 1 :%d\n",isalpha('1'));
	printf("input:: a :%d\n" ,isalpha('a'));
	printf("input:: A :%d\n" ,isalpha('A'));
//	printf("input:: Aa :%d" ,isalpha("Aa"));
	printf("input:: 1 :%d\n",ft_isalpha('1'));
	printf("input:: a :%d\n" ,ft_isalpha('a'));
	printf("input:: A :%d\n" ,ft_isalpha('A'));
	printf("\n-------------------isdigit-----------------\n");
	printf("input:: 1 :%d\n",isdigit('1'));
	printf("input:: a :%d\n" ,isdigit('a'));
	printf("input:: A :%d\n" ,isdigit('A'));
//	printf("input:: Aa :%d" ,isalpha("Aa"));
	printf("input:: 1 :%d\n",ft_isdigit('1'));
	printf("input:: a :%d\n" ,ft_isdigit('a'));
	printf("input:: A :%d\n" ,ft_isdigit('A'));
}
