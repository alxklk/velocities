using System;
using System.IO;

class Primes
{
	static int Main()
	{
		for(int i=0;i<50000;i++)
		{
			int comp=0;
			for(int j=2;j<i;j++)
			{
				float f=i;
				float rf=f/j;
				int r=i/j;
				float ri=r;
				if(rf==ri)
				{
					comp=1;
					break;
				}
			}
			if(comp==0)
			{
				Console.WriteLine("{0} --simple", i);
			}
		}
		return 0;
	}
};