#include <stdio.h>

int main()
{
	for(int i=0;i<50000;i++)
	{
		int comp=0;
		for(int j=2;j<i;j++)
		{
			float f=i;
			float rf=f/j;
			int ri=rf;
			if(rf==ri)
			{
				comp=1;
				break;
			}
		}
		if(comp==0)
		{
			printf("%i -- simple\n",i);
		}
	}
	return 0;
}