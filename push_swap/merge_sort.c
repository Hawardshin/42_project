#include <stdio.h>

int arr[100]; // 정렬해야 하는 친구.
int tmp[100]; // 잠시 도와줄 임시공간.

void	merge_sort(long L, long long R)
{
	long long	M;
	int	i;
	int	l;
	int	r;
	if (L >= R)
		return ;

	M = (L + R) / 2;
	merge_sort(L, M);
	merge_sort(M + 1, R);
	i = L;
	l = L;
	r = M + 1;
	while (r!= R + 1 || l != M + 1)
	{
		if ((r != R + 1 && l <= M && arr[l] < arr[r]) || r == R + 1)
			tmp[i] = arr[l++];
		else
			tmp[i] = arr[r++];
		i++;
	}
	i = L - 1;
	while (++i <=R)
	{
		arr[i] = tmp[i];
	}
}
int main()
{

}
